#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"

int server(int sock);

int debug = 0;

int main()
{
	int rc, status, sock[2];
	char buf[64];

	socketpair(AF_UNIX,SOCK_STREAM,0,sock);

	rc = fork();
	if (debug) printf("rc = %d\n", rc);

	if (debug) alarm(10);
	if (debug) printf("made alarm\n");
	if (rc == 0) {
		
		close(sock[0]);
		server(sock[1]);

	} else {
		close(sock[1]);
		
		int done = 0;

		do {		

			memset(buf, '\0', 64);
			//buf[63] = '\0';
			int len = read(sock[0], buf, 64);
			if (len<=0)
			{
				if (debug) printf("Server socket disconnected\n");
				done = 1;
				break;
			}
			
			printf("CLIENT recvd  len %d   msg :%s:\n", len, buf);
			char first = buf[4];
			char last = buf[len-1];
			memset(buf, '\0', 64);
			sprintf(buf, "ack %c%c", first, last);
			write(sock[0], buf, 6);
			
		} while (!done);

		return 0;
		
	}

}










