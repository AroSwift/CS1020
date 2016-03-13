String paparazzi_animation_path = "Paparazzi/Character_1/";

class Paparazzi extends Animation {
  float health;
  boolean alive;
  String state;
  
  Paparazzi(String state) {
    // Default pose and position of character
    super(paparazzi_animation_path + state, 62, true, 400, 425, 125, 275);
    // Health by defualt shall be 100
    health = 100;
    // Should start boolean alive
    alive = true;
    
    this.state = state;
  }
  
  void go(int x, int y) {
    velocity = new PVector(x, y);
    //applyForce(new PVector(x,y));
  }
  
  void stop() {
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
  }
  
  //Set to idle, run, or bathroom
  void set_state(String state) {
    boolean can_repeat_animation;
    
    if(state == "idle") stop();
    if(state == "jump") go(0, -10);
    if(state == "kick" || state == "punch") stop();
    
    if(state == "run") {
      if(key == 'a' || key == 'A') {
         go(-5, 0);
      }else if(key == 'd' || key == 'D') {
        go(10, 0);
      }
    }
    
    can_repeat_animation = state == "idle" || state == "run" ? true : false;
    
    this.state = state;
    
    // Set the new animation state
    super.change_animation(paparazzi_animation_path + state, 62, can_repeat_animation);
  }
  
  void hit() {
   health -= 10;
   if( health <= 0 ) {
     alive = false;
   }
  }
  
  void display() {
     boolean done_with_animation;
     done_with_animation = super.display_animation(); 
      
     if(done_with_animation) set_state("idle");
     
    if( dist(main_character.location.x, main_character.location.y, paparazzi.location.x, paparazzi.location.y) <= main_character.size.x ) {
      float randomize = random(20);
      
      paparazzi.stop();
      
      if( (randomize > 10 && done_with_animation) || state == "run" ) {
        paparazzi.set_state("punch");
      } else if( (randomize < 10 && done_with_animation) || state == "run" ) {
        paparazzi.set_state("kick");
      }
    } else {
     PVector f = main_character.attract(paparazzi);
     f.mult(0.000000005);
     paparazzi.applyForce(f); 
     if(state != "run") paparazzi.set_state("run");
    }
     
     
  }
 
}