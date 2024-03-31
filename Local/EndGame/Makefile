all: main
main: nC_CrossSection.cc
	clang++ -o CrossSection nC_CrossSection.cc -O0 `root-config --cflags` `root-config --libs`

clean:
	rm ./CrossSection

