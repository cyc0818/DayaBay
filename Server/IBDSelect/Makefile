all: main
main: main.cc
	g++ -g -o main main.cc `root-config --cflags` `root-config --libs` -lTreePlayer
clean:
	rm ./*~ ./*.o ./main
