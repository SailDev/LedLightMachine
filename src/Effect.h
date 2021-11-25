#pragma once

#include "LED.h"
#include "Lib/StringTools.h"
#include <string>

using namespace std;

// Forward declaration, because of circular refs
class LED;

class Effect
{
protected:
	const int DO_NOT_REPEAT = 0;
	const int REPEAT_FOREVER = -1;
	int _repetitions = 0;
	int _repetitionCounter = 0;
	bool _isActive = true;
	StringTools _stringTools = StringTools();
	LED *_led;
	unsigned long _tickMilliSeconds = 0L;

public:
	Effect()
	{
		RepeatForever();
	}

	virtual void DoNotRepeat()
	{
		_repetitions = DO_NOT_REPEAT;
	}

	virtual void Repeat(int times)
	{
		_repetitions = times;
	}

	virtual void RepeatForever()
	{
		_repetitions = REPEAT_FOREVER;
	}

	virtual void Update(LED *led, unsigned long tickMilliSeconds) = 0;

	virtual bool EndOfLife()
	{
		if (_repetitions == REPEAT_FOREVER)
		{
			return false;
		}

		if (_repetitions == DO_NOT_REPEAT)
		{
			return true;
		}

		if (_repetitionCounter > _repetitions)
		{
			return true;
		}

		return false;
	}

	virtual string ToString()
	{
		return "Effect";
	}

	virtual ~Effect()
	{
	}
};
