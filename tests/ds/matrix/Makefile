all: matrix.test.exe

matrix.test.exe: matrix.test.cpp
	g++ --std=c++11 matrix.test.cpp -o matrix.test.exe

test: matrix.test.exe 
	./matrix.test.exe

spotless:
	-rm matrix.test.exe
