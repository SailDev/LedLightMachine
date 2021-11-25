#pragma once
#include <string>
#include <random>
#include "LED.h"
#include "Lib/StringTools.h"
#include "Effect.h"

using namespace std;

class SimpleCandleEffect : public Effect
{
private:
	StringTools _stringTools = StringTools();
	unsigned long _lastIntervalTime = 0L;
	unsigned long _intervalTimeMilliSeconds = 0L;
	enum State
	{
		undefined,
		running
	};
	State _state;
	double _brightness = 0;

	default_random_engine _brightnessRandomEngine;
	uniform_int_distribution<int> _brightnessDistribution;

	default_random_engine _intervalTimeRandomEngine;
	uniform_int_distribution<int> _intervalTimeDistribution;

public:
	SimpleCandleEffect(int intervalTime) : Effect()
	{
		_intervalTimeMilliSeconds = intervalTime;
		_isActive = true;
		_state = undefined;
	}

	void Update(LED *led, unsigned long tickMilliSeconds)
	{
		if (!_isActive)
		{
			return;
		}

		_led = led;
		_tickMilliSeconds = tickMilliSeconds;

		switch (_state)
		{
		case undefined:
			StateUndefined();
			break;
		case running:
			StateRunning();
			break;
		}
	}

private:
	void StateUndefined()
	{
		InitRandomGenerator();
		CalculateInterval();

		_lastIntervalTime = _tickMilliSeconds;
		_led->SetBrightness(_brightness);

		_state = running;
	}

	void StateRunning()
	{
		_led->LightUp();

		if ((_tickMilliSeconds - _lastIntervalTime) > _intervalTimeMilliSeconds)
		{
			_lastIntervalTime = _tickMilliSeconds;
			CalculateInterval();
		}
	}

	void InitRandomGenerator()
	{
		random_device brightnessRandomDevice;
		_brightnessRandomEngine.seed(brightnessRandomDevice());
		_brightnessDistribution = uniform_int_distribution<int>(_led->GetMinBrightness(), _led->GetMaxBrightness());

		random_device intervalTimeRandomDevice;
		_intervalTimeRandomEngine.seed(intervalTimeRandomDevice());
		_intervalTimeDistribution = uniform_int_distribution<int>(10, 500);
	}

	void CalculateInterval()
	{
		// Random brightness
		_brightness = _brightnessDistribution(_brightnessRandomEngine);
		_led->SetBrightness(_brightness);

		// Random intervaltime
		_intervalTimeMilliSeconds = _intervalTimeDistribution(_intervalTimeRandomEngine);
	}

	string ToString()
	{
		return "SimpleCandleEffect";
	}

	virtual ~SimpleCandleEffect()
	{
		// TODO
	}
};