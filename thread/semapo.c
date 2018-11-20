#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum=0;

sem_t sem1;
sem_t sem2;

void* thread_func(void* arg){
	for(int i=0; i<50; i++){
		sem_wait(&sem1);
		printf("thread1: %d\n", sum);
		sem_post(&sem2);
	}
}

int main(){

	sem_init(&sem1, 0, 1);// init before create pthread!
	sem_init(&sem2, 0, 0);
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread_func, NULL);
	
	for(int i=0; i<5; i++){
		sem_wait(&sem1);
		printf("thread2: %d\n", sum);
		sem_post(&sem2);
	}
	pthread_join(thread_1, NULL); // waithing creating thread

	printf("result: %d\n", sum);
	sem_destroy(&sem1);
	return 0;

}


