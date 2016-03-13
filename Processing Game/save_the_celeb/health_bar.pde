class HealthBar extends Object {
  int orig_health;
  int current_health;
 
 HealthBar(int orig_health, int x, int y, int h) {
   // Create a rectangle that resembles a health bar and set the width to health
   super(x, y, orig_health, h, 0, 255, 0);
   
   this.orig_health = orig_health;
   current_health = orig_health;
 }
 
 void update(int new_health) {
   current_health = new_health;
   size.y = current_health;
   
   if(current_health >= orig_health) {
    super.myColor = new PVector(0,255,0);
    // Set the health bar color to green
   } else if(current_health >= orig_health/2) {
     // Set the health bar color to yellow/orange
     super.myColor = new PVector(255,200,0);
   } else if(current_health >= orig_health/3) {
     // Set the health bar color to red
     super.myColor = new PVector(255,0,0);
   }
 }
   
 
 
  
}