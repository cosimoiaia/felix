
#define CH_A 12 // Motore A Pin
#define CH_B 13 // Motore A Pin

#define BK_A 9
#define BK_B 9

#define SPIN_A 3
#define SPIN_B 11

#define LED 10

#define FADE 5
#define FADE_TIME 30

#define FORWARD HIGH
#define BACKWARD LOW

int brightness=0;

void setup()
{
	Serial.begin(9600);
	pinMode(CH_A, OUTPUT);
	pinMode(CH_B, OUTPUT);

	pinMode(BK_A, OUTPUT);
	pinMode(BK_A, OUTPUT);

	pinMode(LED, OUTPUT);
}
/**** LED FADING PART ---- LED WILL BE CONNECTED TO PIN 13 ********/
void bright(int diff)
{
	while( brightness <= 255 && brightness <= brightness+diff)
	{
		analogWrite(LED, brightness);
		brightness=brightness + FADETIME;
	}
	delay(FADE_TIME);
}

void fade(int diff)
{
	while( brightness >= 0 && brightness > brightness-diff)
	{
		analogWrite(LED, brightness);
		brightness=brightness - FADE;
	}
	delay(FADE_TIME);
}

/******* END LED PART ******/


/***** MOTOR FROM MOTOR SHIELD PART ***************/

void motor_a(int speed, int direction, int step)
{
	digitalWrite(CH_A, direction);
	digitalWrite(BK_A, LOW);
	analogWrite(SPIN_A, speed%255);
	delay(step*FADE_TIME);
	digitalWrite(BK_A, HIGH);
}

void motor_b(int speed, int direction, int step)
{
	digitalWrite(CH_B, direction);
	digitalWrite(BK_B, LOW);
	analogWrite(SPIN_B, speed%255);
	delay(step*FADE_TIME);
	digitalWrite(BK_B, HIGH;
}


/****** END MOTOR SHIELD PART ***********/
void loop()
{
	int numBytes=0;
	while (1)
	{	
		if((numBytes=Serial.available())>0)
		{
			int i;
			char buff[numBytes];
			for(i=0;i<numBytes;i++)
			{
				buff[i]=Serial.read();
			}
			Serial.println(i);
		}
		delay(10);
	}
}
