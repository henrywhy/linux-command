/*
 *show current system's login information,
 *utmp file stores data, which is a sequence of utmp records
 */
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>

void show_record(struct utmp * p);

int main(int argc, char * argv[])
{
	struct utmp cur_record;
	int buffer_size = sizeof(cur_record);
	int fd; //file descriptor

	fd = open("/var/run/utmp", O_RDONLY);	
	if(fd == -1) {
		printf("open file error\n");
		return 1;
	}

	while(read(fd, &cur_record, buffer_size)) {
		show_record(&cur_record);	
	}

	//must close the utmp file
	close(fd);
	return 0;
}

void show_record(struct utmp * p)
{
	printf("%s   %s\n", p->ut_user, p->ut_host);
}

