/*
 *Author: Hunter Esler
 *Course: CSCI 4330
 *Lab number: Lab 1
 *Purpose: This lab will create 10 threads and print each thread number then end the program
 *Due date: January 23, 2018
 *
 * Used threadTemplate.c as a guideline (cs.mtsu.edu/~pettey/4330/labs)
 * */

#include <stdio.h>
#include <pthread.h>

//Number of threads
const int MAX = 10;

//What each child will run
void* child(void* me) {
	int num = *((int*)me);
	printf("Hello World from child thread %d\n", num);
}


int main()
{
	//threads
	pthread_t ids[MAX];
	
	//thread ids
	int nums[MAX];

	//i variable
	int i;
	//number of threads user asks for
	int num_threads = MAX + 1;
	do {
		printf("Input number of threads ");
		scanf("%d", &num_threads);
		if (num_threads < 1 || num_threads > MAX) {
			printf("Please input between 1 and %d\n", MAX);
		}
	} while (num_threads < 1 || num_threads > MAX);



	//creating threads
	for (i = 0; i < num_threads; i++) {
		nums[i] = i;
		pthread_create(&ids[i], NULL, child, (void*)&nums[i]);
	}
	//joining threads
	for (i = 0; i < num_threads; i++) {
		pthread_join(ids[i], NULL);
	}

	//thread exercize over
	printf("That's all from the parent\n");

	return 0;
}
