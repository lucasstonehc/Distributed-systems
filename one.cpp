#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv ){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_size(MPI_COMM_WORLD, &rank);
    std::cout << "Hello world from process " << rank << " of " << size << std::endl;
    MPI_Finalize();
    return 0;
}