/* Author: Garrett Scholtes
 * Date:   2015-11-17-2015
 * 
 * Lab6 - CS4029
 * 
 * This program serves to test the character device at /dev/interface
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_SIZE 100

int main(int argc, char **argv) {
	int fd;
	fd = open("/dev/interface", O_RDWR);

	if(argc == 2 && !strcmp("read", argv[1])) {
		char read_buf[BUFF_SIZE];
		printf("Reading...\n");

		read(fd, read_buf, sizeof(read_buf));
		printf("Success: \"%s\"\n", read_buf);
	} else if(argc == 3 && !strcmp("write", argv[1])) {
		int string_size = strlen(argv[2]);
		// Set the buffer to contain all NULL characters
		// so that when we read, we only print out the amount
		// of characters written in the last write
		char write_buf[BUFF_SIZE] = {0};
		printf("Writing string of length %d...\n", string_size);

		if(string_size > BUFF_SIZE) {
			printf("ABORT: strings longer than %d bytes not allowed\n", BUFF_SIZE);
			return;
		}

		strncpy(write_buf, argv[2], string_size);
		write(fd, write_buf, BUFF_SIZE);
		printf("Success!\n");
	} else {
		printf("Usage:\n");
		printf("    app read         - Gets characters from /dev/interface\n");
		printf("    app write STRING - Writes STRING to /dev/interface\n");
		printf("STRING must be under %d characters\n", BUFF_SIZE);
		printf("/dev/interface must be tied to our character device\n");
	}

	close(fd);
	return 0;
}