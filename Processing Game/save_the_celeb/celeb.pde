String animation_path = "MainCharacter/Actions/";

class Celeb extends Animation {
  float health;
  boolean alive;
  String state;
  
  Celeb(String state) {
    // Default pose and position of character
    super(animation_path + state, 62, 100, 500, 75, 150);
    // Health by defualt shall be 100
    health = 100;
    // Should start boolean alive
    alive = true;
  }
  
  //Set to idle, run, or bathroom
  void set_state(String state) {
    super.change_animation(animation_path + state, 62);
  }
  
  void hit() {
   health -= 10;
   if( health <= 0 ) {
     alive = false;
   }
  }
 
}