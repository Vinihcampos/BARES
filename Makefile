CC = g++
CPPFLAGS = -std=c++11 -I include/
CPPSOURCE = src/bares.cpp src/driver.cpp
CPPDESTINY = bin/driver

all: driver

driver: 
	$(CC) $(CPPFLAGS) $(CPPSOURCE) -o $(CPPDESTINY) -g

clean:
	-rm -f *.o bin/driver *~

run: 
	./bin/driver data/simple.dat 

remade:
	$(MAKE) run 
	$(MAKE) clean
	$(MAKE)
