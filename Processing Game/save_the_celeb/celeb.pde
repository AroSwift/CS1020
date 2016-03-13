//
// celeb
// by: Aaron Barlow
//
// Encapsilate the characteristics of the celebrity.
// The celeb can run left, right, punch, and kick paparazzi.
//
class Celeb extends Animation {
  // Default max life of character(s)
  int max_health = 100;
  HealthBar health_bar;
  int health;
  boolean alive;
  String state;
  int num_kills;
  Blood drawing_blood;
  
  Celeb(String state) {
    // Default pose and position of character
    super(paparazzi_animation_path + state, 61, true, 400, 425, 125, 275);
    health = max_health;
    // Should start game alive
    alive = true;
    // We are not being punched or kicked
    drawing_blood = null;
    // Have not kicked anyone
    num_kills = 0;
    
    // Set the current animation state
    this.state = state;
    
    // Put a health bar in the top left corner
    PVector new_location = new PVector(0, 10);
    health_bar = new HealthBar(health, 50, new_location);
  }
  
  void go(int x, int y) {
    // Move in the specified direction
    super.velocity = new PVector(x, y);
  }
  
  void stop() {
    // Stop moving in any direction
    super.velocity = new PVector(0, 0);
    super.acceleration = new PVector(0, 0);
  }
  
  //Set to animation state to idle, run, jump, punch, or kick
  void set_state(String state) {
    boolean can_repeat_animation;
    
    if(state == "idle") stop();
    if(state == "jump") go(0, -10);
    if(state == "kick" || state == "punch")  {
      stop();
      
    if( dist(main_character.location.x, main_character.location.y, paparazzi.location.x, paparazzi.location.y) <= main_character.size.x ) {
      float randomize = random(15,30);
      // Decrease the health of paparazzi because celeb is punching or kicking them
      paparazzi.hit( int(randomize) );
      paparazzi.drawing_blood = new Blood(100, paparazzi.location, 5, 8);
      
      if(state == "kick") {
        kick.play();
        kick.rewind();
      }
      
      if(state == "punch") {
        punch.play();
        punch.rewind(); //<>//
      } //<>//
      
    }
      
    }
    
    if(state == "run") {
      if(key == 'a' || key == 'A') {
         go(-5, 0);
       } else if(key == 'd' || key == 'D') {
        go(10, 0);
      }
    }
    
    can_repeat_animation = state == "idle" || state == "run" ? true : false;
    
    this.state = state;
    
    // Set the new animation state
    super.change_animation(celeb_animation_path + state, 61, can_repeat_animation);
  }
  
  void hit(int loss) {
    health -= loss;
    if( health <= 0 ) {
      die();
    }
  }
  
  void die() {
    alive = false;
    super.applyRotation(40);
    go(-100, width/2);
    
    // Play the death sound effect
    death.play();
    death.rewind();
  }
  
  boolean still_doing_current_animation() {
    return super.frame <= super.image_count; 
  }
  
  void display() {
    boolean done_with_animation;
    done_with_animation = super.display_animation(); 
      
    if(done_with_animation) set_state("idle");

    health_bar.update(health);
    health_bar.display();
    
    if(drawing_blood != null) drawing_blood.display();
  }
 
}