#include <FastLED.h>
#define LED_PIN 7
#define LED_COUNT    19
CRGB leds[LED_COUNT];


const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

const int MIN_DISTANCE = 15;
const int MAX_DISTANCE = 150;

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, LED_COUNT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int distance  = getDistance();
  //STOP RED LIGHT
  if (distance <= MIN_DISTANCE) {
    stop();
  }

  if (distance > MIN_DISTANCE && distance <= MAX_DISTANCE) {
    int tmpLedsCount =  abs(distance / 5) > 19 ? 19 : abs(distance / 5);
    Serial.print(tmpLedsCount);
    fill_solid(leds, LED_COUNT, CRGB(0, 0, 0));
    fill_solid(leds, tmpLedsCount, CRGB(50, 100, 0));
    delay(10);
    FastLED.show();
  }

  if (distance > MAX_DISTANCE) {
    idleGlow();
  }
}

void idleGlow() {
  for (int dot = 0; dot < LED_COUNT; dot++)
  {

    leds[dot] = CRGB(50, 50, 50);
    FastLED.show();
    //    leds[dot] = CRGB::Black;
    delay(40);
  }

  for (int dot = 0; dot < LED_COUNT; dot++)
  {
    leds[LED_COUNT - dot] = CRGB(50, 100, 0);
    FastLED.show();
    delay(40);
  }
}

int getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;

}
void stop()
{
  fill_solid(leds, LED_COUNT, CRGB(0, 0, 0));
  for (int i = 0; i <= LED_COUNT; i++) {
    leds[i] = CRGB(255, 0, 0);
    delay(70);
    FastLED.show();
  }
}
