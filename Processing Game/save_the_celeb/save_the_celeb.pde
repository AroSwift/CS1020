// Sound Libraries for music and sound effects
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

PImage intial_bg_image;
PImage game_bg_image;
PImage end_bg_image;
Celeb main_character;
Animation crowd;
int game_screen = 0;

//
// Sounds and support objects.
//
AudioPlayer player;
Minim minim;


void setup() {
   // Set the size of the window
   size(1200,600);

   // Set frame rate so that game works on lower spec machines
   frameRate(40);
  
   minim = new Minim(this);
   // Bacon & Eggs is produced by Ethan Barlow and processed by Aaron Barlow
   player = minim.loadFile("Bacon & Eggs.mp3", 2048);
   player.loop();
  
   main_character = new Celeb("idle");
   //crowd = new Animation("MainCharacter/Actions/crowd", 25, true, 125, 450, 250, 250);
  
   // Load the intial background image only once
   intial_bg_image = loadImage("intial_screen_background.jpg");
   intial_bg_image.resize(width, height);
}

void draw() {
 // Detemine which state the game is in 
 //switch(game_screen) {
 // case 0: 
 //   // Show intro screen (instructions)
 //   initial_screen();
 // case 1:
 //   // Play the game!
 //   play_game_screen();
 // case 2:
 //   // Show end of game screen
 //   end_game_screen();
 // default:
 //   initial_screen();
 //}

  if(game_screen == 0) {
   initial_screen(); 
  } else {
    play_game_screen();
  }

}


void keyPressed() {
  // Play the game when the user is ready to play the game
  if(game_screen == 0) game_screen = 1;
  
 if( key == 'd' || key == 'D' ) {
   main_character.set_state("run");
 } else if( key == 'a' || key == 'A' ) {
   main_character.set_state("run");
 } else if( key == 'w' || key == 'W' ) {
   //main_character.set_state("jump");
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

void initial_screen() {
   background(intial_bg_image);
}

void play_game_screen() {
  background(255);
 
  // Set the floor
  fill(175);
  noStroke();
  rect(0, height-100, width, 100);
 
  // Set the sky background
  fill(255);
  noStroke();
  rect(0, 0, width, 200);
 
  main_character.update();
  main_character.display();
}

void end_game_screen() {
  
}