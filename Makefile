target:
	g++ -c lab6.cpp
	g++ -c InputHandler.cpp
	g++ -c assets.cpp
	g++ -o lab6 lab6.o InputHandler.o assets.o
