
#define CH_A 12 // Motore A Pin
#define CH_B 13 // Motore A Pin

#define BK_A 9
#define BK_B 8

#define SPIN_A 3
#define SPIN_B 11

#define LED 10

#define FADE 5
#define FADE_TIME 15

#define FORWARD HIGH
#define BACKWARD LOW

#define MOTOR_STEP 500

int brightness=0;

void setup()
{
	Serial.begin(9600);
	pinMode(CH_A, OUTPUT);
	pinMode(CH_B, OUTPUT);

	pinMode(BK_A, OUTPUT);
	pinMode(BK_B, OUTPUT);

	pinMode(LED, OUTPUT);
}
/**** LED FADING PART ---- LED WILL BE CONNECTED TO PIN 13 ********/


void bright(int value)
{
	if (brightness > value )
	{
		while(brightness > value || brightness >=0 )
		{
			analogWrite(LED, brightness);
			delay(FADE_TIME);
			brightness++;
		}
	}
	else
	{
		while(brightness < value || brightness <=255 )
		{
			analogWrite(LED, brightness);
			delay(FADE_TIME);
			brightness--;
		}
	
	}
}

void led_raise_full(int stop) // useful to stop to half
{
	int b;
	for (b=0;b<=stop;b++)
	{
		analogWrite(LED, b);
		delay(FADE_TIME);
	}
}

void led_low_full(int stop) // useful to stop to half
{
	int b;
	for (b=255;b>=stop;b--)
	{
		analogWrite(LED, b);
		delay(FADE_TIME);
	}

}

void led_low_half(int stop)
{
	int b;
	for (b=125;b>=stop;b--)
	{
		analogWrite(LED, b);
		delay(FADE_TIME);
	}
}

void led_raise_half(int stop)
{
	int b;
	for (b=125;b<=stop;b++)
	{
		analogWrite(LED, b);
		delay(FADE_TIME);
	}
}
/*
void fade(int diff)
{
	while( brightness >= 0 && brightness > brightness-diff)
	{
		analogWrite(LED, brightness);
		brightness=brightness - FADE;
	}
	delay(FADE_TIME);
}
*/
/******* END LED PART ******/


/***** MOTOR FROM MOTOR SHIELD PART ***************/

void motor_a(int speed, int direction, int step)
{
	
	digitalWrite(CH_A, HIGH);
	digitalWrite(BK_A, LOW);
	analogWrite(SPIN_A, speed);
	delay(step * MOTOR_STEP);
	digitalWrite(BK_A, HIGH);
}

void motor_b(int speed, int direction, int step)
{
	digitalWrite(CH_B, HIGH);
	digitalWrite(BK_B, LOW);
	analogWrite(SPIN_B, speed);
	delay(step * MOTOR_STEP);
	digitalWrite(BK_B, HIGH);
}


/****** END MOTOR SHIELD PART ***********/

void test(char c)
{
//	bright(255);
//	led_raise_full(255);
//	led_low_full(0);
//	led_raise_full(125);
//	led_low_half(0);
	if (c =='l') led_raise_full(100);
//	led_low_full(0);
//	bright(0);
	if(c=='a') motor_a(200, FORWARD, 2);
	if (c=='b') motor_b(200, FORWARD, 2);	
	if(c=='o') led_low_half(0);
//	motor_a(120, BACKWARD, 2);
//	delay(1000);
//	motor_b(120, BACKWARD, 2);
}
void loop()
{
	int numBytes=0;
	while (1)
	{	
		if((numBytes=Serial.available())>0)
		{
			char buff;
			buff=(char)Serial.read();
			Serial.println(buff);
			test(buff);

		}
		delay(10);
	}
}
