/*
 *show current system's login information,
 *utmp file stores data, which is a sequence of utmp records
 */
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BUFFERSIZE 10

void show_record(struct utmp * p);

int main(int argc, char * argv[])
{
	struct utmp records[BUFFERSIZE]; // use buffer tech
	int fd; //file descriptor
	int count;	
	int i;

	fd = open("/var/run/utmp", O_RDONLY);	
	if(fd == -1) {
		printf("open file error\n");
		return 1;
	}

	while(count = read(fd, records, sizeof(records))) {
		for(i=0; i<count/sizeof(struct utmp); ++i) {
			show_record(&records[i]);	
		}
	}

	//must close the utmp file
	close(fd);
	return 0;
}

void show_record(struct utmp * p)
{
	if(p->ut_type != USER_PROCESS) {
		return;  //not user, don't show login information
	}
	time_t time_s = p->ut_tv.tv_sec;
	struct tm * login_time = localtime(&time_s);	
	printf("%-9s%-13s%d-%02d-%02d %02d:%02d (%s)\n", p->ut_user, p->ut_line, login_time->tm_year+1900, login_time->tm_mon+1, login_time->tm_mday, login_time->tm_hour, login_time->tm_min, p->ut_host);
}

