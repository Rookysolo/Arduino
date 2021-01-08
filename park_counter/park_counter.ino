unsigned char slots = 0;

// EACH BYTE CORRESPONDING TO DIGIT LEDS SEQUENCES
const byte digit_7segments[] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111,
};

#define enter 2
#define quit 3

#define A 4
#define B 5
#define C 6
#define D 7
#define E 8
#define F 9
#define G 10

#define DP 11

#define red_led 12
#define green_led 13

void setup() {
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);

  pinMode(enter, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);

  // DECLARE USB PORT FOR DEBUG
  Serial.begin(9600);

  // EVENTS
  attachInterrupt(0, removeSlot, FALLING);
  attachInterrupt(1, addSlot, FALLING);
}

void loop() {
   if (slots > 0) {
      digitalWrite(green_led, HIGH);
      digitalWrite(red_led, LOW);
   } else if (slots == 9) {
      digitalWrite(green_led, LOW);
      digitalWrite(red_led, HIGH);
   }
} 

void addSlot() {
  if (slots != 9) {
    slots++;
  }
  Serial.println(slots);
  writeDigit(slots);
}

void removeSlot() {
  if (slots != 0) {
    slots--;
  }
  Serial.println(slots);
  writeDigit(slots);
}

// HIGH LEDS CORRESPONDING TO NUMBER
void writeDigit(unsigned char number) {
  // SECURITY CHECK
  if (number > 9 || number < 0) {
    return;
  }

  // GET LED SEQUENCE
  byte digit = digit_7segments[number];

  // HIGH LED CORRESPONDING TO SEQUENCE
  digitalWrite(A, bitRead(digit, 0));
  digitalWrite(B, bitRead(digit, 1));
  digitalWrite(C, bitRead(digit, 2));
  digitalWrite(D, bitRead(digit, 3));
  digitalWrite(E, bitRead(digit, 4));
  digitalWrite(F, bitRead(digit, 5));
  digitalWrite(G, bitRead(digit, 6));

  Serial.println(digit);
}
