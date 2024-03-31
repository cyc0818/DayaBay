all: main
main: main.cc
	g++ -o main main.cc -O0 `root-config --cflags` `root-config --libs`

clean:
	rm ./*~ ./*.o ./main

	#g++ -g -o main main.cc -lEG `root-config --cflags` `root-config --libs` -lTreePlayer
