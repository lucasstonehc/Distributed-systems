#include <iostream>
#include <mpi.h>

/* Testar com 100000000 e 100000000 e depois alterar o rank para 8    -> Cálculo dos speedups  */
using namespace std;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_rank,world_size;
    int NX = atoi (argv[1]);    

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int ScatterData[NX];
    int ReceiveData[NX];
    double sum_to[world_size];
    //fill the buffer
    if(world_rank == 0){
        for (int i=0; i<NX; i++) {
            ScatterData[i] = rand() % 100;
        }
    }
    MPI_Scatter(ScatterData,NX/world_size,MPI_INT,ReceiveData,NX/world_size,MPI_INT,0,MPI_COMM_WORLD);

    double sum;
   
    for(int i=0;i<NX/world_size;i++){
        sum+=ReceiveData[i];
    }
    sum = sum/NX;
    

    MPI_Gather(&sum,1,MPI_INT,sum_to,1,MPI_INT,0,MPI_COMM_WORLD);
    

    if(world_rank == 0){
        double average = 0;
        for(int i=0;i<world_size;i++){
            average += sum_to[i];
        }
        average =  average/world_size;
        cout << "average is: " << average << endl;
    }
    MPI_Finalize();
}

   
