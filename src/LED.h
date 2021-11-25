#pragma once

#include <Arduino.h>
#include "Effect.h"
#include "Lib/StringTools.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class LED
{
protected:
	string _id;
	int _gpioPin;
	int _channel;
	std::vector<std::unique_ptr<Effect>> _effects;
	StringTools _stringTools = StringTools();
	double _brightness = 0;
	double _maxBrightness = 255;
	double _minBrightness = 0;

public:
	LED(string id, int gpioPin, int  channel )
	{
		_id = id;
		_gpioPin = gpioPin;
		_channel = channel;
	}

	// Getter and setter
	virtual void SetMaxBrightness(double brightness)
	{
		_maxBrightness = brightness;
	}

	virtual double GetMaxBrightness()
	{
		return _maxBrightness;
	}
	
	virtual void SetMinBrightness(double brightness)
	{
		_minBrightness = brightness;
	}

	virtual double GetMinBrightness() 
	{
		return _minBrightness;
	}

	virtual void SetBrightness(double brightness)
	{
		_brightness = brightness;
	}

	virtual double GetBrightness() 
	{
		return _brightness;
	}

	virtual void ChangeBrightness(double difference)
	{
		_brightness += difference;
	}

	virtual void Setup()
	{
		ledcAttachPin(_gpioPin, _channel);

		ledcSetup(_channel, 1000, 8);
	};

	virtual void Update(unsigned long tickMilliSeconds)
	{
		ExecuteEffects(tickMilliSeconds);
	};

	virtual void AddEffect(Effect *effect)
	{
		_effects.emplace_back(effect);
	}

	virtual void ExecuteEffects(unsigned long tickMilliSeconds) = 0;

	virtual void LightUp() 
	{
		ledcWrite(_channel, _brightness);
	}

	virtual string ToString()
	{
		return "LED";
	}
};
