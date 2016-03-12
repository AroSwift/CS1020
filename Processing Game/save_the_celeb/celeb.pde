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
    applyForce(new PVector(10,0));
  }
  
  void stop() {
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
  }
  
  //Set to idle, run, or bathroom
  void set_state(String state) {
    if(state == "idle") stop();
    if(state == "run") go(10, 0);
    if(state == "bathroom") stop();
    
    // Set the new animation state
    super.change_animation(animation_path + state, 62);
  }
  
  void hit() {
   health -= 10;
   if( health <= 0 ) {
     alive = false;
   }
  }
 
}