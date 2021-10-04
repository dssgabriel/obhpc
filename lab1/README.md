# OBHPC - Lab 1
## C programming

The goal of this lab is to write several C programs to work on matrices.

The end application should be able to :
1. Generate matrices initialized with random floating point values.
   Store them in files using the following unidimensional format:
   ```
   NB_ROWS NB_COLS
   VAL0 VAL1 VAL2...
   ```
   The dimensions and output file of the matrices must be passed from the
   command line as arguments to the program.
   ```sh
   ./genmat N M A.matx
   ```
2. Read matrices from files and compute their sum.
   The resulting matrix must be stored in a file using the format described
   above.
   The input and output files of the matrices must be passed from the 
   command line as arguments of the program.
   ```sh
   ./matsum A.matx B.matx C.matx
   ```
3. Read a matrix from a file and compute their reduction.
   The resulting scalar must be printed to the screen.
   The imput file of the matrix must be passed from the command line
   as an argument of the program.
   ```sh
   ./matreduc A.matx
   ```
4. Read a matrix from a file and compute their scaled version when multiplied
   by a constant.
   The resulting matrix must be stored using the format described
   above.
   The input and output files of the matrices, as well as the constant must be
   passed from the command line as arguments of the program.
   ```sh
   ./matscale A.matx K B.matx
   ```

Each of these must be implemented in different versions:
- 2D allocations using simple precision floating point (spfp)
- 2D allocations using double precision floating point (dpfp)
- 1D allocations using simple precision floating point (spfp)
- 1D allocations using double precision floating point (dpfp)

Every memory allocation must be dynamic.

## Installation
Once you have copied this repository onto your machine using `git clone`, you 
should be able to compile the source code provided that you have the following 
dependencies installed on your system:
- gcc
- GNU make
- OpenMP

To build everyting, simple run `make`.
Binaries will be placed in the `target/` directory.
