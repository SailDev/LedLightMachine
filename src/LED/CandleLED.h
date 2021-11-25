#pragma once
#include "LED.h"
#include "Effect.h"
#include "Lib/StringTools.h"

class CandleLED : public LED
{
private:
	StringTools _stringTools = StringTools();

public:
	CandleLED(string id, int channel, int gpioPin) : LED(id, channel, gpioPin)
	{
		LED::SetMinBrightness(50);
		LED::SetMaxBrightness(350);
	}

	void Update(unsigned long tickMilliSeconds)
	{
		ExecuteEffects(tickMilliSeconds);
	}

	void ExecuteEffects(unsigned long tickMilliSeconds)
	{
		for (int i = 0; i < _effects.size(); i++)
		{
			_effects[i]->Update(this, tickMilliSeconds);
		}
	}

	string ToString()
	{
		return "CandleLED " + _id;
	}
};