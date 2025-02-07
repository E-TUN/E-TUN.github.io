#include <LiquidCrystal.h>

// Initialize the LCD (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Custom character data
byte bottomHalf[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte topHalf[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  lcd.begin(16, 2);

  // Create custom characters
  lcd.createChar(0, bottomHalf); // Custom char 0: bottom half lit
  lcd.createChar(1, topHalf);   // Custom char 1: top half lit

  lcd.clear();
  lcdAnimation();
}

void lcdAnimation() {
  while (true) { // Infinite animation loop
    
     lcd.setCursor(0,1);
     lcd.print("Tum Se Hi");
     
      for (int i = 0; i < 16; i++) {
      lcd.setCursor(i, 0); // Top row

      // Randomly decide whether to show the top half, bottom half, or a blank space
      int randomChoice = random(0, 3);
      if (randomChoice == 0) {
        lcd.write(byte(0)); // Bottom half
      } else if (randomChoice == 1) {
        lcd.write(byte(1)); // Top half
      } else {
        lcd.print(" "); // Blank space
      }
    }


    delay(100); // Adjust for animation speed
    
    
  }
}

void loop() {
  // The loop remains empty because lcdAnimation() runs infinitely
}
 