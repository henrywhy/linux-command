#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 512

int main(int argc, char * argv[])
{
	int source_fd;
	int target_fd;
	char buffer[BUFFERSIZE];
	int count;	
	if(argc < 3) {
		printf("source or target file cannot be found\n");
		return 1;	
	}
	
	source_fd = open(argv[1], O_RDONLY);
	target_fd = creat(argv[2], 0644);
	if(source_fd < 0) {
		printf("open source file error!\n");
		return 1;
	}
	if(target_fd < 0) {
		printf("create target file error!\n");
		return 1;	
	}

	//copy content to file
	while(count = read(source_fd, buffer, BUFFERSIZE)) {
		write(target_fd, buffer, count);
	}

	close(source_fd);
	close(target_fd);
	return 0;
}
