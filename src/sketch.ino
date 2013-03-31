
void setup()
{
	Serial.begin(9600);
}

void loop()
{
	char val='c';
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
		}
	//	val = Serial.read();
		delay(10);
		if (val != -1)
		{
			Serial.println(val);
		}
		delay(10);
	}
}
