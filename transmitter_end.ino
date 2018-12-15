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
    const char *msg = "150";
    /* 
    HERE AS U CAN OBSERVE THERE IS NO. '150' STORED IN COMPILE_TIME IN *msg, IN IT '1' DENOTES THE LANE_ID, FOR WHICH THE SPEED LIMIT IS CONSIDERED
        AND '50' IS THE MAX. ALLOWED SPEED IN THAT LANE, IT WILL BE SEPERATED AT RECEIVER END. 
        */
        
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}

/*
	THIS LOOP WILL CONTINOUSLY BROADCAST THIS SPEED LIMIT  */
