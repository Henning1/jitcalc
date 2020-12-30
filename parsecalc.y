%token_type {ast::Node*}
%extra_argument { ast::Node** rootNode }

entry ::= expr(A). { *rootNode = A; }
expr(A) ::= expr(B)  PLUS   term(C). { A = ast::makeNode2 ( ast::NodeType::Plus,  B, C ); }
expr(A) ::= expr(B)  MINUS  term(C). { A = ast::makeNode2 ( ast::NodeType::Minus, B, C ); }
expr(A) ::= term(B).                 { A = B; }
expr ::= NUM.

term(A) ::= term(B)  MUL  factor(C). { A = ast::makeNode2 ( ast::NodeType::Multiply, B, C ); }
term(A) ::= term(B)  DIV  factor(C). { A = ast::makeNode2 ( ast::NodeType::Divide, B, C ); }
term ::= factor.

factor(A) ::= OB expr(B) CB.         { A = B; }
factor ::= NUM.



