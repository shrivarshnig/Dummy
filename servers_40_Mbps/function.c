#include "main.h"
int init_sigtimer(struct sigevent sev, timer_t* timer_id){

	/**<Check for NULL pointers*/
	if(timer_id == NULL){
		printf("NULL pointer detected\n");
		return -1;
	}

	/**<Check that the signal number is less than SIGRTMAX and more than SIGRTMIN*/
	if((sev.sigev_signo > SIGRTMAX) | (sev.sigev_signo < SIGRTMIN)){
		printf("Realtime Signal Number is Invalid");
		return -1;
	}

	/**<Creates the timer sourced from the realtime clock*/
	if(timer_create(CLOCK_REALTIME, &sev, timer_id) < 0)
	{
		printf("error in timer_create\n");
		return -1;
	}

	return 1;
}

int init_sigthreadtimer(pid_t thread_id, int signum, timer_t* timer_id){

	struct sigevent sev;	/**<Defines signal to generate on timer expiry*/

	/**<Clear the struct*/
	memset(&sev, 0, sizeof(sev));
	sev.sigev_signo = signum;	/**<Signal number to be generated*/
	sev.sigev_notify = SIGEV_THREAD_ID;	/**<Ensures sigevent like signal is sent
	specifically to the thread mentioned below*/
	sev._sigev_un._tid = thread_id;	/**<Thread to send the signal to*/

	/**<Specify the timer trigger signal settings*/
	if(init_sigtimer(sev, timer_id) == -1){
		return -1;
	}

	return 1;

}
int init_thread_timer(thread_info* thread, int signum)
{

	thread->kthread_ID = syscall(SYS_gettid);
	if(thread->kthread_ID < 0){
		printf("init_thread_timer error\n");
		return -1;
	}

	if(init_sigthreadtimer(thread->kthread_ID, signum, &(thread->timer_ID)) < 0){
		return -1;
	}

	return 1;
}
int start_timer(timer_t timer_id, TIMER_MODE mode, struct timespec* trig_time)
{

	/**<Check for NULL pointer*/
	if(trig_time == NULL){
		printf("NULL pointer detected\n");
		return -1;
	}

	/**<Ensure timer nsec provided is above min limits. Min limit set during HIL testing on Rpi.*/
	if((trig_time->tv_sec == 0) & (trig_time->tv_nsec < MIN_TIMER_VAL)){
		printf("Timer nsec value provided is less than 10us\n");
		return -1;
	}

	/**<Ensure timer nsec provided is below max limits*/
	if(trig_time->tv_nsec > NSEC_MAX_VAL){
		printf("Timer nsec value is larger than 1sec. Use sec for seconds\n");
		return -1;
	}

	struct itimerspec itv;	/**<Stores timer trigger configuration values*/
	memset(&itv, 0, sizeof(struct itimerspec));	/**<Clears struct*/

	if(mode == REPEAT){
		itv.it_value = *trig_time;	/**<When started, the timer will expire at this time*/
		itv.it_interval = *trig_time;	/**<Afterwards, the time will expire at
		this time and keep repeating*/
	}else if(mode == ONESHOT){
		itv.it_value = *trig_time;	/**<By only setting this struct,
		timer only runs once till expiration*/
	}

	/**<Arm the timer*/
	if (timer_settime(timer_id, 0, &itv, NULL) < 0)
	{
		printf("Unable to arm timer\n");
		return (-1);
	}

	return (1);
}

int set_procmask(sigset_t* sev, int signum){

	/**<Block all signals*/
	if(sigfillset(sev) < 0){
		perror(" " );
		return -1;
	}
	if(sigprocmask(SIG_BLOCK, sev, NULL) < 0){
		perror(" " );
		return -1;
	}

	/**<Block all other signals*/
	if(sigemptyset(sev) < 0){
		perror(" " );
		return -1;
	}
	/**<Unblock required signal*/
	if(sigaddset(sev, signum) < 0) {
		perror(" " );
		return -1;
	}

//	if(sigprocmask(SIG_UNBLOCK, sev, NULL) < 0){
//		perror(" " );
//		return -1;
//	}
	return 1;
}