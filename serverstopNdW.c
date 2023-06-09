#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<fcntl.h>
int main() {
	int s_sock, c_sock;
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t add;
struct timeval {
   long tv_sec;    /* seconds */
   long tv_usec;   /* microseconds */
};


	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
		printf("Binding failed\n");
		return 0;
	}
	printf("\tServer Up\n Stop and wait protocol ARQ used to send 10 messages \n\n");
	listen(s_sock, 10); 
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
    time_t t1,t2;
	char msg[50]="server message : "; //TO PRINT SERVER MESSAGE ON SCREEN
	char buff[50];
    int flag=0;

fd_set set; //An fd_set is a fixed size buffer. 
  struct timeval timeout;  //declare a timeval for our timer
  int rv;


	for(int i=0;i<10;i++) {
		if(i==6&&flag==0){
		i=15; //TRIES TO SEND FRAME 15, WHICH IS AN INCORRECT SEQNO
		printf("\ncorrupt packet sending simulation\n");		//for simulating corruption
		}
        bzero(buff,sizeof(buff)); //RESET buff
		char buff2[60];
//Goto label qq
		qq:
		bzero(buff2,sizeof(buff2)); //RESET buff2
		strcpy(buff2,msg); //copy the message server message to buff2 variable
		buff2[strlen(msg)]=i+'0'; //Add frame number to server message
		
		printf("Message sent to client :%s \n",buff2);
  
		FD_ZERO(&set); // zero out the read set
//This function initializes the file descriptor set to contain no file descriptors.
  		
FD_SET(c_sock, &set); // // add socket to the read set
// Executing FD_CLR() or FD_SET() with a value of fd that is negative or is equal to or larger than FD_SETSIZE will result in undefined behavior. Moreover, POSIX requires fd to be a valid file descriptor.
  		timeout.tv_sec = 2; //set timeout period as 2 secs
  		timeout.tv_usec = 0; // add timeout period as 0 micro seconds to timer val
		write(c_sock, buff2, sizeof(buff2)); //write the data in buffer to socket
            rv = select(c_sock + 1, &set, NULL, NULL, &timeout); //if rv>o timeout occured
  if(rv == -1)
    perror("select "); // an error has occured 
  else if(rv == 0){
      printf("\nResending message \n");
		if(i==15)
		i=6; //Lost frame 6 labelled as frame 15 is resend again 
        goto qq; // for resending lost frame
} // a timeout occured 
  else
  read(c_sock, buff, sizeof(buff)); //Read message in socket var c_sock to buff  
    
	if(buff[strlen(buff)-1]!=(i%2==0)+'0'){
		printf("\n acknowledgement problem %s\n",buff);
		//problem occurred due to negative ack
goto qq; 	}

		printf("Message from Client: %s\n", buff);
//The message either acknowledgement 0/1 is printed
	}
	close(c_sock);
	close(s_sock);
	return 0;
}
