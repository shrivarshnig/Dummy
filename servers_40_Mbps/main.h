#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <errno.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <pthread.h>
#include<inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>  
#include <sys/mman.h> 
#include <sys/stat.h> 
#include <time.h>
#include<sys/time.h>
#include<stdatomic.h>
#include<arpa/inet.h>


#define THREAD_NAME_SIZE	20
#define MIN_TIMER_VAL	10000		/**<10us minimum expiration time*/
#define	NSEC_MAX_VAL	999999999
typedef enum{
	ONESHOT,
	REPEAT,
}TIMER_MODE;


typedef struct{
pthread_t pthread_ID;	/*!< Posix thread ID for generated thread */

	//Optional Parameters
	pid_t kthread_ID;	/*!< Kernel thread ID for generated thread */
	char name[THREAD_NAME_SIZE];	/**<Assign this thread a name if scheduled by timer*/

	//If used along with a timer
	timer_t timer_ID;	/*!< Timer ID used to schedule thread */
	struct timespec trig_time; /*!< Interval time for timer trigger */
}thread_info;
static void *handle_tcp_channel(void *data);
int init_thread_timer(thread_info* thread, int signum);
int start_timer(timer_t timer_id, TIMER_MODE mode, struct timespec* trig_time);
int set_procmask(sigset_t* sev, int signum);