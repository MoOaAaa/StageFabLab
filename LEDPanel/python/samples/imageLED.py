#!/usr/bin/env python
import time
import os
from samplebase import SampleBase
from PIL import Image

class ImageDraw(SampleBase):
    def __init__(self, *args, **kwargs):
        super(ImageDraw, self).__init__(*args, **kwargs)
        self.parser.add_argument("-i", "--image", help="The image you want to draw", default="gifs/ElectricRobot/Idle/ElectricRobot_Idle_frame1.png")
        
    def run(self):
        if not 'image' in self.__dict__:
            self.image = Image.open(self.args.image).convert('RGB')
        self.image.resize((32, 32), Image.ANTIALIAS)
        
        offset_canvas = self.matrix.CreateFrameCanvas()
        
        pixels = self.image.load()
        for x in range(32):
            for y in range(32):
                offset_canvas.SetPixel(x, y, pixels[x, y][0], pixels[x, y][1], pixels[x, y][2])
                print("pixel(", x, " ", y, ") a une valeur RGB de: R=", pixels[x, y][0], " G=", pixels[x, y][1], " B=", pixels[x, y][2])
        offset_canvas = self.matrix.SwapOnVSync(offset_canvas)
        
        loop = True
        while(loop):
            loop = True
            
        
if __name__ == "__main__":
    image_draw = ImageDraw()
    if (not image_draw.process()):
        image_draw.print_help()
