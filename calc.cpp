#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <asmjit/x86.h>
#include <iostream>

#include "ast.h"
#include "parsecalc.c"



using namespace asmjit;

typedef int (*Func)(void);

x86::Gp translateNode ( ast::Node* node, x86::Compiler& cc ) {

    x86::Gp resL, resR, vreg;

    if ( node->left != NULL ) {
        resL = translateNode ( node->left, cc );
    }
    if ( node->right != NULL ) {
        resR = translateNode ( node->right, cc );
    }

    switch ( node->type ) {
        case ast::IntegerNumber:
            vreg = cc.newGpd();
            cc.mov ( vreg, node->val );
            return vreg;
 
        case ast::Plus:
            cc.add ( resL, resR );
            return resL;
        
        case ast::Minus:
            cc.sub ( resL, resR );
            return resL;
        
        case ast::Multiply:
            cc.imul ( resL, resR );
            return resL;
        
        case ast::Divide:
            x86::Gp rem = cc.newGpd();
            cc.mov ( x86::eax, resL );
            cc.cdq ( x86::edx, x86::eax );
            cc.idiv ( x86::edx, x86::eax, resR );
            cc.mov ( resL, x86::eax );
            return resL;
    }
}


void translate ( ast::Node* node ) {

    FileLogger logger(stdout);

    JitRuntime rt;                    // Runtime specialized for JIT code execution.
    CodeHolder code;                  // Holds code and relocation information.
 
    code.init(rt.environment());      // Initialize code to match the JIT environment.
    code.setLogger ( &logger );
    x86::Compiler cc(&code);          // Create and attach x86::Compiler to code.
 
    cc.addFunc(FuncSignatureT<int>());// Begin a function of `int fn(void)` signature.
 
    x86::Gp res = translateNode ( node, cc );
    cc.ret(res);                     // Return `vReg` from the function.
            
    cc.endFunc();                     // End of the function body.
    cc.finalize();                    // Translate and assemble the whole 'cc' content.
    // ----> x86::Compiler is no longer needed from here and can be destroyed <----
 
    Func fn;
    Error err = rt.add(&fn, &code);   // Add the generated code to the runtime.
    if (err) printf ( "error\n" );   // Handle a possible error returned by AsmJit.
    // ----> CodeHolder is no longer needed from here and can be destroyed <----
    
 
    printf ( "\n ---- Result ---- \n" );
    int result = fn();                // Execute the generated code.
    printf(" = %d\n", result);           // Print the resulting "1".
    
 
    rt.release(fn);  

}




int main(int argc, char *argv[]) {


    while ( 1 ) {

        ast::Node* astRoot;
        void *parser = ParseAlloc ( malloc );
        char str[100];
        printf( " ---- Enter a calculation ---- \n");
        fgets( str, 100, stdin );
        char* it = str;
        while ( *it != '\0' && it < (str+100) ) {
        
            if ( *it == ' ' ) { it++; continue; }
            
            ast::Node* node = nullptr;
  
            unsigned int tokType = 0; 
            int tokVal = 0;
 
            switch (*it) {
                case '+':
                    tokType = PLUS;
                    break;
                case '-':
                    tokType = MINUS;
                    break;
                case '*':
                    tokType = MUL;
                    break;
                case '/':
                    tokType = DIV;
                    break;
                case '(':
                    tokType = OB;
                    break;
                case ')':
                    tokType = CB;
                    break;
                case 'q':
                    exit(0);
                    break;
                default:
                    if ( isdigit(*it) ) {
                        tokType = NUM;
                        tokVal = strtol ( it, &it, 10 );
                        it--;
                    }
                    node = ast::makeNode0 ( ast::NodeType::IntegerNumber );
                    node->val = tokVal;
            } 

            Parse ( parser, tokType, node, &astRoot ); 
            it++;
        }

        Parse( parser, 0, 0, &astRoot );

        printf ( "\n ---- Abstract Syntax Tree ---- \n" );
        ast::print ( astRoot );

        printf ( "\n ---- x86 Machine Assembly ---- \n" );
        translate ( astRoot );

        ParseFree ( parser, free );
        printf ( "\n\n" );
    }

}
