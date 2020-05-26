#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"


void outbuf(char* buf, int buf_size); 


int main (int argc, char** argv)
{
	alarm(60);
	
	int i, rc;

	int stdin_pipe_fds[2], stdout_pipe_fds[2], stderr_pipe_fds[2];
	char buf[100];
	char rbuf[100];

	pipe(stdin_pipe_fds);
	pipe(stdout_pipe_fds);
	pipe(stderr_pipe_fds);

	rc = fork();

	if (rc == -1)
	{
		printf("fork failed\n");
		exit(-1);
	}
	if (rc == 0) // child
	{

		close(stdin_pipe_fds[1]);
		close(stdout_pipe_fds[0]);
		close(stderr_pipe_fds[0]);

		close(0);
		dup(stdin_pipe_fds[0]);
		close(stdin_pipe_fds[0]);
		close(1);
		dup(stdout_pipe_fds[1]);
		close(stdout_pipe_fds[1]);
		
	//	dup2(stdout_pipe_fds[1], fileno(stdout));
		//close(stdout_pipe_fds[1]);

		close(2);
		dup(stderr_pipe_fds[1]);
		close(stderr_pipe_fds[1]);//*/


		//char* const args[] = {"/usr/bin/bc", NULL};
		argv[1] = NULL;

		for (i = 2; i < argc; i++) {
			argv[i-1] = argv[i];
			argv[i] = NULL;
		}
		
		rc = execvp("/usr/bin/bc", argv);



		//printf("jeez man %s\n", strerror(errno));

		exit(0);

	}

	
	//	char* const args[] = {"/usr/bin/bc", "-q", NULL};
		
	//	rc = execve("/usr/bin/bc", args, NULL);


	close(stdin_pipe_fds[0]);
	close(stdout_pipe_fds[1]);
	close(stderr_pipe_fds[1]);

	fd_set set;
	//fd_set set2;
	
	struct timeval tv;
	int done = 0;
	int n;

	FILE* fp;

	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("couldn't read file\n");
		return 1;
	}
	
	memset(rbuf, '\0', 100);

	while (fgets(rbuf, sizeof(rbuf), fp) != NULL)
	{

	//	rbuf[strlen(rbuf)-1] = '\0';
		
		rbuf[100] = '\0';
		printf("in: %s", rbuf);
			
		//strcpy(rbuf, "5*5\0");
		
		
		rc = write(stdin_pipe_fds[1], rbuf, strlen(rbuf));
		//printf("write rc: %d\n", rc);
		
		//memset(buf, '\0', 100);

	//	n = read(stdout_pipe_fds[0], buf, 100);
		//buf[100] = '\0';


		//memset(buf, '\0', 100);
		//n = read(stdout_pipe_fds[0], buf, 100);
		//buf[100] = '\0';
		//if (n > 0) {
			
			//outbuf(buf, 100);
		//}else {

	//	printf("rc: %d\n", rc);
		
	//	printf("after write\n");

			FD_ZERO(&set);
			FD_SET( stdout_pipe_fds[0], &set);

		
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			//printf("selecting\n");
			rc = select(FD_SETSIZE, &set, NULL, NULL, &tv);
			//printf("select done! rc: %d\n", rc);
			if (rc==0)
			{
			//	printf("timeout\n");
				//done = 1;
			} else if (rc < 0) {
			//	printf("else\n");
				//printf("select failed\n");
				//done = 1;
			}
	
			if (FD_ISSET(stdout_pipe_fds[0], &set))
			{
				
			//	printf("got here\n");
				
				memset(buf, '\0', 100);
				n = read(stdout_pipe_fds[0], buf, 100);
				buf[100] = '\0';
				if (n==-1)
				{
					printf("read failed\n");
					//done = 1;
				} else if (n==0)
				{
				//	done = 1;
				//	printf("n = 0\n");
				} else {
					outbuf(buf, 100);
				}
			} else {
			//	printf("lse\n");
			}
		//}
		memset(rbuf, '\0', 100);
		printf("\n");

	}

}


void outbuf(char* buf, int buf_size) { 
	int i;
	//printf("yaaa\n");
	int x = -1;
	int y = 0;
	for (i = 0; i < buf_size; i++) {
		if (buf[i]=='\0' || buf[i]=='\n') {
			if (x < 0 && buf[i]=='\0')
				break;
			else {
				if (x > 0)
					printf("bc: %.*s\n", x, buf + y);
				x = 0;
				if (buf[i]=='\n')
					y = i+1;
				else if (buf[i]=='\0')
					break;
			}
		} else {
			x+=1;
			if (x==0)
				x+=1;
		}
					
	}

}

