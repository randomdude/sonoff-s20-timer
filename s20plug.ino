//
// This simple little project will turn a Sonoff S20 smart plug into a simple timer.
// Press the power button on the S20 to turn the plug on for one hour.
//

#define PIN_BUTTON 0
#define PIN_GREEN_LED 13
#define PIN_RELAY_AND_BLUE_LED 12

void setup() 
{
	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_GREEN_LED, OUTPUT);
	pinMode(PIN_RELAY_AND_BLUE_LED, OUTPUT);

	digitalWrite(PIN_GREEN_LED, HIGH);
	digitalWrite(PIN_RELAY_AND_BLUE_LED, LOW);

	// Let the user know we're up OK
	digitalWrite(PIN_GREEN_LED, LOW);
	delay(500);
	digitalWrite(PIN_GREEN_LED, HIGH);
}

void loop() 
{
	bool isOn = false;
	unsigned long timeS = 0;
	unsigned long turnoffTime = timeS;
	while(true)
	{
		ESP.wdtFeed();
		
		unsigned long delaystart = millis();
		while(millis() < delaystart + 1000)
		{
			if (isOn == false)
			{
				if (digitalRead(PIN_BUTTON) == LOW)
				{
					turnoffTime = timeS + (60 * 60);
					digitalWrite(PIN_RELAY_AND_BLUE_LED, HIGH);
					isOn = true;
				}
			}
		}
		
		timeS++;
		
		if (isOn == true)
		{
			if (turnoffTime < timeS)
			{
				digitalWrite(PIN_GREEN_LED, HIGH);
				digitalWrite(PIN_RELAY_AND_BLUE_LED, LOW);
				isOn = false;
			}
			else
			{
				digitalWrite(PIN_GREEN_LED, timeS % 2);
			}
		}
	}
}
