all: myAppStore

myAppStore: main.o util.o bst.o heap.o hash.o prime.o
	g++ -std=c++11 main.cpp util.cc bst.cc heap.cc hash.cc prime.cc -o myAppStore

main.o: main.cpp ./Headers/defn.h
	g++ -std=c++11 main.cpp ./Headers/defn.h -c

util.o: util.cc ./Headers/util.h
	g++ -std=c++11 util.cc ./Headers/util.h -c

bst.o: bst.cc ./Headers/bst.h
	g++ -std=c++11 bst.cc ./Headers/bst.h -c

heap.o: heap.cc ./Headers/heap.h
	g++ -std=c++11 heap.cc ./Headers/heap.h -c

hash.o: hash.cc ./Headers/hash.h
	g++ -std=c++11 hash.cc ./Headers/hash.h -c

prime.o: prime.cc ./Headers/prime.h
	g++ -std=c++11 prime.cc ./Headers/prime.h -c

clean:
	rm *.o
	rm *.gch

