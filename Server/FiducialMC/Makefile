all: main
main: FiducialMC.cc
	g++ -o FiducialMC FiducialMC.cc -O0 `root-config --cflags` `root-config --libs`

clean:
	rm ./FiducialMC

