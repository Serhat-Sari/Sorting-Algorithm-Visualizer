all: compile link

compile:
	g++ -I ../include -c *.cpp -Wall -Werror

link:
	g++ *.o -o main -L ../lib -lsfml-graphics -lsfml-window -lsfml-system 