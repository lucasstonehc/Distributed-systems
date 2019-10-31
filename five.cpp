#include <iostream>
#include <mpi.h>

/* Testar com 100000000 e 100000000 e depois alterar o rank para 8    -> Cálculo dos speedups  */
using namespace std;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    double start, final;
    long int NX = atoi (argv[1]);
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    unsigned long long ScatterDataOne[NX],ScatterDataTwo[NX];
    unsigned long long ReceiveDataOne[int(NX/world_size)],ReceiveDataTwo[int(NX/world_size)]; // all malloc size equals or greater than

    unsigned long long sum_to[world_size]; // this is a vector that received all local sums
    if(world_rank == 0){
        start = MPI_Wtime();
        for (int i=0; i<int(NX); i++) {
            ScatterDataOne[i] = rand() % 100;
            ScatterDataTwo[i] = rand() % 100;
        }
    } // fill all vectors 
   //Test
   /*
    if(world_rank == 0){
        for (int i=0; i<NX; i++) {
            ScatterDataOne[i] = 1;
            ScatterDataTwo[i] = 1;
        } 
    }*/

    MPI_Scatter(ScatterDataOne,NX/world_size,MPI_INT,ReceiveDataOne,NX/world_size,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(ScatterDataTwo,NX/world_size,MPI_INT,ReceiveDataTwo,NX/world_size,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    unsigned long long  sum;
    for(int i=0;i<int(NX)/world_size;i++){
            sum+=(ReceiveDataOne[i] * ReceiveDataTwo[i]);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&sum,1,MPI_INT,sum_to,1,MPI_INT,0,MPI_COMM_WORLD);

    if(world_rank == 0){
         unsigned long long sum_totally = 0;

        for(int i=0;i<world_size;i++){
            sum_totally += sum_to[i];
        }
        cout << "sum is: " << sum_totally << endl;
        final = MPI_Wtime();
        cout << "Totally time is " << final-start << endl;
    }
    
    /*cout << "After Scattter" <<endl;
    for(int i=0;i<NX/world_size;i++){
        cout << "Process " << world_rank << " received " << ReceiveData[i] << endl;
    }
    int sum;
    if(world_rank == 1){
        for(int i=0;i<NX/world_size;i++){
            sum+=ReceiveData[i];
        }
        cout << "Sum of rank " << world_rank << " is " << sum  <<endl;

    }
    if(world_rank == 2){
        for(int i=0;i<NX/world_size;i++){
            sum+=ReceiveData[i];
        }
        cout << "Sum of rank " << world_rank << " is " << sum << endl;
    }
    if(world_rank == 3){
        for(int i=0;i<NX/world_size;i++){
            sum+=ReceiveData[i];
        }
        cout << "Sum of rank " << world_rank << " is " << sum << endl;
    }

    MPI_Gather(&sum,1,MPI_INT,sum_to,1,MPI_INT,0,MPI_COMM_WORLD);
    

    if(world_rank == 0){
        int sum_total = 0;

        for(int i=0;i<world_size;i++){
            cout << "ID sum" << sum_to[i];
        }

        for(int i=0;i<world_size;i++){
            sum_total += sum_to[i];
        }
        cout << "sum is: " << sum_total << endl;
    }

   
*/

    MPI_Finalize();
}
