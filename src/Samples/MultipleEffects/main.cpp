#include <Arduino.h>

#include "Effects/BlinkEffect.h"
#include "Effects/FadeEffect.h"
#include "Effects/SimpleCandleEffect.h"
#include "Effects/AdvancedCandleEffect.h"

#include "LED/PWMLED.h"
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
/*
 * Some experiments:
 *
  PWMLED *led1 = new PWMLED("N", 32, 0);
  BlinkEffect *led1BlinkEffect = new BlinkEffect(1000, 1000, 400, 40);
  led1BlinkEffect->Repeat(3);
  led1->AddEffect(led1BlinkEffect);
  led1->Setup();
  PWMLED *led2 = new PWMLED("E", 16, 1);
  FadeEffect *led2FadeEffect = new FadeEffect(10000, 0, 100, 1);
  BlinkEffect *led2BlinkEffect = new BlinkEffect(500, 500, 125, 0, true);
  SimpleCandleEffect *led2SimpleCandleEffect = new SimpleCandleEffect(1000);
  led2->AddEffect(led2SimpleCandleEffect);
  led2->AddEffect(led2BlinkEffect);
  led2->Setup();
  CandleLED *led2 = new CandleLED("E", 16, 1);
  SimpleCandleEffect *led2SimpleCandleEffect = new SimpleCandleEffect(1000);
  led2->AddEffect(led2SimpleCandleEffect);
  led2->Setup();
*/

  PWMLED *led1 = new PWMLED("N", 32, 0);
  FadeEffect *led1FadeEffect = new FadeEffect(10000, 0, 100, 1);
  led1->AddEffect(led1FadeEffect);
  led1->Setup();

  CandleLED *led2 = new CandleLED("E", 16, 1);
  AdvancedCandleEffect *led2AdvancedCandleEffect = new AdvancedCandleEffect(1000);
  led2->AddEffect(led2AdvancedCandleEffect);
  led2->Setup();

  PWMLED *led3 = new PWMLED("S", 17, 2);
  led3->AddEffect(new BlinkEffect(500, 250, 25, 5, true));
  led3->Setup();

  PWMLED *led4 = new PWMLED("W", 27, 3);
  led4->AddEffect(new BlinkEffect(250, 125, 25, 5, true));
  led4->Setup();

  machine.AddLED(led1);
  machine.AddLED(led2);
  machine.AddLED(led3);
  machine.AddLED(led4);

  machine.Start();
}

void loop()
{
  machine.Run();
}