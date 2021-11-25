#pragma once
#include <string>
#include "LED.h"
#include "Lib/StringTools.h"
#include "Effect.h"

class BlinkEffect : public Effect
{
private:
	StringTools _stringTools = StringTools();
	double _onPhaseDurationMilliSeconds = 0;
	double _onPhaseBrightness = 100;
	double _offPhaseDurationMilliSeconds = 0;
	double _offPhaseBrightness = 0;
	bool _forceBrightness = true;
	enum State
	{
		undefined,
		on,
		off
	};

	State _state = undefined;
	unsigned long _onStateCheckTime = 0L;
	unsigned long _offStateCheckTime = 0L;

public:
	BlinkEffect(double onPhaseDuration, double offPhaseDuration) : Effect()
	{
		_onPhaseDurationMilliSeconds = onPhaseDuration;
		_offPhaseDurationMilliSeconds = offPhaseDuration;
		_state = undefined;
		_isActive = true;
	}

	BlinkEffect(double onPhaseDuration, double offPhaseDuration, double onPhaseBrightness, double offPhaseBrightness, bool forceBrightness) : Effect()
	{
		_onPhaseDurationMilliSeconds = onPhaseDuration;
		_offPhaseDurationMilliSeconds = offPhaseDuration;
		_onPhaseBrightness = onPhaseBrightness;
		_offPhaseBrightness = offPhaseBrightness;
		_forceBrightness = forceBrightness;
		_state = undefined;
		_isActive = true;
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
		case on:
			StateOn();
			break;
		case off:
			StateOff();
			break;
		}
	}

private:
	void StateUndefined()
	{
		// Initialize
		_onStateCheckTime = _tickMilliSeconds;
		_offStateCheckTime = _tickMilliSeconds + _onPhaseDurationMilliSeconds;
		_state = on;
	}

	void StateOn()
	{
		// On phase is running
		if (_forceBrightness)
		{
			_led->SetBrightness(_onPhaseBrightness);
		}

		_led->LightUp();

		if ((_tickMilliSeconds - _onStateCheckTime) > _onPhaseDurationMilliSeconds)
		{
			// En of on phase, switch to off phase
			_onStateCheckTime = _tickMilliSeconds;
			_state = off;
		}
	}

	void StateOff()
	{
		// Off phase is running
		if (_forceBrightness)
		{
			_led->SetBrightness(_offPhaseBrightness);
		}

		_led->LightUp();

		if ((_tickMilliSeconds - _offStateCheckTime) > _offPhaseDurationMilliSeconds)
		{
			// End of off phase, switch back to on phase
			// Note: Add on phase duration as offset
			_offStateCheckTime = _tickMilliSeconds + _onPhaseDurationMilliSeconds;

			// At this point a complete cycle (on + off phase) is done.
			if (EndOfLife())
			{
				_isActive = false;
			}
			else
			{
				_repetitionCounter++;
			}

			_state = on;
		}
	}

	string ToString()
	{
		return "BlinkEffect: on=" + _stringTools.ToString(_onPhaseDurationMilliSeconds);
	}

	virtual ~BlinkEffect()
	{
		// TODO
	}
};