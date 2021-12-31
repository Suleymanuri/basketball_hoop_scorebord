#include <LiquidCrystal.h>                         

// pin declerations for hcsr-04

#define TRIG 7
#define ECHO 6

// pin declerations for the 16x2 lcd

#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

int skor;
int sure;
float uzaklik;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// an enumeration to keep track of the last known state
// of the machinery
enum State {
    EMPTY,
    NOT_EMPTY
}

State last_state;

void setup() {
    skor = 0;
    sure = 0;
    uzaklik = 0;
    last_state = EMPTY;

    lcd.begin(16, 2);
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // read from hcsr-04

    digitalWrite(TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    sure = pulseIn(ECHO, HIGH);
    uzaklik = sure / 29 / 2;
  
    // determine if `skor` should be updated
    // depending on the `last_state` variable

    if (uzaklik < 10 && last_state == EMPTY) {
        skor++;
        last_state = NOT_EMPTY;
    }
    else if (uzaklik > 10) {
        last_state = EMPTY;
    }

    // print the current score to the lcd#include <LiquidCrystal.h>                         

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Skor: ");
    lcd.print(skor);

    Serial.println(uzaklik);
}
