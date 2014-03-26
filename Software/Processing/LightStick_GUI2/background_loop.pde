
void background_loop() {

  if (myPort.available()>0) {
    if (millis()-last_time>2000 && start_comm) {//Don't communicate with the microcontroller until user has finished designing the pattern 
      set_pattern(); //Set the pattern drawn in sketch display window
      send_pattern(); //Send pattern array to microcontroller
    }
  }

  if (mousePressed) {
    for (int i=0; i<8; i++) {
      for (int j=0; j<8; j++) {
        //Check which led was clicked
        if (mouseX>=leds[i][j].loc_x-20 && mouseX<=leds[i][j].loc_x+20  &&  mouseY>=leds[i][j].loc_y-20 && mouseY<=leds[i][j].loc_y+20) {
          start_comm = true; //Change in pattern detected, can now send data to microcontroller
          last_time=millis();
          if (leds[i][j].led_state==1) {//If led is on...
            leds[i][j].set_state(0); //...turn it off
          }
          else { //If led is off...
            leds[i][j].set_state(1); //...turn it on
          }
          delay(175); //Reducing delay may cause leds to change states twice per click
        }
      }
    }
  }
}

