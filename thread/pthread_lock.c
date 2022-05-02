//线程同步
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define NUM 10000
int number = 0;

//定义一把锁
pthread_mutex_t mutex;

//线程执行函数
void *mythread1(void *arg)
{
	int i = 0;
	int n;
	for(i = 0; i < NUM; ++i)
	{
		pthread_mutex_lock(&mutex);

		n = number;
		n++;
		number = n;
		printf("1:[%d]\n",number);
		
		pthread_mutex_unlock(&mutex);
	}
}

void *mythread2(void *arg)
{
	
	int i = 0;
	int n;
	for(i = 0; i < NUM; ++i)
	{
		pthread_mutex_lock(&mutex);
		n = number;
		n++;
		number = n;
		printf("2:[%d]\n",number);
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	//互斥锁初始化
	pthread_mutex_init(&mutex, NULL);

	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	//                      void *(*start_routine) (void *), void *arg);
	//创建子线程
	pthread_t thread1;
	int ret = pthread_create(&thread1, NULL, mythread1, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	pthread_t thread2;
	ret = pthread_create(&thread2, NULL, mythread2, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("number = %d",number);

	//目的是为了让子线程能够执行起来
	//sleep(1);

	//释放互斥锁
	pthread_mutex_destroy(&mutex);

	return 0;
}

