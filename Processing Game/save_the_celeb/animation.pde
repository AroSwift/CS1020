// Class for animating a sequence of GIFs

class Animation extends Object {
  PImage[] images;
  int image_count;
  int frame;
  boolean repeat;
  
  Animation(String path, int count, boolean repeat, int x, int y, int w, int h) {
    super(x, y, w, h);
    images = new PImage[count];
    image_count = count;
    frame = 0;
    this.repeat = repeat;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
     images[i].resize(int(size.x), int(size.y));
    }
    
    heightBuffer = 130;
    widthBuffer = 40;
  }
  
  void change_animation(String path, int count, boolean repeat) {
    images = new PImage[count];
    image_count = count;
    frame = 0;
    this.repeat = repeat;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
     images[i].resize(int(size.x), int(size.y));
    }
  }

  boolean display_animation() {
    boolean done_with_animation = false;
    
    frame = (frame+1) % image_count;
    super.myImage = images[frame];
    
    // When at the end of animation
    if(frame+1 == image_count) {
      // Only run the animation once unless otherwise specified
       if( repeat ) {
         frame = 0;
       } else {
         done_with_animation = true;
       }
    }
    
    super.display();
    
    return done_with_animation;
  }
  
}