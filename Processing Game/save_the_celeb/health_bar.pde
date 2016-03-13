class HealthBar extends Object {
  int orig_health;
  int current_health;
 
 HealthBar(int orig_health, int x, int y, int h) {
   // Create a rectangle that resembles a health bar and set the width to health
   super(x, y, orig_health, h, 0, 255, 0);
   
   // Show health text
   textSize(32);
   text("Health", 10, 30); 
   
   this.orig_health = orig_health;
   current_health = orig_health;
 }
 
 void update(int new_health) {
   current_health = new_health;
   // Change the size of the rectangle to match the new state of health
   size.x = current_health;
   
   // Does the given character still have more than 2/3 of health?
   if(current_health >= orig_health*0.67) {
    // Set the health bar color to green
    super.myColor = new PVector(0,255,0);
   // Does the given character still have more than 1/3 of health?
   } else if(current_health >= orig_health*.34) {
     // Set the health bar color to yellow/orange
     super.myColor = new PVector(255,200,0);
   //} else if(current_health >= orig_health*.34) {
   } else { // Character has less than 1/3 of life
     // Set the health bar color to red
     super.myColor = new PVector(255,0,0);
   }
 }
   
 
 
  
}