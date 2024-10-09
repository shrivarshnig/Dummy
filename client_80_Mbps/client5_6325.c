#include"main.h"

#define PORT  6325
#define IP ("1.1.1.97")
#define FREQUENCY 5000

#define BUFFER_SIZE 4096
#define TARGET_RATE_MBPS_5 5120000
typedef struct 
{
    struct timespec timestamp;
    char buffer[BUFFER_SIZE];  

   
}telemetry_t;
static long target_rate_bps_5 = 5120000/8;  
static long total_bytes_sent_5= 0;


int main()
{ 
     thread_info telemetry_threads;

	/**< Some timer stuff.*/
	atomic_store(&(telemetry_threads.kthread_ID), syscall(SYS_gettid));

	/**<Defines which signals to wait for */
	sigset_t set;
	
	/**< Use a unique signal number for each thread. */
	int signum = SIGRTMIN + 0;

	/** Convert the frequency in LUT to period in nanoseconds.*/
	 uint64_t  period = (uint64_t)(1000000000/FREQUENCY);
	
	/**< Store the period in the thread info struct. */
	telemetry_threads.trig_time.tv_sec = period/1000000000;
	telemetry_threads.trig_time.tv_nsec = period%1000000000;

	/**< Initialize the timer and bind it to the signal number.*/
	if(init_thread_timer(&telemetry_threads, signum) == -1)
	{
		printf("error\n");
	}

	/**< Start the timer in REPEAT mode*/
	if(start_timer(telemetry_threads.timer_ID, REPEAT, 
					 &(telemetry_threads.trig_time)) == -1)
	{
		printf("error\n");
		pthread_exit(NULL);
	}

	/**< Set the signal mask for this thread*/
	set_procmask(&set, signum);
	int g_timer_count=0;
	/**< Create a buffer of size specified in the LUT*/


    printf("client-5\n");
    socklen_t addr_size;
    struct sockaddr_in ats_clientaddress;
    int sockfd;
    struct timespec sleep_time1 = {0};
    struct timespec trig_time;
    
    addr_size=sizeof(ats_clientaddress); 
    /*Socket creation*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd<0)
    {
      printf("error in socket creation");
    }

    printf("socket creation is successful\n");

    /*Assigning port number and IP_ADDRESS*/
    ats_clientaddress.sin_family = AF_INET;
    ats_clientaddress.sin_addr.s_addr = inet_addr(IP);
    ats_clientaddress.sin_port = htons(PORT);

    /*Connect to the client*/
    if (connect(sockfd, (struct sockaddr *)&ats_clientaddress,sizeof(ats_clientaddress)) == -1) 
    {
        perror("Connection failed");
        exit(1);
    }
    printf("connected successfully\n");
    printf("got successfully\n");
    struct timespec ts_sys5;

     clock_gettime(CLOCK_REALTIME, &ts_sys5);

    telemetry_t sending   ={.buffer="hi"};
    sending.timestamp = ts_sys5;
    while (total_bytes_sent_5 < target_rate_bps_5) 
    {    if(sigwait(&set, &signum) != 0) {
            perror("sigwait");
            return NULL;
        }
        ssize_t bytes_sent_5 = send(sockfd, (void *)&sending, sizeof(telemetry_t), 0);
        if(bytes_sent_5<=0)
        {
            perror("Error in receiving\n");

            exit(1);

        }
        total_bytes_sent_5+=bytes_sent_5;
        printf("%s\n",sending.buffer);
     printf("Timestamp sent: %lld seconds, %lld nanoseconds\n", (long long)ts_sys5.tv_sec, (long long)ts_sys5.tv_nsec);
    }
    printf("Sent for port 2 %ld bytes at %d Mbps.\n", total_bytes_sent_5, TARGET_RATE_MBPS_5);

}
        