LDFLAGS=$(shell wx-config --libs) -ltiff
CXXFLAGS=$(shell wx-config --cxxflags)

all: Main.o App.o
	g++ Main.o App.o ${LDFLAGS} ${CXXFLAGS} -o minesweeper

Main.o: Main.cpp
	g++ -c Main.cpp ${LDFLAGS} ${CXXFLAGS} -o Main.o

App.o:
	g++ -c App.cpp ${LDFLAGS} ${CXXFLAGS} -o App.o
