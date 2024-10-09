

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define BUFFER_SIZE 2048
#define FREQUENCY1 5
#define FREQUENCY2 61
#define FREQUENCY3 1000
#define FREQUENCY4 3000
#define FREQUENCY5 5000
#define FREQUENCY6 10000
#define FREQUENCY7 20000 


int main()
{
long int data_rate_bps1,data_rate_bps2,data_rate_bps3,data_rate_bps4,data_rate_bps5,data_rate_bps6,data_rate_bps7,data_rate_bps8,
data_rate_bps9,data_rate_bps10,data_rate_bps11,data_rate_bps12,data_rate_bps13,data_rate_bps14,data_rate_bps15;
long total_data_rate_bps;

long int bytes1,bytes2,bytes3,bytes4,bytes5,bytes6,bytes7,bytes8,bytes9,bytes10,bytes11,bytes12,bytes13,bytes14,bytes15;

data_rate_bps1 = (BUFFER_SIZE * 8 * FREQUENCY1)/8;
printf("data_rate_1 is %ld\n",data_rate_bps1);
bytes1=data_rate_bps1/8;
printf("bytes_1 is %ld\n",bytes1);

data_rate_bps2 = (BUFFER_SIZE * 8 * FREQUENCY2)/8;
printf("data_rate_2 is %ld\n",data_rate_bps2);
bytes2=data_rate_bps2/8;
printf("bytes_2 is %ld\n",bytes2);


data_rate_bps3 = (BUFFER_SIZE * 8 * FREQUENCY3)/8;
printf("data_rate_3 is %ld\n",data_rate_bps3);
bytes3=data_rate_bps3/8;
printf("bytes_3 is %ld\n",bytes3);


data_rate_bps4 = (BUFFER_SIZE * 8 * FREQUENCY4)/8;
printf("data_rate_4 is %ld\n",data_rate_bps4);
bytes4=data_rate_bps4/8;
printf("bytes_4 is %ld\n",bytes4);


data_rate_bps5 = (BUFFER_SIZE * 8 * FREQUENCY5)/8;
printf("data_rate_5 is %ld\n",data_rate_bps5);
bytes5=data_rate_bps5/8;
printf("bytes_5 is %ld\n",bytes5);


data_rate_bps6 =( BUFFER_SIZE * 8 * FREQUENCY6)/8;
printf("data_rate_6 is %ld\n",data_rate_bps6);
bytes6=data_rate_bps6/8;
printf("bytes_6 is %ld\n",bytes6);



data_rate_bps7 = (BUFFER_SIZE * 8 * FREQUENCY7)/8;
printf("data_rate_7 is %ld\n",data_rate_bps7);
bytes7=data_rate_bps7/8;
printf("bytes_7 is %ld\n",bytes7);



// data_rate_bps8 = (BUFFER_SIZE * 8 * FREQUENCY8)/8;
// printf("data_rate_8 is %ld\n",data_rate_bps8);
// bytes8=data_rate_bps8/8;
// printf("bytes_8 is %ld\n",bytes8);



// data_rate_bps9 = (BUFFER_SIZE * 8 * FREQUENCY9)/8;
// printf("data_rate_9 is %ld\n",data_rate_bps9);
// bytes9=data_rate_bps9/8;
// printf("bytes_9 is %ld\n",bytes9);



// data_rate_bps10 = (BUFFER_SIZE * 8 * FREQUENCY10)/8;
// printf("data_rate_10 is %ld\n",data_rate_bps10);
// bytes10=data_rate_bps10/8;
// printf("bytes_10 is %ld\n",bytes10);



// data_rate_bps11 = ( BUFFER_SIZE* 8 * FREQUENCY11)/8;
// printf("data_rate_11 is %ld\n",data_rate_bps11);
// bytes11=data_rate_bps11/8;
// printf("bytes_11 is %ld\n",bytes11);



// data_rate_bps12 = (BUFFER_SIZE * 8 * FREQUENCY12)/8;
// printf("data_rate_12 is %ld\n",data_rate_bps12);
// bytes12=data_rate_bps12/8;
// printf("bytes_12 is %ld\n",bytes12);



// data_rate_bps13 = (BUFFER_SIZE * 8 * FREQUENCY13)/8;
// printf("data_rate_13 is %ld\n",data_rate_bps13);
// bytes13=data_rate_bps13/8;
// printf("bytes_13 is %ld\n",bytes13);




total_data_rate_bps=
 data_rate_bps1
+data_rate_bps2
 +data_rate_bps3+
 data_rate_bps4
 +data_rate_bps5
+data_rate_bps6
+data_rate_bps7;
+data_rate_bps8
+data_rate_bps9;
//  +data_rate_bps10;
// +data_rate_bps11

// +data_rate_bps12
// +data_rate_bps13;

long int total_bytes_1=
bytes1
+bytes2
+bytes3
+
bytes4
+bytes5
+bytes6
+bytes7;
// +bytes8
// +bytes9;
// +bytes10;
// +bytes11
// +bytes12
// +bytes13;

long int total_bytes=total_data_rate_bps/8;

printf("total_data_rate is %ld\n",total_data_rate_bps);
printf("total_bytes is %ld\n",total_bytes);
printf("total_bytes_1 is %ld\n",total_bytes_1);

return 0;
}