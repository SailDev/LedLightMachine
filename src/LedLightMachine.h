#pragma once
#include <string>
#include "Lib/App.h"
#include "LED.h"

class LedLightMachine
{
private:
	App *_app;
	std::vector<std::unique_ptr<LED>> _leds;
	bool _isRunning = false;

public:
	LedLightMachine(App *app)
	{
		_app = app;
	}

	void AddLED(LED *led)
	{
		_leds.emplace_back(led);
	}

	void Start()
	{
		if (_isRunning)
		{
			return;
		}
		_isRunning = true;
	}

	void Stop()
	{
		if (!_isRunning)
		{
			return;
		}

		_isRunning = false;
	}

	void Run()
	{
		while (_isRunning)
		{
			for (int i = 0; i < _leds.size(); i++)
			{
				_leds[i]->Update(_app->TimeAsMilliSeconds());
			}
		}
	}
};