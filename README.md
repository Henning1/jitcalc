# jitcalc

Trying out lemon parser and asmjit with an jit calucalator.

## Instructions

- First build asmjit: Go to jitcalc/asmjit and execute `cmake .` and `make`. 
- Then build jitcalc: Go to jitcalc and execute `make`.
- Finally execute: Add jitcalc/asmjit to your library path, e.g. `export DYLD_LIBRARY_PATH=./asmjit:$DYLD_LIBRARY_PATH` on Mac. Then execute `./jitcalc`.
