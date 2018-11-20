#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum=0;

sem_t sem1;

void* thread_func(void* arg){
	for(int i=0; i<1000000; i++){
		sem_wait(&sem1);
		sum = sum-1;
		sem_post(&sem1);
		//printf("thread: %d\n", sum);
	}
}

int main(){

	sem_init(&sem1, 0, 1);// init before create pthread!
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread_func, NULL);
	
	for(int i=0; i<1000000; i++){
		sem_wait(&sem1);
		sum = sum+1;
		sem_post(&sem1);
		//printf("main: %d\n", sum);
	}
	pthread_join(thread_1, NULL); // waithing creating thread

	printf("result: %d\n", sum);
	sem_destroy(&sem1);
	return 0;

}


