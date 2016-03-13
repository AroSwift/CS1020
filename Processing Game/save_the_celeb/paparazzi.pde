class Paparazzi extends Animation {
  // Default max life of character(s)
  int max_health = 50;
  HealthBar health_bar;
  int health;
  boolean alive;
  String state;
  Blood drawing_blood;
  
  Paparazzi(String state) {
    // Default pose and position of character
    super(paparazzi_animation_path + state, 61, true, 7, 425, 125, 275);
    // Health by defualt shall be 100
    health = max_health;
    // Should start boolean alive
    alive = true;
    drawing_blood = null;
    
    this.state = state;
    
    // Put a health bar above the paparazzi's head
    //health_bar = new HealthBar(max_health, 10, location);
    PVector new_location = new PVector(location.x, location.y+size.y);
    health_bar = new HealthBar(health, 10, new_location);
  }
  
  void go(int x, int y) {
    velocity = new PVector(x, y);
    //applyForce(new PVector(x,y));
  }
  
  void stop() {
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
  }
  
  //Set to idle, run, jump, punch, or kick
  void set_state(String state) {
    boolean can_repeat_animation;
    
    if(state == "idle") stop();
    if(state == "jump") go(0, -10);
    if(state == "kick" || state == "punch") {
      main_character.hit( int(random(3, 10)) );
      main_character.drawing_blood = new Blood(100, main_character.location, 5, 8);
      stop();
            
      if(state == "kick") {
        kick.play();
        kick.rewind();
      }
      
      if(state == "punch") {
        punch.play();
        punch.rewind();
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
    super.change_animation(paparazzi_animation_path + state, 61, can_repeat_animation);
  }
  
  void hit(int loss) {
    health -= loss;
    if( health <= 0 && alive ) {
      die();
    }
  }
  
  void die() {
    alive = false;
    super.applyRotation(20);
    go(-50, width/2);
    
    // Celeb got another kill
    main_character.num_kills++;
    
    // Play the death sound effect
    death.play();
    death.rewind();
  }
  
  // Overide super class's enforcement of boundries
  void enforceBoundaries() {
    if(alive) {
      super.enforceBoundaries();
    } else {
      if (location.x <= -size.x/2) {
         location.y = width;
      }
        
      if (location.y <= -size.y/2) {
         location.y = height;
      }
    }
  }
  
  void display() {
     if(!alive) {
        super.display();
        return;
     }
     boolean done_with_animation;
     done_with_animation = super.display_animation(); 
      
     if(done_with_animation) set_state("idle");
     
     // Define the actions that the simulate the paparazzi following the celebrity
     if( dist(main_character.location.x, main_character.location.y, paparazzi.location.x, paparazzi.location.y) <= main_character.size.x ) {
       float randomize = random(20);
      
       paparazzi.stop();
      
       if( (randomize > 10 && done_with_animation) || state == "run" ) {
         paparazzi.set_state("punch");
       } else if( (randomize <= 10 && done_with_animation) || state == "run" ) {
         paparazzi.set_state("kick");
       }
    } else {
       PVector f = main_character.attract(paparazzi);
       f.mult(0.000003);
       paparazzi.applyForce(f); 
       if(state != "run") paparazzi.set_state("run");
    }
    
    PVector new_location = new PVector(location.x, location.y+heightBuffer+(-size.y));    
    health_bar.update(health, new_location);
    health_bar.display();
    
    if(drawing_blood != null) drawing_blood.display();
  }
 
}