#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN_RIGHT 2
#define LED_PIN_LEFT 3
CRGB leds_RIGHT[NUM_LEDS];
CRGB leds_LEFT[NUM_LEDS];
int motor1pin1 = 4;
int motor1pin2 = 5;

int motor2pin1 = 6;
int motor2pin2 = 7;
int off = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("\nHi, I'm Snapple!");
  FastLED.addLeds<WS2812B, LED_PIN_LEFT, GRB>(leds_LEFT, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_RIGHT, GRB>(leds_RIGHT, NUM_LEDS);
  FastLED.setBrightness(100);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

int i=0;
    while(i<11){
   fill_solid(leds_LEFT, NUM_LEDS, CRGB::Blue);
   fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Yellow);
   FastLED.show();
   delay(500);
   fill_solid(leds_LEFT, NUM_LEDS, CRGB::Green);
   fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Magenta);
   FastLED.show();
   delay(500);
   fill_solid(leds_LEFT, NUM_LEDS, CRGB::Red);
   fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Cyan);
   FastLED.show();
   delay(500);
   i++; 
    }
    FastLED.clear();
    FastLED.show();
    return;
    

}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  }
