calc: parsecalc.y calc.cpp
	cc lemon/lemon.c -o lemon/lemon; \
	./lemon/lemon parsecalc.y; \
        clang++ -g calc.cpp -Iasmjit/src -std=c++11 -Lasmjit -lasmjit -o jitcalc


clean:
	rm -f parsecalc.c parsecalc.h *.out jitcalc
