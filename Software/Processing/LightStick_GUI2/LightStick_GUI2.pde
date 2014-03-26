import processing.serial.*;

Serial myPort;

//Initialize pattern array
int pattern[] = {
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"), 
  unbinary("00000001"),
};

//Declare 16 led objects
LED[][] leds = new LED[8][8];

int last_time = 0;
boolean start_comm = false;

void setup() {
  size(800, 600);
  smooth();
  frameRate(30);
  myPort = new Serial(this, Serial.list()[0], 115200);

  //Construct led's
  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      leds[i][j] = new LED();
      leds[i][j].set_location(width/2-50*7/2+50*i, height/2-50*7/2+50*j); //Position led's
      leds[i][j].set_state(0);//Turn all led's off (0=off, 1=on)
    }
  }
}


void draw() {
  background_loop();
}

//Send data to microcontroller
void send_pattern() {
  int c = myPort.read();
  myPort.write(":A"); //Send header and command
  for (int i=0; i<8; i++) {
    myPort.write(pattern[i]); //Send pattern
    try {
      Thread.sleep(75);
    }
    catch(Exception e) {
    }
  }
  myPort.write("AA");//Send chksum
  start_comm = false; //Send data only once
}

//Build pattern array
void set_pattern() {

  String led_row="";
  for (int j=0; j<8; j++) {
    for (int i=0; i<8; i++) {
      led_row+=leds[i][j].led_state+""; //Collect states of led's in one row
    }
    pattern[j] = unbinary(led_row); 
    led_row=""; //Clear led_row for the next row
  }
}


class LED {

  int led_state;
  int loc_x;
  int loc_y;

  //Draw led
  void set_location(int xpos, int ypos) {
    ellipse(xpos, ypos, 40, 40);
    loc_x = xpos;
    loc_y = ypos;
  }

  //Turn led on/off
  void set_state(int turn_on) {
    if (turn_on==1) {
      fill(0, 250, 0);
      ellipse(loc_x, loc_y, 40, 40);
      led_state = turn_on;
    }
    else {
      fill(100, 100, 100);
      ellipse(loc_x, loc_y, 40, 40);
      led_state = turn_on;
    }
  }
}




