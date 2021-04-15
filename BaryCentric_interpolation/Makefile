FLAGS = -std=c++14 -framework opengl -framework glut -w

main: main.o basic.o
	g++ main.o basic.o -o main $(FLAGS)

main.o: main.cpp
	g++ main.cpp -c $(FLAGS)

basic.o: basic.cpp basic.h
	g++ basic.cpp -c $(FLAGS)

clean:
	rm -f main *.o
