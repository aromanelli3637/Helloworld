#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <linux/random.h>
#include <sys/random.h>
#include <unistd.h>

#define NUMBER_OF_THREADS     20

pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;
pthread_mutex_t input_lock;
int input;

void *getinput(void *threadid)
{	
	/* lock input*/
	pthread_mutex_lock(&input_lock);

	/* get user input */
	printf("Please enter a number : ");
	scanf("%d",&input);

	/* signal and unlock input */
	pthread_cond_broadcast(&cond_var);
	pthread_mutex_unlock(&input_lock);
	pthread_exit(NULL);
}

void *printrandom(void *threadid)
{
	long tid;
	tid = (long)threadid;

	/* wait for write thread */
	pthread_cond_wait(&cond_var,&input_lock);
	pthread_mutex_unlock(&input_lock);
	
	/* generate random number */
	int buf=0;
	int rand=0;
	getrandom(&buf, sizeof(buf), GRND_RANDOM);
	rand = abs(buf % 100);
		
	usleep(rand*1000);
	printf("Random num = %d -- threadID #%ld!\n",rand+input,tid);
	pthread_exit(NULL);
}

int main (void)
{
	pthread_t threads[NUMBER_OF_THREADS];
	int return_code;

	for(long t=0; t<NUMBER_OF_THREADS; t++)
	{	
		if(t==NUMBER_OF_THREADS-1) {
			printf("In main: creating write thread %ld\n", t);
			return_code = pthread_create(&threads[t], NULL, &getinput, (void *)t);
		}
		else
		{
			printf("In main: creating print thread %ld\n", t);
			return_code = pthread_create(&threads[t], NULL, &printrandom, (void *)t);
		}
		
		/* check error code */
		if (return_code)
		{
			printf("ERROR; return code from pthread_create() is %d\n", return_code);
			exit(-1);
		}
	}
	
	/* wait for all threads by joining them */
	void *retval;		
	for(long t=0; t<NUMBER_OF_THREADS; t++)
	{
		pthread_join(threads[t],&retval);
	}
	
	pthread_exit(NULL);
}

