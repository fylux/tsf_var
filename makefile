# export LD_LIBRARY_PATH=/opt/intel/lib/intel64:/opt/intel/mkl/lib/intel64
CC=g++
CVERSION=-std=c++14
CGDB=-ggdb
COPT=-O3
CMKL=-I /opt/intel/mkl/include/ -L/opt/intel/mkl/lib/intel64 \
-lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core \
        -L /opt/intel/compilers_and_libraries_2017.4.196/linux/compiler/lib/intel64_lin -liomp5 -lpthread -lm 
#CMACROS=-D EXAHUSTIVE
CFLAGS=$(CVERSION) $(CGDB) $(COPT) $(CMACROS)

.PHONY : start clean

start: gen test 
	@echo './gen -var N -dep N -instances N [-ivar N -idep N] [-noise R]';
	@echo './test [-training R] < dataFile';
	
gen :  src/gen/gen.cpp build/genFromMatrix.o build/Time.o \
		build/printMatrix.o  build/vectorToPointer.o 
	 @$(CC) $^ -o gen $(CFLAGS) $(CMKL);

test : src/test/test.cpp build/lls.o build/genFromMatrix.o \
		build/Time.o build/vectorToPointer.o build/printMatrix.o
	 @$(CC) $^ -o test $(CFLAGS) $(CMKL);

build/genFromMatrix.o : src/gen/genFromMatrix.[ch]pp build/vectorToPointer.o
	@$(CC) -c $(basename $<).cpp -o $@ $(CFLAGS) $(CMKL);


build/lls.o : src/lls/lls.[ch]pp
	@$(CC) -c  $(basename $<).cpp -o $@ $(CFLAGS) $(CMKL);

build/%.o : src/util/%.[ch]pp
	@$(CC) -c $(basename $<).cpp -o $@ $(CFLAGS);

clean :
	@rm -f build/*
	@rm -f gen test

