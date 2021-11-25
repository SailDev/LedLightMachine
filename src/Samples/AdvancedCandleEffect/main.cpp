#include <Arduino.h>

#include "Effects/AdvancedCandleEffect.h"

#include "LED/CandleLED.h"

#include "Lib/App.h"
#include "LedLightMachine.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

StringTools tools = StringTools();

App *app = new App();
LedLightMachine machine(app);

void setup()
{
  Serial.begin(9600);

  CandleLED *led1 = new CandleLED("E", 16, 1);
  AdvancedCandleEffect *led2AdvancedCandleEffect = new AdvancedCandleEffect(1000);
  led1->AddEffect(led2AdvancedCandleEffect);
  led1->Setup();

  machine.AddLED(led1);

  machine.Start();
}

void loop()
{
  machine.Run();
}