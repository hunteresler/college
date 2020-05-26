#include <stdio.h>
#include <stdlib.h>

/* include any other required header files here */
#include "signal.h"
#include "wait.h"
#include "unistd.h"
#include "sys/types.h"

int child_done;
void p7test();


/* put CHLD signal handler function here */
void gotChildSignal(int sig) {
	//printf("We got a signal! Signal: %d\n", sig);
	child_done = 1;
}

int main(int argc, char *argv[])
{
    int pid, status;

    alarm(60);

    /* install CHLD signal handler here */
    //printf("Hello, my world!\n");
    signal(SIGCHLD, gotChildSignal);

    child_done = 0;

    if ((pid = fork()) == -1)
    {
        printf("fork failed\n");
        exit(-1);
    }

    if (pid == 0)  // child
    {
        p7test();  // bases its actions on env vars
        exit(0);
    }

    while ( ! child_done)
        ;

    /* obtain child termination/signal/exit info and print it here */
   
    if (wait(&status)==pid)
    {
    	//printf("status: %d\n", status);
	if (WIFEXITED(status)) {
		printf("NORMAL\n%d\n", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
	{
		printf("ABEND\n%d\n", WTERMSIG(status));
	}
    }
	exit(0);
}
