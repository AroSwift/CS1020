// Class for animating a sequence of GIFs

class Animation extends Object {
  PImage[] images;
  int image_count;
  int frame;
  
  Animation(String path, int count) {
    super(300, 300, 300, 300);
    images = new PImage[count];
    image_count = count;
    frame = 0;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
    }
  }
  
  void change_animation(String path, int count) {
    images = new PImage[count];
    image_count = count;
    frame = 0;
    
    for (int i = 0; i < image_count; i++) {
     String image_name = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(image_name);
    }
  }

  void display(int x, int y) {
    frame = (frame+1) % image_count;
    image(images[frame], x, y);
  }
  
}