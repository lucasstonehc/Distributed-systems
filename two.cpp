#include <stdio.h>
#include <iostream>
#include <mpi.h>


using namespace std;


// TO EXECUTE THIS PROGRAMMER
//mpic++ -g -Wall -o mpi_sum_multi two.cpp
//mpiexec -n 2 ./mpi_sum_multi

int main(int argc, char **argv ) {
    int count = 1;
    int source = 0, destination = 1;

    MPI_Init(&argc, &argv);
    //PROCESS ZERO
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int number, number_two;
    if (world_rank == 0) {
        number = -1;
        MPI_Send(&number, count, MPI_INT, destination, 0, MPI_COMM_WORLD);

        MPI_Recv(&number_two, count, MPI_INT, destination, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        printf("Sum %d",number+number_two);
    } else if (world_rank == 1) {
        number_two = 10;
        MPI_Recv(&number, count, MPI_INT, source, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        MPI_Send(&number_two, count, MPI_INT, source, 0, MPI_COMM_WORLD);

        printf("Product %d",number*number_two);
    }

    MPI_Finalize();
    return 0;
    }