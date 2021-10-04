CC = gcc
CFLAGS = -Wall -Wextra -g
LFLAGS = -fopenmp
OFLAGS = -Ofast -march=native -mtune=native -ffast-math -finline-functions -funroll-loops -floop-interchange -ftree-vectorize -ftree-loop-vectorize

build: matrix 1d_dpfp 2d_dpfp 1d_spfp 2d_spfp

matrix: target/deps/1d_dpfp-matrix.o target/deps/2d_dpfp-matrix.o target/deps/1d_spfp-matrix.o target/deps/2d_spfp-matrix.o 

target/deps/1d_dpfp-matrix.o: src/1d_dpfp/matrix.c
	@mkdir -p target/deps/
	$(CC) $(CFLAGS) $(LFLAGS) $(OFLAGS) -c src/1d_dpfp/matrix.c -o $@
	
target/deps/2d_dpfp-matrix.o: src/2d_dpfp/matrix.c
	@mkdir -p target/deps/
	$(CC) $(CFLAGS) $(OFLAGS) -c src/2d_dpfp/matrix.c -o $@
	
target/deps/1d_spfp-matrix.o: src/1d_spfp/matrix.c
	@mkdir -p target/deps/
	$(CC) $(CFLAGS) $(OFLAGS) -c src/1d_spfp/matrix.c -o $@
	
target/deps/2d_spfp-matrix.o: src/2d_spfp/matrix.c
	@mkdir -p target/deps/
	$(CC) $(CFLAGS) $(OFLAGS) -c src/2d_spfp/matrix.c -o $@

1d_dpfp: src/1d_dpfp/main*.c target/deps/1d_dpfp-matrix.o
	$(CC) $(CFLAGS) $(LFLAGS) $(OFLAGS) src/1d_dpfp/main1.c target/deps/1d_dpfp-matrix.o -o target/1d_dpfp-genmat
	$(CC) $(CFLAGS) $(LFLAGS) $(OFLAGS) src/1d_dpfp/main2.c target/deps/1d_dpfp-matrix.o -o target/1d_dpfp-matsum
	$(CC) $(CFLAGS) $(LFLAGS) $(OFLAGS) src/1d_dpfp/main3.c target/deps/1d_dpfp-matrix.o -o target/1d_dpfp-matreduc
	$(CC) $(CFLAGS) $(LFLAGS) $(OFLAGS) src/1d_dpfp/main4.c target/deps/1d_dpfp-matrix.o -o target/1d_dpfp-matscale

2d_dpfp: src/2d_dpfp/main*.c target/deps/2d_dpfp-matrix.o
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_dpfp/main1.c target/deps/2d_dpfp-matrix.o -o target/2d_dpfp-genmat
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_dpfp/main2.c target/deps/2d_dpfp-matrix.o -o target/2d_dpfp-matsum
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_dpfp/main3.c target/deps/2d_dpfp-matrix.o -o target/2d_dpfp-matreduc
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_dpfp/main4.c target/deps/2d_dpfp-matrix.o -o target/2d_dpfp-matscale

1d_spfp: src/1d_spfp/main*.c target/deps/1d_spfp-matrix.o
	$(CC) $(CFLAGS) $(OFLAGS) src/1d_spfp/main1.c target/deps/1d_spfp-matrix.o -o target/1d_spfp-genmat
	$(CC) $(CFLAGS) $(OFLAGS) src/1d_spfp/main2.c target/deps/1d_spfp-matrix.o -o target/1d_spfp-matsum
	$(CC) $(CFLAGS) $(OFLAGS) src/1d_spfp/main3.c target/deps/1d_spfp-matrix.o -o target/1d_spfp-matreduc
	$(CC) $(CFLAGS) $(OFLAGS) src/1d_spfp/main4.c target/deps/1d_spfp-matrix.o -o target/1d_spfp-matscale

2d_spfp: src/2d_spfp/main*.c target/deps/2d_spfp-matrix.o
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_spfp/main1.c target/deps/2d_spfp-matrix.o -o target/2d_spfp-genmat
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_spfp/main2.c target/deps/2d_spfp-matrix.o -o target/2d_spfp-matsum
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_spfp/main3.c target/deps/2d_spfp-matrix.o -o target/2d_spfp-matreduc
	$(CC) $(CFLAGS) $(OFLAGS) src/2d_spfp/main4.c target/deps/2d_spfp-matrix.o -o target/2d_spfp-matscale

clean:
	rm -Rf target/ *.matx
