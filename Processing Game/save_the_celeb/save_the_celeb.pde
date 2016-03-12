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
Animation crowd;

//
// Sounds and support objects.
//
AudioPlayer player;
Minim minim;


void setup() {
  // Set the size of the window
  size(1200,600);
  // Load the background image
  bg_image = loadImage("background.jpg");
  
  // Set frame rate so that game works on lower spec machines
  frameRate(40);
  
  minim = new Minim(this);
  // Bacon & Eggs is produced by Ethan Barlow and processed by Aaron Barlow
  player = minim.loadFile("Bacon & Eggs.mp3", 2048);
  player.loop();
  
  
  main_character = new Celeb("idle");
  crowd = new Animation("MainCharacter/Actions/crowd", 25, 125, 450, 250, 250);

}

void draw() {
  // Set the background image
 //background(bg_image);
 background(255);
 
 main_character.update();
 main_character.display();
 
 crowd.display();

}


void keyPressed() {
 if( key == 'd' || key == 'D' ) {
   main_character.set_state("run");
 } else if( key == 'a' || key == 'A' ) {
   main_character.set_state("run");
 } else if( key == 'w' || key == 'W' ) {
   main_character.set_state("jump");
 } else if( key == 'k' || key == 'K' ) {
   main_character.set_state("kick"); 
 } else if( key == 'j' || key == 'J' ) {
   main_character.set_state("punch");
 }
  
  
}


void keyReleased() {
  if( key == 'd' || key == 'D') {
   main_character.set_state("idle");
  } else if( key == 'a' || key == 'A') {
   main_character.set_state("idle");
  }
  
}