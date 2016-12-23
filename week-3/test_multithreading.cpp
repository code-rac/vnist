#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

// void *printHello(void *thread_id){
// 	long t_id;
// 	t_id = (long)thread_id;
// 	cout << "Hello World! thread_id = " << t_id << endl;
// 	pthread_exit(NULL);
// }

// int main(){
// 	pthread_t threads[NUM_THREADS];
// 	int rc, i;
// 	for(i=0; i<NUM_THREADS; i++){
// 		cout << "main(): Creating thread " << i << endl;
// 		rc = pthread_create(&threads[i], NULL, printHello, (void*)i);
// 		if(rc){
// 			cout << "Error: Unable to create thread," << rc << endl;
// 			exit(-1);
// 		}
// 	}
// 	pthread_exit(NULL);
// }

typedef struct thread_data{
	int thread_id;
	char *message;
}thread_data;

void *printHello(void *thread_arg){
	thread_data *my_data;
	my_data = (thread_data*)thread_arg;

	cout << "Thread ID: " << my_data->thread_id ;
	cout << "       Message: " << my_data->message << endl;

	pthread_exit(NULL);
}

int main(){
	pthread_t threads[NUM_THREADS];
	thread_data td[NUM_THREADS];

	int rc, i;

	for(i=0; i<NUM_THREADS; i++){
		cout << "main(): creating thread " << i << endl;
		td[i].thread_id = i;
		td[i].message = "This is message!";

		rc = pthread_create(&threads[i], NULL, printHello, (void*)&td[i]);

		if(rc){
			cout << "Error: Unable to create thread," << rc << endl;
			exit(-1);
		}
	}
	pthread_exit(NULL);
}