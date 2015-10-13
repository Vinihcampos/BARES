# MAKEFILE 
# AUTHORS: Vinicius Campos Tinoco Ribeiro
#		   Vitor Rodrigues Greati


CC = g++
CPPFLAGS = -std=c++11 -I include/
CPPSOURCE = src/bares.cpp src/driver.cpp
CPPDESTINY = bin/bares
DRIVEROBJECT = lib/driver.o
BARESOBJECT = lib/bares.o
DEFAULT = data/simple.dat

all: bares

bares: $(DRIVEROBJECT) $(BARESOBJECT)
	@echo ">>>Compiling all"
	$(CC) $(CPPFLAGS) $(DRIVEROBJECT) $(BARESOBJECT) -o $(CPPDESTINY) -g

$(DRIVEROBJECT): src/driver.cpp
	@echo ">>>Compiling driver.cpp"
	$(CC) $(CPPFLAGS) -c src/driver.cpp -o $(DRIVEROBJECT)

$(BARESOBJECT): src/bares.cpp
	@echo ">>>Compiling bares.cpp"
	$(CC) $(CPPFLAGS) -c src/bares.cpp -o $(BARESOBJECT)

clean:
	@echo ">>>Removing all compiled files"
	rm -f *o $(CPPDESTINY) $(DRIVEROBJECT) $(BARESOBJECT)

run:
	./bin/bares $(filter-out $@,$(MAKECMDGOALS))

remade:
	$(MAKE) run
	$(MAKE) clean
	$(MAKE)
