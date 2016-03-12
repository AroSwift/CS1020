// Class for animating a sequence of GIFs

class Animation {
  PImage[] images;
  int image_count;
  int frame;
  
  Animation(String path, int count) {
    images = new PImage[count];
    image_count = count;
    frame = 0;
    
    for (int i = 0; i < image_count; i++) {
     String imageName = path + "__" + nf(i, 3) + ".png";
     images[i] = loadImage(imageName);
    }
  }

  void display() {
    frame = (frame+1) % image_count;
    image(images[frame], 0, 0);
  }
  
}