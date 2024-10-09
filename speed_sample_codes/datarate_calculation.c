

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define BUFFER_SIZE  8192 
#define FREQUENCY1 1
#define FREQUENCY2 10
#define FREQUENCY3 25
#define FREQUENCY4 50
#define FREQUENCY5 61
#define FREQUENCY6 100
#define FREQUENCY7 125
#define FREQUENCY8 300
#define FREQUENCY9 500
#define FREQUENCY10 6000
#define FREQUENCY11 10000
#define FREQUENCY12 20000


int main()
{
long data_rate_bps1,data_rate_bps2,data_rate_bps3,data_rate_bps4,data_rate_bps5,data_rate_bps6,data_rate_bps7,data_rate_bps8,
data_rate_bps9,data_rate_bps10,data_rate_bps11,data_rate_bps12;
long total_data_rate_bps;

data_rate_bps1 = (BUFFER_SIZE * 8 * FREQUENCY1)/8;
printf("data_rate_1 is %ld\n",data_rate_bps1);

data_rate_bps2 = (BUFFER_SIZE * 8 * FREQUENCY2)/8;
printf("data_rate_2 is %ld\n",data_rate_bps2);

data_rate_bps3 = (BUFFER_SIZE * 8 * FREQUENCY3)/8;
printf("data_rate_3 is %ld\n",data_rate_bps3);


data_rate_bps4 = (BUFFER_SIZE * 8 * FREQUENCY4)/8;
printf("data_rate_4 is %ld\n",data_rate_bps4);

data_rate_bps5 = (BUFFER_SIZE * 8 * FREQUENCY5)/8;
printf("data_rate_5 is %ld\n",data_rate_bps5);

data_rate_bps6 =( BUFFER_SIZE * 8 * FREQUENCY6)/8;
printf("data_rate_6 is %ld\n",data_rate_bps6);

data_rate_bps7 = (BUFFER_SIZE * 8 * FREQUENCY7)/8;
printf("data_rate_7 is %ld\n",data_rate_bps7);

data_rate_bps8 = (BUFFER_SIZE * 8 * FREQUENCY8)/8;
printf("data_rate_8 is %ld\n",data_rate_bps8);


data_rate_bps9 = (BUFFER_SIZE * 8 * FREQUENCY9)/8;
printf("data_rate_9 is %ld\n",data_rate_bps9);

data_rate_bps10 = (BUFFER_SIZE * 8 * FREQUENCY10)/8;
printf("data_rate_10 is %ld\n",data_rate_bps10);

data_rate_bps11 = (BUFFER_SIZE * 8 * FREQUENCY11)/8;
printf("data_rate_11 is %ld\n",data_rate_bps11);

data_rate_bps12 = (BUFFER_SIZE * 8 * FREQUENCY12)/8;
printf("data_rate_12 is %ld\n",data_rate_bps12);

total_data_rate_bps=data_rate_bps1+data_rate_bps2+data_rate_bps3+data_rate_bps4+data_rate_bps5+data_rate_bps7+data_rate_bps8+
data_rate_bps9+data_rate_bps10+data_rate_bps11+data_rate_bps12;
printf("total_data_rate is %ld\n",total_data_rate_bps);

return 0;
}