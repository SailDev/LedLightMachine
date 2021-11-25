#pragma once
#include <string>
#include "LED.h"
#include "Lib/StringTools.h"
#include "Effect.h"

class FadeEffect : public Effect
{
private:
	StringTools _stringTools = StringTools();
	double _durationMilliSeconds = 2000;
	double _fromBrightnessPercent = 0;
	double _toBrightnessPercent = 100;
	double _fadeIntervalPercent = 1;
	unsigned long _checkedTime = 0L;
	enum State
	{
		undefined,
		running
	};
	State _state;

	double _startBrightness = 0;
	double _endBrightness = 0;
	double _brightnessRange = 0;
	double _brightnessIntervalSize = 0;
	double _intervals = 0;
	double _fadeIntervalTime = 0;
	double _elapsedDuration = 0;

public:
	FadeEffect(double duration, double fromBrightnessPercent, double toBrightnessPercent, double fadeIntervalPercent) : Effect()
	{
		_durationMilliSeconds = duration;
		_fromBrightnessPercent = fromBrightnessPercent;
		_toBrightnessPercent = toBrightnessPercent;
		_fadeIntervalPercent = fadeIntervalPercent;
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
		CalculateIntervals();
		_checkedTime = _tickMilliSeconds;
		_elapsedDuration = 0;
		_led->SetBrightness(_startBrightness);
		_state = running;
	}

	void StateRunning()
	{
		_led->LightUp();

		if ((_tickMilliSeconds - _checkedTime) > _fadeIntervalTime)
		{
			_checkedTime = _tickMilliSeconds;
			_led->ChangeBrightness(_brightnessIntervalSize);

			_elapsedDuration += _fadeIntervalTime;
			if (_elapsedDuration > _durationMilliSeconds)
			{

				Serial.println(_stringTools.ToString(_led->GetBrightness()).c_str());
				_isActive = false;
			}
		}
	}

	void CalculateIntervals()
	{
		_startBrightness = _led->GetMinBrightness();
		_endBrightness = _led->GetMaxBrightness();

		_brightnessRange = _led->GetMaxBrightness() - _led->GetMinBrightness();
		_brightnessIntervalSize = _brightnessRange * (_fadeIntervalPercent / 100);

		_intervals = _brightnessRange / _brightnessIntervalSize;
		_fadeIntervalTime = _durationMilliSeconds / _intervals;

		// TODO: Normalize with _from/_toBrightnessPercent

		string info = _stringTools.ToString(_brightnessIntervalSize) + "--" + _stringTools.ToString(_fadeIntervalTime);
		Serial.println(info.c_str());
	}

	string ToString()
	{
		return "FadeEffect";
	}

	virtual ~FadeEffect()
	{
	}
};