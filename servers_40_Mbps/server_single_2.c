#include "main.h"
#define BUFFER_SIZE 1024
typedef struct 
{
     struct timespec timestamp;
    char buffer[BUFFER_SIZE];  
   
}telemetry_t;

static int g_index[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
static int ip_port[] = {6321,6322,6323,6324,6325,6326,6327,6328,6329,6330,6331,6332,6333};
static int frequence[] = {5,61,1000,3000,5000,10000,20000};
static char *file_namw[] ={"port_1.csv","port_2.csv","port_3.csv","port_4.csv","port_5.csv","port_6.csv","port_7.csv","port_8.csv","port_9.csv","port_10.csv",
"port_11.csv","port_12.csv","port_13.csv"};
static char *file_namw_80Mbps[] ={"port_1_80.csv","port_2_80.csv","port_3_80.csv","port_4_80.csv","port_5_80.csv","port_6_80.csv","port_7_80.csv","port_8_80.csv","port_9_80.csv","port_10_80.csv",
"port_11_80.csv","port_12_80.csv","port_13_80.csv"};
static int target_rate_bps_1[] = {(5120/8),7808,(1024000/8),384000,640000,(10240000/8),2560000};
static uint64_t current_timestamp_ms1;
static uint64_t difference_timestamp;
long int get_current_time_ms();

int main()
{
    
    if(-1 == prctl(PR_SET_NAME, "TCP_PROC", NULL,NULL,NULL))
	{
		exit(EXIT_FAILURE);
	}
	
    for (int i = 0; i < 7; i++)
	{
		// printf("main process %d\n",getpid());
		/**< If start communicating with the telemtry, if it is enabled.*/
        pthread_t thread_id;

        int status = pthread_create(&thread_id, NULL,handle_tcp_channel, (void*)&g_index[i]);
        pthread_detach(thread_id);
        if (status != 0)
        {
            printf("Unable to initialize thread\n");
            exit(EXIT_FAILURE);
        }
		printf("%d\n",g_index[i]);
        // usleep(1000);
    }
	while (1) 
    {
    	pause();
    }
}

static void *handle_tcp_channel(void *data)
{
	
    int th_index = -1;
	th_index = *((int*)data);
	printf("inside %d\n",th_index);
    thread_info telemetry_threads;

	/**< Some timer stuff.*/
	atomic_store(&(telemetry_threads.kthread_ID), syscall(SYS_gettid));

	char *ip = INADDR_ANY;
    int port = ip_port[th_index];

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    static struct timespec ts_recv, ts_sys2;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to a specific port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

	/**<Defines which signals to wait for */
	sigset_t set;
	
	/**< Use a unique signal number for each thread. */
	int signum = SIGRTMIN + th_index;

	/** Convert the frequency in LUT to period in nanoseconds.*/
	uint64_t period = (uint64_t)(1000000000/frequence[th_index]);
	
	/**< Store the period in the thread info struct. */
	telemetry_threads.trig_time.tv_sec = period/1000000000;
	telemetry_threads.trig_time.tv_nsec = period%1000000000;

	/**< Initialize the timer and bind it to the signal number.*/
	if(init_thread_timer(&telemetry_threads, signum) == -1)
	{
		printf("error\n");
        pthread_exit(NULL);
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
    
    int total_bytes_received_1 = 0;
	/**< Create a buffer of size specified in the LUT*/
    FILE *fd=fopen(file_namw[th_index],"w");
    if(fd==NULL)
    {
        printf("empty file\n");
    }
	telemetry_t receive;
	 while(total_bytes_received_1 < target_rate_bps_1[th_index])
	{
		sigwait(&set, &signum); 
        memset(&receive,'\0',sizeof(telemetry_t));
        ssize_t bytes_received_1 =recv(new_socket,(void*) &receive,sizeof(telemetry_t), 0);
        if(bytes_received_1>0)
        {
            printf("%s\n",receive.buffer);
            // printf("receive-timestamp-%ld\n",receive.timestamp);
            nanosleep(&telemetry_threads.trig_time, NULL);
            total_bytes_received_1 += bytes_received_1;
             ts_recv=receive.timestamp;

            //Calculating the delay 
            clock_gettime(CLOCK_REALTIME, &ts_sys2);
            long long delay_sec = ts_sys2.tv_sec - ts_recv.tv_sec;
            long long delay_nsec = ts_sys2.tv_nsec - ts_recv.tv_nsec;
            long long delay_usec = delay_sec * 1000000 + delay_nsec / 1000; // Convert to microseconds

            // print the result in the files
            fprintf(fd,"buffer %s port  %d Received %ld bytes. Total received: %d bytes Timestamp:%ld Timestamp delay:%lld microseconds\n",receive.buffer,port, bytes_received_1, total_bytes_received_1,get_current_time_ms(),delay_usec);
            fflush(fd);
        }
    }
    close(new_socket);
    close(server_fd);
}
long int get_current_time_ms() 
{
    //log the timestamp
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
