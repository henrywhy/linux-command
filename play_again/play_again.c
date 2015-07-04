#include <stdio.h>
#include <termios.h>

//0->yes  1->no
int get_response(const char * question);

int main(int argc, char * argv[])
{
	struct termios original_setting, tmp_setting;
	tcgetattr(0, &original_setting);
	tcgetattr(0, &tmp_setting);
	tmp_setting.c_lflag &= ~ICANON;
	tmp_setting.c_lflag &= ~ECHO;
	tmp_setting.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &tmp_setting);
	
	char question[] = "play again?";
	int response;
	response = get_response(question);
	printf("\n%d\n", response);	

	tcsetattr(0, TCSANOW, &original_setting);
	return 0;
}

int get_response(const char * question)
{
	printf("%s (y/n)", question);
	while(1) {
		switch(getchar()) {
			case 'y' :
			case 'Y' :
				return 0;
			case 'n' :
			case 'N' :
			case EOF :
				return 1;
		}
	}	
}
