#include <LiquidCrystal.h>

#define button A6
#define buzzer 10

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String names[] = {"Jonathan", "Gordon", "Oscar", "Misha", "David"};
int numNames = 5;

char score[] = "g1s1d1d1e1s1d1s3F1s1g1s3";

void setup() {
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);
}

int currName = 0;
int pressed = 0;//Toggled to 1 if press is detected in cycle

void loop() {
  Serial.println(analogRead(button));
  
  if (analogRead(button) == 1023)
  {
    //Cycles through names on button press  
    if (currName == numNames - 1)
      currName = 0;
    else
      currName++;

    pressed = 1;
  }

  // Print name to the LCD.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Next task for:");
  lcd.setCursor(0, 1);
  lcd.print(names[currName]);
  lcd.display();

  //600ms delay if pressed to avoid cycling by more than 1 per button press
  if (pressed)
  {
    for (int i=0; i<11; i++)
    {
      int frequency = pow(2, (char_to_midi(score[i*2]) - 69)/12.0) * 440;
      int dur = score[i*2 + 1] - '0';
      if (score[i*2] != 's')
        tone(buzzer, frequency);
      delay(150*dur - 30);
      noTone(buzzer);
      delay(30);
    }
    pressed = 0;
  }
  else
    delay(100);
}

int char_to_midi(char note)
{
  int midi = 0;
  
  switch(note)
  {
    case 's':
      midi = 0;
      break;
      
    case 'c':
      midi = 60;
      break;

    case 'C':
      midi = 61;
      break;

    case 'd':
      midi = 62;
      break;

    case 'D':
      midi = 63;
      break;

    case 'e':
      midi = 64;
      break;

    case 'f':
      midi = 65;
      break;

    case 'F':
      midi = 66;
      break;

    case 'g':
      midi = 67;
      break;

    case 'G':
      midi = 68;
      break;

    case 'a':
      midi = 69;
      break;

    case 'A':
      midi = 70;
      break;

    case 'b':
      midi = 71;
      break;
  }

  return midi;
}
