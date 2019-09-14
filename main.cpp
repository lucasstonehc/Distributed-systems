
#include<iostream>
#include <cstdlib>
#include <omp.h>
#include <stdio.h>
using namespace std;
//g++ main.cpp -o main -fopenmp - to compile we need to use this command
void one(){
	#pragma omp parallel
	system("clear");
	cout << endl <<"Exercise number ONE" << endl;
	cout << "Number of threads are: " << omp_get_num_threads() << endl;
	
}

void two(){
	int num_threads;

	
	system("clear");
	cout << endl <<"Exercise number TWO" << endl;
	cout << endl <<"Type number of threads that you would like!" << endl;
	cin >> num_threads;

	if (num_threads > omp_get_num_threads()){
		num_threads = omp_get_num_threads();	
	}
	#pragma omp parallel num_threads(num_threads)
	cout << "I´m thread " << omp_get_thread_num() <<" of "<< num_threads << endl;
}

void three(){
	int a=0, b=0, c=0;
	#pragma omp parallel num_threads(4)
	#pragma omp single
	a++;
	#pragma omp critical
	b++;
	#pragma omp master
	c++;
	cout << a << " " << b << " " << c;
}
void menu(){
	int option = -1;
	cout << "Welcome, Mr.Potato" << endl;
	cout << "Choose one option, please!" << endl;
	while(option != 0){
		cout << "Type 1 to run programmer 1" << endl;
		cout << "Type 2 to run programmer 2" << endl;
		cout << "Type 3 to run programmer 3" << endl;
		cout << "Type 0 to exit" << endl;
		cin >> option;
		if(option < 0 || option > 3){
			system("clear");
			cout << "Invaled option, please type again" << endl;
		}
		switch(option){
			case 1:
				one();
			break;
			case 2:
				two();
			break;
			case 3:
				three();
			break;
			case 0:
			 exit(0);
			break;		
		}
	}
}

int main(){
	menu();
}
