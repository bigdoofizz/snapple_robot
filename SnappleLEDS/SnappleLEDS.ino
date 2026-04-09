#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN_RIGHT 2
#define LED_PIN_LEFT 3
CRGB leds_RIGHT[NUM_LEDS];
CRGB leds_LEFT[NUM_LEDS];
int motor1pin1 = 4;
int motor1pin2 = 5;
int anologpin1 = 8;
int anologpin2 = 9;
int motor2pin1 = 6;
int motor2pin2 = 7;
int i=0;
int off = 1;

void kill(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void forward(int speed){
  analogWrite(anologpin1, speed);
  analogWrite(anologpin2, speed);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor2pin1, HIGH);  
}

void backward(int speed){
  analogWrite(anologpin1, speed);
  analogWrite(anologpin2, speed);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin2, HIGH);  
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(200);
  Serial.print("\nHi, I'm Snapple!");
  FastLED.addLeds<WS2812B, LED_PIN_LEFT, GRB>(leds_LEFT, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_RIGHT, GRB>(leds_RIGHT, NUM_LEDS);
  FastLED.setBrightness(100);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(anologpin1, OUTPUT);
  pinMode(anologpin2, OUTPUT);

      int cycle_time = 2000;

while (i < 2){


  fill_solid(leds_LEFT, NUM_LEDS, CRGB::Blue);
  fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Yellow);
  FastLED.show();
  delay(cycle_time);
  fill_solid(leds_LEFT, NUM_LEDS, CRGB::Green);
  fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Magenta);
  FastLED.show();
  delay(cycle_time);
  fill_solid(leds_LEFT, NUM_LEDS, CRGB::Red);
  fill_solid(leds_RIGHT, NUM_LEDS, CRGB::Cyan);
  FastLED.show();
  delay(cycle_time);
  i++;
}
  if (i == 2){
      FastLED.clear();
    FastLED.show();
  analogWrite(anologpin1, 0);
  analogWrite(anologpin2, 0);
  }

}



void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char command = Serial.read();
    Serial.print(command);
    if (command == '1') {
      forward(100);
    }
    if (command == '0') {
      kill();
    }
  }
}

  
