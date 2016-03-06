/* Arduino Code for Morse Flasher */

// Morse Flashing with NEO PIXEL Strip. Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN    8
#define N_LEDS 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

/*examples of different color functions
  chase(strip.Color(255, 0, 0)); // Red
  chase(strip.Color(0, 255, 0)); // Green
  chase(strip.Color(0, 0, 255)); // Blue
  chase(strip.Color(200, 200, 0)); 
  chase(strip.Color(0, 200, 200));
  
  static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(50);
  }
}
*/


// Message to be flashed, must be typed in caps
char message[] = "TWO HUNDRED PEOPLE DO NOT DRINK THE POOL WATER";

struct morseTable
{
char text;
String morse;
};

typedef struct morseTable table;
table myTable[36];

//Morse table with all letters and numbers
void createTable(){

myTable[0].text = 'A';  myTable[0].morse  = String(".-");
myTable[1].text = 'B';  myTable[1].morse = String("-...");
myTable[2].text = 'C';  myTable[2].morse = String("-.-.");
myTable[3].text = 'D';  myTable[3].morse = String("-..");
myTable[4].text = 'E';  myTable[4].morse = String(".");
myTable[5].text = 'F';  myTable[5].morse = String("..-.");
myTable[6].text = 'G';  myTable[6].morse = String("--.");
myTable[7].text = 'H';  myTable[7].morse = String("....");
myTable[8].text = 'I';  myTable[8].morse = String("..");
myTable[9].text = 'J';  myTable[9].morse = String(".---");
myTable[10].text = 'K';  myTable[10].morse = String("-.-");
myTable[11].text = 'L';  myTable[11].morse = String(".-..");
myTable[12].text = 'M';  myTable[12].morse = String("--");
myTable[13].text = 'N';  myTable[13].morse = String("-.");
myTable[14].text = 'O';  myTable[14].morse = String("---");
myTable[15].text = 'P';  myTable[15].morse = String(".--.");
myTable[16].text = 'Q';  myTable[16].morse = String("--.-");
myTable[17].text = 'R';  myTable[17].morse = String(".-.");
myTable[18].text = 'S';  myTable[18].morse = String("...");
myTable[19].text = 'T';  myTable[19].morse = String("-");
myTable[20].text = 'U';  myTable[20].morse = String("..-");
myTable[21].text = 'V';  myTable[21].morse = String("...-");
myTable[22].text = 'W';  myTable[22].morse = String(".--");
myTable[23].text = 'X';  myTable[23].morse = String("-..-");
myTable[24].text = 'Y';  myTable[24].morse = String("-.--");
myTable[25].text = 'Z';  myTable[25].morse = String("--..");
myTable[26].text = '0';  myTable[26].morse = String("-----");
myTable[27].text = '1';  myTable[27].morse = String(".----");
myTable[28].text = '2';  myTable[28].morse = String("..---");
myTable[29].text = '3';  myTable[29].morse = String("...--");
myTable[30].text = '4';  myTable[30].morse = String("....-");
myTable[31].text = '5';  myTable[31].morse = String(".....");
myTable[32].text = '6';  myTable[32].morse = String("-....");
myTable[33].text = '7';  myTable[33].morse = String("--...");
myTable[34].text = '8';  myTable[34].morse = String("---..");
myTable[35].text = '9';  myTable[35].morse = String("----.");
}

void dot(uint32_t c)
{
  for(uint16_t i=0; i<strip.numPixels()+4; i++) 
  {
      strip.setPixelColor(i  , c); // Draw new pixel
  }
      strip.show();
      delay(250);
  for(uint16_t i=0; i<strip.numPixels()+4; i++) 
  {
      strip.setPixelColor(i  , 0); // Draw new pixel
  }
      strip.show();
      delay(250);
}

void dash(uint32_t c)
{
  for(uint16_t i=0; i<strip.numPixels()+4; i++) 
  {
      strip.setPixelColor(i  , c); // Draw new pixel
  }
      strip.show();
      delay(500);
  for(uint16_t i=0; i<strip.numPixels()+4; i++) 
  {
      strip.setPixelColor(i  , 0); // Draw new pixel
  }
      strip.show();
      delay(250);
}

//This is the start of the message
void startMessage()
{
	dot(strip.Color(200, 200, 200));
	dash(strip.Color(200, 200, 200));
	dot(strip.Color(200, 200, 200));
	dash(strip.Color(200, 200, 200));
	dot(strip.Color(200, 200, 200));
        dash(strip.Color(200, 200, 200));
	delay(500);
}

//This is the end of the message
void endMessage()
{
	dash(strip.Color(200, 200, 200));
	dot(strip.Color(200, 200, 200));
	dot(strip.Color(200, 200, 200));
	dash(strip.Color(200, 200, 200));
	dot(strip.Color(200, 200, 200));
	delay(1000);
}

void setup()
{
  strip.begin();

  //initializing the table of morse code and numbers
  createTable();
  Serial.begin(9600);
}


// Find the index of the letter
int findLetter(char c)
{
	for(int index = 0;  index < 36 ; index++)
	{
		if(myTable[index].text == c)
		{
                        return index;
		}
	}
        Serial.print("something wrong \n");
	return -1;
}

// Start flashing the morse after finding the index of the letter
void morseFlasher(int index)
{
  int i = myTable[index].morse.length();

  Serial.print(myTable[index].morse);
  Serial.print(myTable[index].text);
  Serial.print("    length = ");
  Serial.print(i);
  Serial.print('\n');

  for(int y = 0; y < i; y++)
  {
    if(myTable[index].morse.charAt(y) == '.')
    {
      dot(strip.Color(200, 1, 1));
    }
    else
    {
      dash(strip.Color(1, 200, 1));
    }
  }	
  delay(1000);
}

// Main loop, it will find the index of the current letter
// then flash the morse and move on to the next letter in the message
void loop()
{
  int i = 0;
  int index = 0;
  startMessage();
  
  // move through the string until null character.
  while(message[i] != '\0')
  {      
        if(message[i] == ' ')
        {
          delay(300);
        }
        else
        {
	  index = findLetter(message[i]);
	  if(index != -1)
	  {
		morseFlasher(index);
	  }
	  else
	  {
		Serial.println("Error \n");
	  }
        }
	i++;
  }
  
  endMessage();
  
  Serial.print("Done, idle for 15 seconds \n");
  delay(1000 * 15);
  /**
  while(1)
  {
     delay(500); //Wait here forever
     Serial.print("idling until reset \n");
  }
  **/
}





