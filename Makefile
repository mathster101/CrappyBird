
src := src

all: entities main link clean

entities:
	g++ -c $(src)/entities.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

main:
	g++ -c $(src)/main.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

link:
	g++ main.o entities.o -o main  -O3 -L"C:\Dev\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o