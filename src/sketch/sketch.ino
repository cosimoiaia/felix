
#define CH_A 12 // Motore A Pin
#define CH_B 13 // Motore A Pin

#define BK_A 9
#define BK_B 8

#define SPIN_A 3
#define SPIN_B 11

#define LED 10

#define FADE 5
#define FADE_TIME 15
#define IN 1
#define OUT -1
#define BRIGHTMAX 255

#define FORWARD HIGH
#define BACKWARD LOW

#define MOTOR_STEP 500

int brightness;

void setup()
{
	Serial.begin(9600);
	pinMode(CH_A, OUTPUT);
	pinMode(CH_B, OUTPUT);

	pinMode(BK_A, OUTPUT);
	pinMode(BK_B, OUTPUT);

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
	if(c=='a')   /* ALL */
	{
		fade(BRIGHTMAX, IN);
		walk(200, FORWARD, 2);
		delay(1000);
		walk(200, BACKWARD, 2);
		fade(BRIGHTMAX, OUT);
	}
	if(c=='w') /* WALK */
	{
		walk(200, FORWARD, 2);
		delay(1000);
		walk(200, BACKWARD, 2);
	}
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
