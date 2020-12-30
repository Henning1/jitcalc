# jitcalc

 ---- Enter a calculation ---- 
2*(3+4)

 ---- Abstract Syntax Tree ---- 
└── *
    ├──2
    └── +
        ├──3
        └──4

 ---- x86 Machine Assembly ---- 
.section .text {#0}
L1:
mov eax, 2
mov edx, 3
mov ecx, 4
add edx, ecx
imul eax, edx
L0:
ret

 ---- Result ---- 
 = 14


## Instructions

- First build asmjit: Go to jitcalc/asmjit and execute `cmake .` and `make`. 
- Then build jitcalc: Go to jitcalc and execute `make`.
- Finally execute: Add jitcalc/asmjit to your library path, e.g. `export DYLD_LIBRARY_PATH=./asmjit:$DYLD_LIBRARY_PATH` on Mac. Then execute `./jitcalc`.
