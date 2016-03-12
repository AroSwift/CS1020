String animation_path = "MainCharacter/Actions/";

class Celeb extends Animation {
  float health;
  boolean alive;
  String state;
  
  Celeb(String state) {
    // Default pose and position of character
    super(animation_path + state, 62, 400, 500, 75, 150);
    // Health by defualt shall be 100
    health = 100;
    // Should start boolean alive
    alive = true;
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
    if(state == "idle") stop();
    if(state == "bathroom") stop();
    if(state == "jump") go(0, -10);
    if(state == "kick" || state == "punch") stop();
    
    if(state == "run") {
      if(key == 'a' || key == 'A') {
         go(-5, 0);
      }else if(key == 'd' || key == 'D') {
        go(10, 0);
      }
    }
    
    // Set the new animation state
    super.change_animation(animation_path + state, 62);
  }
  
  void hit() {
   health -= 10;
   if( health <= 0 ) {
     alive = false;
   }
  }
  
  void display() {
    // Only run the animation once unless otherwise specified
    if(frame+1 == image_count) {
     set_state("idle");
    }
    super.display();
  }
 
}