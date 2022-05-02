//signal函数测试---注册信号处理函数
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handle(int signo)
{
	printf("signo = %d\n",signo);
}

int main()
{
	signal(SIGALRM,handle);

	struct itimerval tm;
	tm.it_interval.tv_sec = 1;
	tm.it_interval.tv_usec = 0;

	tm.it_value.tv_sec = 3;
	tm.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL,&tm,NULL);

	while(1)
	{
		sleep(1);
	}

	return 0;
}

