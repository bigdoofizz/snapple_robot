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
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor2pin1, HIGH);  
}

void backward(int speed){
  analogWrite(anologpin1, speed);
  analogWrite(anologpin2, speed);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor2pin1, LOW);  
}
void turnRight(int speed){
  analogWrite(anologpin1, speed);
  analogWrite(anologpin2, speed);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor2pin1, LOW);  
}
void turnLeft(int speed){
  analogWrite(anologpin1, speed);
  analogWrite(anologpin2, speed);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor2pin1, HIGH);  
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
    if (command == '2') {
      backward(100);
    }
    if (command == '3') {
      turnRight(100);
    }
    if (command == '4') {
      turnLeft(100);
    }
    if (command == '0') {
      kill();
    }
    if (command =='1B') {
      pacifica();
    }
    if (command == '2B'){
      fire()
    }
    if (command == '3B'){
      twinkle();
    }
    if(command == '4B'){
      stopLED();
    }
  }
}
void stopLED(){
     FastLED.clear();
    FastLED.show();
}
void pacifica() {
    // Four layers of waves
    pacifica_one_layer(1, 26, 100, 11);
    pacifica_one_layer(2, 13, 65, 17);
    pacifica_one_layer(3, 8, 43, 23);
    pacifica_one_layer(4, 5, 28, 29);

    // Add whitecaps
    pacifica_add_whitecaps();

    // Deepen colors
    pacifica_deepen_colors();
}

void pacifica_one_layer(uint8_t layer, uint16_t speed, uint8_t scale, uint8_t offset) {
    uint16_t dataOffset = layer * NUM_LEDS;
    for (int i = 0; i < NUM_LEDS; i++) {
        uint16_t angle = (millis() / speed) + (i * scale) + offset;
        uint8_t level = sin8(angle) / 2 + 127;
        leds[i] += CHSV(200, 255, level);  // Blue-green
    }
}

void pacifica_add_whitecaps() {
    uint8_t basethreshold = beatsin8(9, 55, 65);
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t threshold = basethreshold + (i * 2);
        if (leds[i].blue > threshold) {
            uint8_t overage = leds[i].blue - threshold;
            leds[i] += CRGB(overage, overage, overage);
        }
    }
}

void pacifica_deepen_colors() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].blue = scale8(leds[i].blue, 145);
        leds[i].green = scale8(leds[i].green, 200);
    }
}
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
byte heat[NUM_LEDS];

void fire() {
    // Step 1: Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++) {
        heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS) + 2));
    }

    // Step 2: Heat from each cell drifts 'up' and diffuses a little
    for (int k = NUM_LEDS - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3: Randomly ignite new 'sparks' at the bottom
    if (random8() < 120) {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4: Map heat to LED colors
    for (int j = 0; j < NUM_LEDS; j++) {
        // Scale heat to 0-240 for palette index
        byte colorIndex = scale8(heat[j], 240);

        // Use HeatColors palette
        leds[j] = ColorFromPalette(HeatColors_p, colorIndex);
    }
}

void loop() {
    fire();
    FastLED.show();
    delay(15);
}
void twinkle() {
    // Fade all LEDs slightly
    fadeToBlackBy(leds, NUM_LEDS, 32);

    // Add new twinkles
    if (random8() < 50) {  // 50/255 chance per frame
        int pos = random16(NUM_LEDS);
        leds[pos] = CHSV(random8(), 200, 255);  // Random color
    }
}
