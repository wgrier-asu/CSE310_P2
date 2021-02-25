all: myAppStore

myAppStore: main.o util.o bst.o heap.o
	g++ main.cpp util.o bst.o heap.o -o myAppStore

main.o: main.cpp defn.h
	g++ main.cpp defn.h -c

util.o: util.cc util.h
	g++ util.cc util.h -c

bst.o: bst.cc bst.h
	g++ bst.cc bst.h -c

heap.o: heap.cc heap.h
	g++ heap.cc heap.h -c

hash.o: hash.cc
	g++ hash.cc -c


clean:
	rm main.o
	rm defn.h.gch

