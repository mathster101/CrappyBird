all: entities main link


entities:
	g++ -c entities.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

main:
	g++ -c main.cpp -O3 -I"C:\Dev\SFML-2.5.1\include"

link:
	g++ main.o entities.o -o main  -O3 -L"C:\Dev\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system