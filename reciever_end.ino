#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup()
{
    Serial.begin(9600);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    int x=1000;
    int yr_speed;
    int speed_limit=0,lane,maxspeed;
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    serial.print("enter yr speed");
    yr_speed=serial.read();
    if (driver.recv(buf, &buflen))
    {
      for(i=0;i<3;i++) 
	{
		speed_limit+= (buf[i]-'0')*x;
		x=x/10;
	}
	
	speed_limit/=10;
	lane=speed_limit/100;
	maxspeed=speed_limit%100;
	serial.print("speed limit is: ");
	serial.print(maxspeed,DEC);
	serial.print("data is for the lane: ");
	serial.print(lane);
	
	if(yr_speed>=maxspeed)
	{
		serial.print("********************* YOU R OVERSPEEDING *************************");
	}
	
	else
	{
		serial.print("You are going with suitable pace, NO_WORRIES");
	}
	        
    }
}
