
build:
	g++ -Wall -fexceptions -g  -c src/main.cpp -o main.o
	g++ -Wall -fexceptions -g  -c src/rv_disasm.cpp -o rv_disasm.o
	g++ -o disasm main.o rv_disasm.o

clean:
	rm -f disasm *.o
