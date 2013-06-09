/*
  FELIX SPINE
  Cosimo Iaia <cosimo.iaia@gmail.com> Tue May 28 2013

*/

#include<stdio.h>
#include<adk.h>

/* Motor Shield */

#define CH_A 12 // Motore A Pin
#define CH_B 13 // Motore A Pin

#define BK_A 9 // Freno A
#define BK_B 8 // Freno B

#define SPIN_A 3 // DIREZIONE A
#define SPIN_B 11 // DIREZIONE B

/* END MOTOR SHIELD */

/* LED */
#define LED 10	// OCCHI

#define FADE 5
#define FADE_TIME 15
#define IN 1
#define OUT -1
#define BRIGHTMAX 255

/* GENERAL MOTORS */
#define FORWARD HIGH
#define BACKWARD LOW

#define MOTOR_STEP 500

#define M1_R 4
#define M1_L 5
#define M2_R 6
#define M2_L 7
#define M3_R 23
#define M3_L 22
#define M4_R 25
#define M4_L 24


char applicationName[] = "Felix's Brain";
char accessoryName[] = "Felix";
char companyName[] = "Ommim Mad Inc.";

char versionNumber[] = "0.1";
char serialNumber[] = "1";
char url[] = "http://www.cosimoiaia.de/felix_brain.apk";

int brightness;
USBHost Usb;
ADK adk(&Usb, companyName, applicationName, accessoryName,versionNumber,url,serialNumber);

void setup()
{
	cpu_irq_enable();
	Serial.begin(9600);
	pinMode(CH_A, OUTPUT);
	pinMode(CH_B, OUTPUT);

	pinMode(BK_A, OUTPUT);
	pinMode(BK_B, OUTPUT);


	pinMode(M1_R, OUTPUT);
	pinMode(M1_L, OUTPUT);
	pinMode(M2_R, OUTPUT);
	pinMode(M2_L, OUTPUT);
	pinMode(M3_R, OUTPUT);
	pinMode(M3_L, OUTPUT);
	pinMode(M4_R, OUTPUT);
	pinMode(M4_L, OUTPUT);


	digitalWrite(M1_R, LOW);
	digitalWrite(M1_L, LOW);
	digitalWrite(M2_R, LOW);
	digitalWrite(M2_L, LOW);
	digitalWrite(M3_R, LOW);
	digitalWrite(M3_L, LOW);
	digitalWrite(M4_R, LOW);
	digitalWrite(M4_L, LOW);

	pinMode(LED, OUTPUT);
	brightness=0;
}

/**** LED FADING PART ---- LED WILL BE CONNECTED TO PIN 13 ********/


void fade(int diff, int fade)
{
	int i;

	for(i=0;i<diff;i++)
	{
		if( brightness >= 0 || brightness <= BRIGHTMAX)
		{
			analogWrite(LED, brightness);
			brightness=brightness + (i*fade);
			delay(FADE_TIME);
		}
	}
}
/******* END LED PART ******/

/******* GENERAL MOTORS *******/

void servo1(int direction, int step)
{	
	int channel=M1_R;
	
	if(direction != FORWARD) channel=M1_L;

	digitalWrite(channel, HIGH);
	delay(step * MOTOR_STEP); 
	digitalWrite(channel, LOW);
}

void servo2(int direction, int step)
{	
	int channel=M2_R;
	
	if(direction != FORWARD) channel=M2_L;

	digitalWrite(channel, HIGH);
	delay(step * MOTOR_STEP); 
	digitalWrite(channel, LOW);
}

void servo3(int direction, int step)
{	
	int channel=M3_R;
	
	if(direction != FORWARD) channel=M3_L;

	digitalWrite(channel, HIGH);
	delay(step * MOTOR_STEP); 
	digitalWrite(channel, LOW);
}
void servo4(int direction, int step)
{	
	int channel=M4_R;
	
	if(direction != FORWARD) channel=M4_L;

	digitalWrite(channel, HIGH);
	delay(step * MOTOR_STEP); 
	digitalWrite(channel, LOW);
}

/* END GENERAL MOTORS */

/***** MOTOR FROM MOTOR SHIELD PART ***************/

void motor_right(int speed, int direction, int step)
{
	
	digitalWrite(CH_A, direction);
	digitalWrite(BK_A, LOW);
	analogWrite(SPIN_A, speed);
	delay(step * MOTOR_STEP);
	digitalWrite(BK_A, HIGH);
}

void motor_left(int speed, int direction, int step)
{
	digitalWrite(CH_B, direction);
	digitalWrite(BK_B, LOW);
	analogWrite(SPIN_B, speed);
	delay(step * MOTOR_STEP);
	digitalWrite(BK_B, HIGH);
}

void walk(int speed, int direction, int step)
{
	digitalWrite(CH_A, direction);
	digitalWrite(CH_B, direction);
	digitalWrite(BK_A, LOW);
	digitalWrite(BK_B, LOW);
	analogWrite(SPIN_A, speed);
	analogWrite(SPIN_B, speed);
	digitalWrite(BK_A, LOW);
	digitalWrite(BK_B, LOW);
	delay(step * MOTOR_STEP);
	digitalWrite(BK_A, HIGH);
	digitalWrite(BK_B, HIGH);
}

/****** END MOTOR SHIELD PART ***********/

void test(char c)
{
	if (c =='l')  /* LED */
	{
		fade(150, IN);
		delay(500);
		fade(150, OUT);
        }
	if(c=='w') walk(500, FORWARD, 1);
	if(c=='s') walk(500, BACKWARD, 1);
	if(c=='a') motor_left(500, FORWARD, 1);
	if(c=='d') motor_right(500, FORWARD, 1);
	if(c=='1') 
	{
		servo1(FORWARD, 5);
		servo1(BACKWARD, 5);
	}
	if(c=='2') 
	{
		servo2(FORWARD, 5);
		servo2(BACKWARD, 5);
	}
	if(c=='3') 
	{
		servo3(FORWARD, 5);
		servo3(BACKWARD, 5);
	}
	if(c=='4') 
	{
		servo4(FORWARD, 5);
                delay(1000);
		servo4(BACKWARD, 5);
	}
	if(c=='f') demo();

}

void demo()
{
	delay(10000);
	walk(500, FORWARD, 5);
	delay(1000);
	motor_left(500, FORWARD, 2);
	delay(500);
	motor_right(500, FORWARD, 2);
	servo1(FORWARD, 5);
	servo2(FORWARD, 5);
	servo4(FORWARD, 5);
	servo3(FORWARD, 5);
	delay(1000);
	servo1(BACKWARD, 5);
	servo2(BACKWARD, 5);
	servo3(BACKWARD, 5);
	walk(500, BACKWARD, 5);
}

void loop()
{
	Usb.Task();
	int numBytes=0;
	uint8_t buf[1];
	uint32_t nbread = 0;
	
	if (adk.isReady())
	{
		adk.read(&nbread, 255, buf);
		if (nbread > 0)
		{
			test((char)buf[0]);
		}
	}
	else if((numBytes=Serial.available())>0)
	{
		char buff;
		buff=(char)Serial.read();
		Serial.println(buff);
		test(buff);
	}
}
