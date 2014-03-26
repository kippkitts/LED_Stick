/*__________________________________________________________\
|                                                           |
|       October 27 2012                                     |
|       LightStick Project                                  |
|	Copyright kippkitts, LLC 2012	                    |
|			       	                            |
|	kippkitts, LLC                                      |
|	999 Main Street, Suite 705                          |
|       Pawtucket, RI USA			            |
|	Tel: 401-480-7972, Fax: 401-475-3574		    |
|							    |
|       Arduino code LED Stick Code	                    |
|                                                           |
|							    |
| kippkitts HAS MADE EVERY EFFORT TO INSURE THAT	    |
| THE CODE CONTAINED IN THIS RELEASE IS ERROR-FREE.	    |
| HOWEVER, kippkitts DOES NOT WARRANT THE                   |
| OPERATION OF THE CODE, ASSOCIATED FILES,		    |
| SCHEMATICS &/OR OTHER ENGINEERING MATERIAL.               |
|                                                           |
| THESE MATERIALS WERE PRODUCED FOR PROTOTYPE               |
| PURPOSES ONLY, AND ARE NOT INTENDED FOR                   |
| PRODUCTION. THEY ARE RELEASED SOLELY TO GIVE              |
| ASSISTANCE IN PREPARING                                   |
| THE PROJECT FOR FUTURE PRODUCTION.                        |
|                                                           |
| kippkitts ACCEPTS NO RESPONSIBILITY OR LIABILITY          |
| FOR THE USE OF THIS MATERIAL, OR ANY PRODUCTS             |
| THAT MAY BE BUILT WHICH UTILIZE IT.                       |
|                                                           |
|                                                           |
|		File name : 		LEDStickWhite.ino   |
|		Written by: 		K Bradford          |
|		Final edit date : 	27 October, 2012    |
|                                                           |
|                                                           |
|	1. This prototype code is not for release.          |
|                                                           |
|	2. This project is built for the Arduino ATMEGA328  |
|	                                                    |
|		NOT FOR PRODUCTION                          |
\__________________________________________________________*/


// LED DRIVERS 
int DIN1 = 2; // Data In
int CLK1 = 3; // Clock
int LE1 = 4; // Latch Enable
int OEN = 5; // Output Enable

int LED13 = 13;  // Give us a PIN13 LED

struct Ser_Packet
{
  char header;
  char command;
  char data[8];
  char chksum[2];  // Fletcher checksum
};

Ser_Packet MyData;

int index = 0;

char Pattern[] = 
{
//  B00000000,
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
} ;

int Background(void);

void Task1(void);

void setup() {
  
  pinMode(DIN1, OUTPUT);
  pinMode(CLK1, OUTPUT);
  pinMode(LE1, OUTPUT);
  pinMode(OEN, OUTPUT);
  
  pinMode(LED13, OUTPUT);
    
  Serial.begin(115200);
  index = 0;
  digitalWrite(LED13, HIGH);
  Serial.println("Hello World");
  digitalWrite(LED13, LOW);
  
}

void loop() { 

  Task1();
  switch(Background())
  {
    case 'A':
    {
      Pattern[0] = MyData.data[0];
      Pattern[1] = MyData.data[1];
      Pattern[2] = MyData.data[2];
      Pattern[3] = MyData.data[3];
      Pattern[4] = MyData.data[4];
      Pattern[5] = MyData.data[5];
      Pattern[6] = MyData.data[6];
      Pattern[7] = MyData.data[7];
      break;
    }
    case 'B':
    {
      break;
    }
    default:
      break;
  }
  delay(75);

}

void Task1(void)
{
  digitalWrite(LE1, LOW);
  shiftOut(DIN1, CLK1, MSBFIRST, Pattern[index]);
//    shiftOut(DIN1, CLK1, MSBFIRST, 0xFF);
  digitalWrite(LE1, HIGH);
  
  Serial.print("Index = ");
  Serial.print(index);
  Serial.print("  Pattern = ");
  Serial.println((unsigned int)Pattern[index]);

  index = (index + 1) % sizeof(Pattern);

}



