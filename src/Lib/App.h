#pragma once
#include <Arduino.h>

class App
{
public:
	unsigned long TimeAsMilliSeconds()
	{
		return millis();
	}

	double TimeAsSeconds()
	{
		return TimeAsMilliSeconds() / 1000;
	}

	double TimeAsMinutes()
	{
		return TimeAsSeconds() / 60;
	}

	double TimeAsHours()
	{
		return TimeAsMinutes() / 60;
	}

	double TimeAsDays()
	{
		return TimeAsHours() / 24;
	}
};