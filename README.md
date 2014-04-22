LED_Stick
=========

The LED Stick contains eight white LEDs and an AS1109 8-Bit LED driver, which allows you to control the states of all the LEDs with just two data pins from a microcontroller.  Eagle files for the board are provided here, as are an Arduino sketch and a Processing based graphical user interface for selecting and displaying custom flash patterns.   

##Graphical User Interface

The GUI will display 64 gray circles.  The 8 circles in each row represent the 8 LEDs on the circuit board.  Clicking on the circles will toggle the state of the corresponding LEDs on the Stick.  Once you've selected a pattern on each row, the Processing sketch will cycle through the rows (top to bottom) and display them on the LED Stick one after the other at 75 ms intervals.
