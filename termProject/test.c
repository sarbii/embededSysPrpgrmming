#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

//#include <unistd.h>


int main() {
//int main(int argc, char** argv) {
	char buf[BUFSIZ];
	char i = 0;
	unsigned int data1;
	unsigned int data2;
	int fd_sensor1 = -1;
	int fd_sensor2 = -1;
	int count =0;
	int fd_led=-1;
	memset(buf, 0, BUFSIZ);




	fd_sensor1 = open("/dev/sensor", O_RDWR);
	//fd_sensor2 = open("/dev/sensor2", O_RDWR);
	fd_led = open("/dev/gpioled", O_RDWR);
	
	printf("fd_sensor1 = %d\n", fd_sensor1);
	printf("fd_led = %d\n", fd_led);
//	printf("%d\n", strlen(argv[1]));
//	printf("%s\n", argv[1]);
	if(0 >= fd_sensor1){
		printf("Open fail!\n");
		exit(0);
	}

	if(0 >= fd_led){
		printf("Open fail led!\n");
		exit(0);
	}
	
	while(count <18){
		ioctl(fd_sensor1,NULL,&data1);
	//	ioctl(fd_sensor2,NULL,&data2);
		
		printf("distance from sensor1 is %dcm\n", data1);
	//	printf("distance from sensor2 is %dcm\n", data2);
		/*if(data1 >= data2){
		  	data1 = data2
		  } */
		if(data1<= 30){
			printf("led ON!\n");
			write(fd_led,"1",1,NULL);
			read(fd_led, buf,0, NULL);
		}else{
			printf("led off!\n");
			write(fd_led,"0",1,NULL);
			read(fd_led, buf, 1, NULL);
		}
		count++;
		sleep(2);
	}



	close(fd_sensor1);
	close(fd_led);

	return 0;

}
