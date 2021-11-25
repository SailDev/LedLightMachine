#pragma once
#include <string>
#include <random>
#include "LED.h"
#include "Lib/StringTools.h"
#include "Effect.h"
#include "CandleDisturbancePattern.h"

using namespace std;

class AdvancedCandleEffect : public Effect
{
private:
	StringTools _stringTools = StringTools();
	unsigned long _lastIntervalTime = 0L;
	unsigned long _intervalTimeMilliSeconds = 0L;
	enum State
	{
		undefined,
		random,
		disturbance
	};
	State _state;
	double _brightness = 0;

	default_random_engine _brightnessRandomEngine;
	uniform_int_distribution<int> _brightnessDistribution;

	default_random_engine _intervalTimeRandomEngine;
	uniform_int_distribution<int> _intervalTimeDistribution;

	default_random_engine _randomDurationRandomEngine;
	uniform_int_distribution<int> _randomDurationDistribution;

	int _randomDurationMilliSeconds = 0;
	int _disturbanceIndex = 0;
	int _maxDisturbanceIndex = 499;

public:
	AdvancedCandleEffect(int intervalTime) : Effect()
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
		case random:
			StateRandom();
			break;
		case disturbance:
			StateIntenseDisturbance();
			break;
		}
	}

private:
	void StateUndefined()
	{
		InitRandomGenerator();
		CalculateRandomInterval();
		CalculateRandomDuration();

		_disturbanceIndex = 0;
		_maxDisturbanceIndex = 499;

		_lastIntervalTime = _tickMilliSeconds;
		_led->SetBrightness(_brightness);

		_state = random;
	}

	void StateRandom()
	{
		Serial.println("Random mode");

		_led->LightUp();

		if ((_tickMilliSeconds - _lastIntervalTime) > _intervalTimeMilliSeconds)
		{
			_lastIntervalTime = _tickMilliSeconds;
			_randomDurationMilliSeconds -= _intervalTimeMilliSeconds;
			CalculateRandomInterval();
		}

		if (_randomDurationMilliSeconds <= 0)
		{
			CalculateIntenseDisturbanceInterval();
			_disturbanceIndex = 0;
			_state = disturbance;
		}
	}

	void StateIntenseDisturbance()
	{
		Serial.println("Disturbance mode");

		_led->LightUp();

		if ((_tickMilliSeconds - _lastIntervalTime) > _intervalTimeMilliSeconds)
		{
			_lastIntervalTime = _tickMilliSeconds;
			CalculateIntenseDisturbanceInterval();

			if (_disturbanceIndex < _maxDisturbanceIndex)
			{
				_disturbanceIndex++;
			}
			else
			{
				CalculateRandomDuration();
				_state = random;
			}
		}
	}

	void InitRandomGenerator()
	{
		random_device brightnessRandomDevice;
		_brightnessRandomEngine.seed(brightnessRandomDevice());
		_brightnessDistribution = uniform_int_distribution<int>(_led->GetMinBrightness(), _led->GetMaxBrightness());

		random_device intervalTimeRandomDevice;
		_intervalTimeRandomEngine.seed(intervalTimeRandomDevice());
		_intervalTimeDistribution = uniform_int_distribution<int>(300, 600);

		random_device randomDurationRandomDevice;
		_randomDurationRandomEngine.seed(randomDurationRandomDevice());
		_randomDurationDistribution = uniform_int_distribution<int>(5000, 15000);
	}

	void CalculateRandomDuration()
	{
		_randomDurationMilliSeconds = _randomDurationDistribution(_randomDurationRandomEngine);
	}

	void CalculateRandomInterval()
	{
		// Random brightness
		_brightness = _brightnessDistribution(_brightnessRandomEngine);
		_led->SetBrightness(_brightness);

		// Random intervaltime
		_intervalTimeMilliSeconds = _intervalTimeDistribution(_intervalTimeRandomEngine);
	}

	void CalculateIntenseDisturbanceInterval()
	{
		double brightnessPercent = _candleIntenseDisturbancePattern[_disturbanceIndex][1];
		_brightness = _led->GetMaxBrightness() * brightnessPercent / 100;

		_led->SetBrightness(_brightness);

		double durationMillis = _candleIntenseDisturbancePattern[_disturbanceIndex][0];
		_intervalTimeMilliSeconds = durationMillis * 12;

		// string info = " interval: " + _stringTools.ToString(_intervalTimeMilliSeconds)
		//  + "->" + _stringTools.ToString(_brightness);
		// Serial.println(info.c_str());
	}

	string ToString()
	{
		return "SimpleCandleEffect";
	}

	virtual ~AdvancedCandleEffect()
	{
	}
};