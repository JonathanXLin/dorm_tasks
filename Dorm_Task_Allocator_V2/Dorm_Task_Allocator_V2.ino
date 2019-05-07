#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int button = 2;
int buzzer = 3;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String names[] = {"Jonathan", "Gordon", "Oscar", "David"};
int numNames = 4;

char score[] = "g1s1d1d1e1s1d1s3F1s1g1s3";

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
  
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(10);
}

int currName = 0;
int pressed = 0;//Toggled to 1 if press is detected in cycle

void loop() {
  if (digitalRead(button))
  {
    //Cycles through names on button press  
    if (currName == numNames - 1)
      currName = 0;
    else
      currName++;

    pressed = 1;
  }

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

    // Print name to the OLED.
    display.clearDisplay();
    
    if (currName == 0)
      display.setTextSize(2);
    else
      display.setTextSize(3);
      
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(names[currName]);
    display.display();
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
