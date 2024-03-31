all: main
main: main.cc EventTree.C
	g++ -g -o main2 main.cc `root-config --cflags` `root-config --libs` -lTreePlayer

clean:
	rm ./*~ ./*.o ./main

