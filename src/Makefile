all: SMCC

clean:
	rm parser.cpp parser.hpp SMCC scanner.cpp
parser.cpp: parser.y
	bison -d -o $@ $^

parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $^

SMCC: parser.cpp main.cpp scanner.cpp
	g++ -o SMCC *.cpp
