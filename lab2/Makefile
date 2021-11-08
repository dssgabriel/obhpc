FC = gfortran
CFLAGS = -Wall -Wextra -g
OFLAGS = -O3

build: genmat matsum matmul matreduc matscale

matrix_ops: src/matrix_ops.f90
	$(FC) $(CFLAGS) $(OFLAGS) -c $<

io_streams: src/io_streams.f90
	$(FC) $(CFLAGS) $(OFLAGS) -c $<

genmat: src/genmat.f90
	mkdir -p target/
	$(FC) $(CFLAGS) $(OFLAGS) $< -o target/$@

matsum: src/matsum.f90
	mkdir -p target/
	$(FC) $(CFLAGS) $(OFLAGS) $< -o target/$@

matmul: src/matmul.f90
	mkdir -p target/
	$(FC) $(CFLAGS) $(OFLAGS) $< -o target/$@

matreduc: src/matreduc.f90
	mkdir -p target/
	$(FC) $(CFLAGS) $(OFLAGS) $< -o target/$@

matscale: src/matscale.f90
	mkdir -p target/
	$(FC) $(CFLAGS) $(OFLAGS) $< -o target/$@

clean:
	@rm -rf target/ *.matx *.o *.mod
