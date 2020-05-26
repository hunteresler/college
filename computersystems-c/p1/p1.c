#include<stdio.h>
#include<ctype.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {
	
	int fd;

	fd = open("test.txt", O_RDONLY);


	int n = 1;

	int pos = 0;

	while (n != 0) {
		
		unsigned char buff[17];
		int i = 0;
		unsigned char str[1024];
		int s = 0;
		n = read(fd, buff, 16);


		s = s + sprintf(str + s, "%07x: ", pos);

		pos = pos + n;
		for (i = 0; i < n; i++) {
			s = s + sprintf(str + s,"%02x", buff[i]);	
			if (i%2 == 1)
				s = s + sprintf(str + s," ");	
		}

		

		if (n < 16) {
			int times = (16 - n);
			int spaces = 0;
			if (times%2 == 1) {
				spaces+=2;
				times = times - 1;
			}

			times/=2;

			spaces+=(times*5);
			
			for (i = 0; i < spaces; i++) {
				s = s + sprintf(str + s, " ");
			}

		}

		s = s + sprintf(str + s, " ");

		for (i = 0; i < n; i++) {
			if isprint(buff[i]) {
				s = s + sprintf(str + s, "%c", buff[i]);
			} else {
				s = s + sprintf(str + s, ".");
			}
		}

			
		printf("%s\n", str);
		if (n < 16)
			n = 0;	
	}



}
