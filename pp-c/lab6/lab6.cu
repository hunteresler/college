/*Author: Hunter Esler
 * Course: CSCI 4330
 * Lab number: Lab 6
 * Purpose: This lab will use mpich to calculage integral of sqrt(4-x^2) from 0 to 2 using trapezoidal rule with cuda
 * Due date: 4/22/2019
 * */

#include <stdio.h>
#include <math.h>

//device function
__device__
double func(double x) {
	return (sqrtf(4-x*x));
}

//kernel, grabs left and right of step and uses the custom device func and then stores area in its spot
__global__
void calcarea(float* step, float* areas) {
	
	int here = threadIdx.x;

	float left, right;
	left = here * (*step);
	right = (*step) * (here + 1);
	
	//do ttrapezoid rule
	areas[here] = ((func(left)+func(right))*(*step))/2.0;
}


int main(int argc, char * argv[]) {
	int nproc, i;
	float* step = (float*)malloc(sizeof(float));//the step for each cuda core
	float* stepgpu;//gpu pointer
	float* areasgpu;//gpu pointer
	float* areas;//return areas from gpu
	float sum = 0.0;//total sum

	//grabbing number of steps
	printf("Enter steps: ");
	scanf("%d", &nproc);

	areas = (float*)malloc(nproc*sizeof(float));
	*step = 2.0 / nproc;
	printf("Mallocing and starting function on gpu\n");
	//mallocing on gpu
	cudaMalloc((void**)&stepgpu, sizeof(float));
	cudaMalloc((void**)&areasgpu, nproc * sizeof(float));
	//giving gpu step size
	cudaMemcpy(stepgpu, step, sizeof(float), cudaMemcpyHostToDevice);

	//calling kernel
	//printf("Starting function on gpu\n");
	calcarea<<<1, nproc>>>(stepgpu, areasgpu);

	//copying from gpu to cpu
	cudaMemcpy(areas, areasgpu, nproc * sizeof(float), cudaMemcpyDeviceToHost);
	cudaFree(stepgpu);
	cudaFree(areasgpu);
	free(step);
	
	//sum and print result
	for (i = 0; i < nproc; i++) {
		sum+=areas[i];
	}
	printf("sum: %f\n", sum);

	free(areas);
	return 0;
}
