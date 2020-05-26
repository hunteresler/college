
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"

#define MAXTHREADS 32

int p4test(int num);
void *myp4test(void* arg);
int elems[MAXTHREADS][2];
int extra;
int hextra;
int spread;

int main(int argc, const char* argv[])
{
	alarm(60);

	if (argc < 3)
	{
		printf("Need 2 arguments: %s <threads> <maxarg>\n", argv[0]);
		exit(1);
	}

	int threads, maxarg;
	threads = atoi(argv[1]);

	if (threads < 1) {
		printf("Need <threads> to be greater than 0\n");
		exit(1);
	} else if (threads > MAXTHREADS) {
		printf("Can't have more <threads> than %d\n", MAXTHREADS);
		exit(1);
	}

	maxarg = atoi(argv[2]);

	pthread_t tid[MAXTHREADS];

	int myid[MAXTHREADS];

	spread = maxarg/(threads);

	//hextra = (maxarg-(spread*threads));//basically modulo?

	extra = 0;//we have extras
	hextra = maxarg % threads; // number of threads that need an extra number
	if (hextra != 0) {
		extra = 1;
	}

	int i;

	for (i = 0; i < (threads); i++) {
		elems[i][0] = 0;
		elems[i][1] = 0;
		myid[i] = i;
		if (i < threads && threads != 1) {
			pthread_create(&tid[i], NULL, myp4test, &(myid[i]));
		} else {//main thread
			myp4test(&(myid[i]));
		}
		//printf("i: %d\n", i);
	}

	for (i = 0; i < threads-1; i++) {
		pthread_join(tid[i], NULL);
	}

//	printf("max check\n");

	int max, val = 0;

	for (i = 0; i < threads; i++) {
		if (elems[i][0] > max) {
			max = elems[i][0];
			val = elems[i][1];
		}
	}

	printf("argument with highest return code: %d\n", val);
	printf("highest return code: %d\n", max);

	exit(0);

}


void* myp4test(void *arg) {
	int myid = *(int*)arg;
	int start = myid * spread;
	int end = start + spread;
	if (extra) {
		//shifting the start and end accordingly
		if (hextra-myid > 0)
		{
			start+=myid;
			end+=1;
//			printf("doing extra: %d\n", myid);
		} else {
			end+=hextra;//already done extras, shift by the number of extras
			start+=hextra;
		}
	}
	
	int i, rc, max, val;
	max = 0;
	val = 0;
	for (i = start; i < end; i++) {
		rc = p4test(i);	
		if (rc > 0 && rc > max) {
			max = rc;
			val = i;
		}
	}

	elems[myid][0] = max;
	elems[myid][1] = val;

}
