/*
 *show current system's login information,
 *utmp file stores data, which is a sequence of utmp records
 */
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

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
	if(p->ut_type != USER_PROCESS) {
		return;  //not user, don't show login information
	}
	time_t time_s = p->ut_tv.tv_sec;
	struct tm * login_time = localtime(&time_s);	
	printf("%-9s%-13s%d-%02d-%02d %02d:%02d (%s)\n", p->ut_user, p->ut_line, login_time->tm_year+1900, login_time->tm_mon+1, login_time->tm_mday, login_time->tm_hour, login_time->tm_min, p->ut_host);
}

