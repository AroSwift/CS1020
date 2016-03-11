import g4p_controls.*;
import interfascia.*;

PImage bg_image;


void setup() {
  // Set the size of the window
  size(1200,700);
  // Load the background image
  bg_image = loadImage("background.jpg");
  

}


void draw() {
 background(bg_image);
}