
compile:
	mkdir -p build
	g++ -Wall -fexceptions -g  -c src/main.cpp -o build/main.o
	g++ -Wall -fexceptions -g  -c src/rv_disasm.cpp -o build/rv_disasm.o
	g++ -o build/disasm build/main.o build/rv_disasm.o

clean:
	rm -rf build/ *.o disasm
