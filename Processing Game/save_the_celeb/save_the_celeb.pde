// Paparazzi Peril
// Paparazzi Attack

// Sound Libraries for music and sound effects
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

// Library for randomness
import java.util.*;

// Screen background images
PImage intial_bg_image;
PImage game_bg_image;
PImage end_bg_image;

// Characters
Celeb main_character;
Paparazzi paparazzi;
String celeb_animation_path = "MainCharacter/";
String paparazzi_animation_path = "Paparazzi/Character_1/";

// Blood Effects
Blood drawing_blood = null;

// Default screen
int game_screen = 0;

// Set the defualt offset from window in which objects should not go
int heightBuffer = 130;
int widthBuffer = 40;

// Determine the amount of time that has passed since beg
long loop_time;

// Sounds and support objects
Random generator;
AudioPlayer music;
AudioPlayer punch;
AudioPlayer kick;
Minim minim;


void setup() {
   // Set the size of the window
   size(1200,600);
   //fullScreen();

   // Set a lower frame rate so that game works on lower spec machines
   frameRate(30);
  
  
  // Load music and sound effects
   minim = new Minim(this);
   // Bacon & Eggs is produced by Ethan Barlow and processed by Aaron Barlow
   music = minim.loadFile("Bacon & Eggs.mp3", 2048);
   music.loop();
   
   // Sound effects provided by SoundBible
   punch = minim.loadFile("Punch.mp3", 2048);
   kick = minim.loadFile("Kick.mp3", 2048);
   
   // Keep tract of the time that has changed
   //loop_time = millis() + 60000;
   loop_time = millis();
  
   paparazzi = new Paparazzi("idle");
   main_character = new Celeb("idle");
  
   // Load the intial background image only once
   intial_bg_image = loadImage("intial_screen_background.jpg");
   intial_bg_image.resize(width, height);
}

void draw() {
 // Detemine which state the game is in
  if(game_screen == 0) {
    // Show intro screen (instructions)
   initial_screen(); 
  } else if(game_screen == 1) {
    // Play the game!
    play_game_screen();
  } else if(game_screen == 2) {
    // Show end of game screen
    end_game_screen();
  } else {
    // Set a defualt screen just incase
    initial_screen();
  }
}


void keyPressed() {
  // Play the game when the user is ready to play the game
  if(game_screen == 0) {
    // Starting game for the first time
    game_screen = 1;
    main_character.set_state("idle");
    paparazzi.set_state("idle");
    redraw();
    //main_character = new Celeb("idle");
  } else if(game_screen == 2) {
    // Play the game again
    reset_game();
  } else if(game_screen == 1) { // Playing game
    if( key == 'd' || key == 'D' ) {
      // Do not reset run animation if already running!
      if(main_character.state != "run") main_character.set_state("run");
    } else if( key == 'a' || key == 'A' ) {
      // Do not reset run animation if already running!
      if(main_character.state != "run") main_character.set_state("run");
    } else if( key == 'w' || key == 'W' ) {
      //main_character.set_state("jump");
    } else if( key == 'k' || key == 'K' ) {
      if(main_character.state != "kick") main_character.set_state("kick"); 
    } else if( key == 'j' || key == 'J' ) {
      if(main_character.state != "punch") main_character.set_state("punch");
    } else if(key == 'p' || key == 'P') {
       if(looping) {
         fill(0);
         textSize(40);
         // Inform user that game is paused
         textAlign(CENTER);
         text("Game Paused...",width/2,(height/2)-(height*0.3));
         text("P to continue",width/2,(height/2)-(height*0.3)+50);
         
         // Stop the game
         noLoop();
       } else {
         // Start the game agin
         loop();
       }  
    }
  }
}


void keyReleased() {
  // Dont do game actions if user is not ready to play game
  if(game_screen != 0 && game_screen != 2) {
    if( key == 'd' || key == 'D') {
      // Do not reset idle animation if already idling
      if(main_character.state != "idle") main_character.set_state("idle");
    } else if( key == 'a' || key == 'A') {
      // Do not reset idle animation if already idling
      if(main_character.state != "idle")  main_character.set_state("idle");
    }
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
 
  main_character.update();
  main_character.display();
  
  paparazzi.update();
  paparazzi.display();
 
  // Show blood if someone was hit
  if(drawing_blood != null) drawing_blood.display();
  
   fill(0);
   textSize(20);
   // Display main character's kills and account for text size
   text("Kills: " + main_character.num_kills,(width-widthBuffer-main_character.num_kills-60),BOTTOM-heightBuffer+60);
  
  if(!main_character.alive) game_screen = 2;
}

void end_game_screen() {
  background(intial_bg_image);
}

void reset_game() {
 game_screen = 1;
 paparazzi = new Paparazzi("idle");
 main_character = new Celeb("idle");
 
 main_character.set_state("idle");
 paparazzi.set_state("idle");
}