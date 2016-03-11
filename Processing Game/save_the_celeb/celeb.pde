class Celeb extends Object {
  float health;
  boolean alive;
  
  Celeb() {
    // Default pose for character
    super(100,100, "MainCharacter/idle.gif");
    // Health by defualt shall be 100
    health = 100;
    // Should start boolean alive
    alive = true;
  }
  
  //Set to idle, run, or bathroom
  void change_animation(String animation) {
   super.change_image("MainCharacter/" + animation + ".gif");
  }
  
  void hit() {
   health -= 10;
   if( health <= 0 ) {
     alive = false;
   }
  }
 
}