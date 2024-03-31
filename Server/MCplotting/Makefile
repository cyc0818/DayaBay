all: main
FiducialMC: FiducialMC.cc
	g++ -o FiducialMC FiducialMC.cc -O0 `root-config --cflags` `root-config --libs`

MCplotting: MCplotting.cc
	g++ -o MCplotting MCplotting.cc -O0 `root-config --cflags` `root-config --libs`

MCplotting2: MCplotting2.cc
	g++ -o MCplotting2 MCplotting2.cc -O0 `root-config --cflags` `root-config --libs`

MCplotting3: MCplotting3.cc
	g++ -o MCplotting3 MCplotting3.cc -O0 `root-config --cflags` `root-config --libs`

EnergySlices: EnergySlices.cc
	g++ -o EnergySlices EnergySlices.cc -O0 `root-config --cflags` `root-config --libs`

NeutronKE: NeutronKE.cc
	g++ -o NeutronKE NeutronKE.cc -O0 `root-config --cflags` `root-config --libs`

Time: Time.cc
	g++ -o Time Time.cc -O0 `root-config --cflags` `root-config --libs`

clean:
	rm ./MCplotting2

