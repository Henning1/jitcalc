# jitcalc

Trying out lemon parser and asmjit with a jit calculator. Sample output:

     ---- Enter a calculation ---- 
    1+2*3
    
     ---- Abstract Syntax Tree ---- 
    └── +
        ├──1
        └── *
            ├──2
            └──3
    
     ---- x86 Machine Assembly ---- 
    .section .text {#0}
    L1:
    mov eax, 1
    mov edx, 2
    mov ecx, 3
    imul edx, ecx
    add eax, edx
    L0:
    ret
    
     ---- Result ---- 
     = 7


## Instructions

- First build asmjit: Go to jitcalc/asmjit and execute `cmake .` and `make`. 
- Then build jitcalc: Go to jitcalc and execute `make`.
- Finally execute: Add jitcalc/asmjit to your library path, e.g. `export DYLD_LIBRARY_PATH=./asmjit:$DYLD_LIBRARY_PATH` on Mac. Then execute `./jitcalc`.
