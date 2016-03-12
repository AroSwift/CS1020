// Class for animating a sequence of GIFs

class Animation extends Object {
  PImage[] images;
  int image_count;
  int frame;
  
  Animation(String path, int count, int x, int y, int w, int h) {
    super(x, y, w, h);
    images = new PImage[count];
    image_count = count;
    frame = 0;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
     images[i].resize(int(size.x), int(size.y));
    }
  }
  
  void change_animation(String path, int count) {
    images = new PImage[count];
    image_count = count;
    frame = 0;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
     images[i].resize(int(size.x), int(size.y));
    }
  }

  void display( boolean repeat ) {
    if(repeat && frame+1 == image_count) frame = 0;
    
    frame = (frame+1) % image_count;
    super.myImage = images[frame];
    
    super.display();
  }
  
}