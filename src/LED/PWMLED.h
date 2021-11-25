#pragma once
#include "LED.h"
#include "Effect.h"
#include "Lib/StringTools.h"

class PWMLED : public LED
{
private:
	StringTools _stringTools = StringTools();

public:
	PWMLED(string id, int channel, int gpioPin) : LED(id, channel, gpioPin)
	{
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
		return "PWMLED " + _id;
	}
};