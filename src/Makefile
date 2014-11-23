all: smcc

clean:
	rm parser.cpp parser.hpp smcc scanner.cpp
parser.cpp: parser.y
	bison -d -o $@ $^

parser.hpp: parser.cpp

CodeGenerator.hpp: CodeGenerator.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $^

smcc: parser.cpp main.cpp scanner.cpp
	g++ -o  smcc *.cpp -std=c++0x `llvm-config --libs core  native --cxxflags --ldflags` -lpthread -lffi -ldl -lm -ltinfo -O3
