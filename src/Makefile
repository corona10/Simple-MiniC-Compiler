all: smcc

clean:
	rm parser.cpp parser.hpp SMCC scanner.cpp
parser.cpp: parser.y
	bison -d -o $@ $^

parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $^

smcc: parser.cpp main.cpp scanner.cpp
	g++ -o smcc *.cpp
