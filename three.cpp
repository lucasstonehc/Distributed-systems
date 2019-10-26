#include <stdio.h>
#include <iostream>
#include <mpi.h>


using namespace std;


// TO EXECUTE THIS PROGRAMMER
//mpic++ -g -Wall -o mpi_sum_multi two.cpp
//mpiexec -n 2 ./mpi_sum_multi

int main(int argc, char **argv ) {
    MPI_Init(&argc, &argv);
    //PROCESS ZERO
    int world_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    double buffer[5] = {10.0, -11.0, 90.0, 21.0, 56.0};
    if (world_rank == 0) {
        MPI_Send(buffer, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(buffer, 5, MPI_INT, 2, 0, MPI_COMM_WORLD);
        cout << "Buffer is sending..." << endl;

  } else if(world_rank == 1) {
        //add positive elements
        int totally = 0;
        MPI_Recv(buffer, 5, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i=0;i<5;i++){
            if(buffer[i] >= 0){
                totally+=buffer[i];
            }
        }
        std::cout << "The sum of positives elements is " << totally << endl;
    } else if(world_rank == 2){
        //add negative elements
        int totally = 0;
        MPI_Recv(buffer, 5, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i=0;i<5;i++){
            if(buffer[i] < 0){
                totally+=buffer[i];
            }
        }
        std::cout << "The sum of negatives elements is " << totally << endl;
    }

    MPI_Finalize();
    return 0;
}