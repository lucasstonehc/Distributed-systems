#include <stdio.h>
#include <iostream>
#include <stdlib.h>
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
    int sub_rand_nums;
    
    if (world_rank == 0) {
        int rand_nums[10];
        for(int i=0;i<10;i++){
            rand_nums[i] = rand() % 100;
        } 
    }

    // Scatter the random numbers to all processes
    MPI_Scatter(rand_nums, 2, MPI_FLOAT, sub_rand_nums,2, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Compute the average of your subset
    float sub_avg = compute_avg(sub_rand_nums, 2);
    // Gather all partial averages down to the root process
    float *sub_avgs = NULL;
    if (world_rank == 0) {
        sub_avgs = malloc(sizeof(float) * world_size);
    }
    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);

    // Compute the total average of all numbers.
    if (world_rank == 0) {
        float avg = compute_avg(sub_avgs, world_size);
        cout << "Avengere is: " << avg << endl;
    }
    return 0;
}