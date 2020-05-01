all: items.o main.o searcher.o stock.o ui.o laba

items.o: items.cpp
    g++ -c -o items.o items.cpp

main.o: main.cpp
    g++ -c -o main.o main.cpp

searcher.o: searcher.cpp
	g++ -c -o searcher.o searcher.cpp

stock.o: stock.cpp
	g++ - c -o stock.o stock.cpp

ui.o: ui.cpp
	g++ -c -o stock.o stock.cpp

laba: items.o main.o searcher.o stock.o ui.o
     g++ main.o items.o searcher.o stock.o ui.o -o laba
