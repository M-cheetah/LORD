#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <time.h>
#include <string.h>

void delay(int sec)
{
	int mili=1000*sec;
	clock_t start=clock();
	while(clock()<start+mili);
}

struct mesg_buffer { 
	long mesg_type; 
	char salt[15];
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	char pass_salt[15]="viscabarca";
	int msgid, speed_limit=0,x=1000,i,lane,maxspeed,current=0; 
	
	printf("enter the current speed\n");
	scanf("%d",&current);

	key = ftok("progfile", 65); 

	msgid = msgget(key, 0666 | IPC_CREAT); 

	msgrcv(msgid, &message, sizeof(message), 1, 0); 
	if(strcmp(message.salt,pass_salt)==0)
	{
		
		printf("Data Received is : %s \n", message.mesg_text);

		for(i=0;i<3;i++) 
		{
			speed_limit+= (message.mesg_text[i]-'0')*x;
			x=x/10;
		}

		speed_limit/=10;
		lane=speed_limit/100;
		maxspeed=speed_limit%100;
		printf("\nspeed limit is %d\n", maxspeed);
		printf("data is for the lane %d\n",lane); 

		if(current>=maxspeed)
		{
			printf("\n\n\n********************* YOU R OVERSPEEDING *************************\n\n");
			for(i=0;i<100;i++)
			{
			printf("\a");	
			delay(100);
			}
		}

		else
		{
			printf("\nYou are going with suitable pace, NO_WORRIES\n\n\n");
		}
	}
	else
	{
		printf("FALSE DATA DETECTED");
	}
	msgctl(msgid, IPC_RMID, NULL); 

	return 0; 
} 

