/*Author:  Hunter Esler
 *  *Course:  CSCI 4330
 *   *Lab number: Lab 5
 *    *Purpose: This lab will use mpich to simulate pond and turtle from lab5.html
 *    		 *Due date: April 5, 2019
 *    		 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//prints generation
void printgen(int pond[9], int turtlepos) {
	int x, i;
	for (x = 0; x < 3; x++) {
		for (i = 0; i < 3; i++) {
			printf("%d", pond[x*3+i]);
			if (turtlepos==x*3+i)
				printf("T ");
			else
				printf(" ");
		}
		printf("\n");
	}
}

//what clone values go to
int clonetbl[6] = {
	0,
	2,
	4,
	4,
	5,
	5
};

//rank indices points towards next value
int order[9] = {
	1, 2, 5, 4, 0, 8, 3, 6, 7
};

int generations = 10;

int getleft(int rank) {
	for (int i = 0; i < 9; i++)
		if (order[i]==rank)
			return i;
}

int main(int argc, char* argv[]) {

	int nproc, myrank, left, right, myindex;
	MPI_Status status;
	FILE *input;

	int turtlepos = -1;
	int pond[9];
	int myducks = 0;
	int tempt, tempd;

	int i,x;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	//get left and right neighbors
	left = getleft(myrank);
	right = order[myrank];

	//reading file
	if (myrank==0) {

		input = fopen("ola5.dat", "r");
		if (input==NULL) {
			fprintf(stderr, "Can't open ola5.dat!\n");
			exit(1);
		}
		for (i = 0; i < 9; i++) {
			pond[i] = 0;
			fscanf(input, "%d", &pond[i]);
			if (pond[i] > 5)
				pond[i] = 5;
			if (pond[i] < 0)
				pond[i] = 0;
			//printf("got: %d\n", pond[i][x]);
		}
		fscanf(input, "%d", &turtlepos);

		printgen(pond, turtlepos);
		fclose(input);

	}
	
	//scatter pond count
	MPI_Scatter(pond, 1, MPI_INT, &myducks, 1, MPI_INT, 0, MPI_COMM_WORLD);


	for (i = 0; i < generations; i++) {
		//send turtlepos after updating position
		MPI_Bcast(&turtlepos, 1, MPI_INT, 0, MPI_COMM_WORLD);

		//cloning
		myducks = clonetbl[myducks];
		if (turtlepos == myrank) {	
			myducks = myducks - 2;
			if (myducks < 0)
				myducks = 0;
		}
		//dumb bug
		right = order[myrank];//IF I DONT DO THIS RIGHT MAGICALLY CHANGES ITSELF AFTER A GENERATION? ? ? ? ? ? ? ?
		MPI_Sendrecv(&myducks, 1, MPI_INT, right, 42, &tempd, 1, MPI_INT, left, 42, MPI_COMM_WORLD, &status);
		myducks = tempd;
		MPI_Gather(&myducks, 1, MPI_INT, pond, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		if (myrank==0) {
			printf("After gen %d\n",i+1);
			turtlepos = getleft(turtlepos);
			printgen(pond,turtlepos);
		}
		
		MPI_Barrier(MPI_COMM_WORLD);
		
	}




	MPI_Finalize();

	return 0;
}
