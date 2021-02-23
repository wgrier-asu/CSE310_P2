all: myAppStore

myAppStore: main.o
	g++ main.cpp -o main

main.o: main.cpp defn.h
	g++ main.cpp defn.h -c

clean:
	rm main.o
	rm defn.h.gch

