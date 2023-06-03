src := src

all: entities main link clean

entities: $(src)/entities.cpp $(src)/entities.hpp
	g++ -static -static-libgcc -static-libstdc++ -c $(src)/entities.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

main: $(src)/main.cpp
	g++ -static -static-libgcc -static-libstdc++ -c $(src)/main.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

link:
	g++ -static -static-libgcc -static-libstdc++ main.o entities.o -o main  -O3 -L"C:\Dev\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o