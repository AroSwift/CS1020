import de.looksgood.ani.*;
import de.looksgood.ani.easing.*;

// Sound Libraries for music and sound effects
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

import g4p_controls.*;
import interfascia.*;

PImage bg_image;
Celeb main_character;
Animation animation1;


//
// Sounds and support objects.
//
AudioPlayer player;
Minim minim;


void setup() {
  // Set the size of the window
  size(1200,700);
  // Load the background image
  bg_image = loadImage("background.jpg");
  
  // Set frame rate so that game works on lower spec machines
  frameRate(40);
  
  minim = new Minim(this);
  // Bacon & Eggs is produced by Ethan Barlow and processed by Aaron Barlow
  player = minim.loadFile("Bacon & Eggs.mp3", 2048);
  //player.play();
  player.loop();
  
  main_character = new Celeb();
  
  animation1 = new Animation("MainCharacter/Actions/run", 62);



  Ani.init(this);

}


void draw() {
  // Set the background image
 background(bg_image);
 
 //main_character.display();
 
 

  // Display the sprite at the position xpos, ypos
   animation1.display();
 
}


void keyPressed() {
 if( key == 'd' || key == 'D' ) {
   main_character.change_animation("run");
   
 } else if( key == 'w' || key == 'W' ) {
   //character.change_animation("jump");
 }
  
  
}