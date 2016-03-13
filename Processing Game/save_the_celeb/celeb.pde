String celeb_animation_path = "MainCharacter/Actions/";
int max_health = 100;
class Celeb extends Animation {
  // Default max life of character(s)
  int max_health = 100;
  HealthBar health_bar;
  int health;
  boolean alive;
  String state;
  
  Celeb(String state) {
    // Default pose and position of character
    super(paparazzi_animation_path + state, 62, true, 400, 425, 125, 275);
    // Health by defualt shall be 100
    health = max_health;
    // Should start boolean alive
    alive = true;
    
    this.state = state;
    
    // Put a health bar in the top left screen
    health_bar = new HealthBar(max_health, 0, 5, 20);
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
    super.change_animation(celeb_animation_path + state, 62, can_repeat_animation);
  }
  
  void hit(int loss) {
   health -= loss; //<>//
   if( health <= 0 ) { //<>//
     alive = false;
   }
  }
  
  boolean still_doing_current_animation() {
    return super.frame <= super.image_count; 
  }
  
  void display() {
     boolean done_with_animation;
     done_with_animation = super.display_animation(); 
      
     if(done_with_animation) set_state("idle");
     
     if( dist(main_character.location.x, main_character.location.y, paparazzi.location.x, paparazzi.location.y) <= main_character.size.x ) {
      float randomize = random(30);
      
      paparazzi.stop();
      
      if( (randomize > 15 && done_with_animation) || state == "run" ) {
        paparazzi.set_state("punch");
      } else if( (randomize <= 15 && done_with_animation) || state == "run" ) {
        paparazzi.set_state("kick");
      }
    }
    
    health_bar.update(health);
    health_bar.display();
  }
 
}