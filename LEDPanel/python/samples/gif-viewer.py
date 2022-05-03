#!/usr/bin/env python
import time
import os
from samplebase import SampleBase
from PIL import Image
from operator import itemgetter


class ImageGif(SampleBase):
    def __init__(self, *args, **kwargs):
        super(ImageGif, self).__init__(*args, **kwargs)
        self.parser.add_argument("-d", "--dir", help="The directory which contain all the images of a gif", default="gifs/TransporterRobot/Idle")
        self.parser.add_argument("-s", "--speed", help="The speed between each frame of a gif, the default value is 0.2s", default=0.2)
        self.parser.add_argument("-l", "--loop", help="The gif loop or not (0=no and 1=yes)", default="0")
        self.parser.add_argument("-i", "--iteration", help="The number of time th gif loop", default=1)
        self.gif = []

    def run(self):
        #if not 'image' in self.__dict__:
        #    self.image = Image.open(self.args.image).convert('RGB')
        #self.image.resize((self.matrix.width, self.matrix.height), Image.ANTIALIAS)

        fList = []
        for file in os.listdir(self.args.dir):
            f = os.path.join(self.args.dir, file)
            if(os.path.isfile(f)):
                finish = False
                for car in range(len(f)):
                    if(f[car].isdigit() and finish == False):
                        if(f[car + 1].isdigit()):
                            imageNum = (f, int(f[car] + f[car + 1]))
                            fList.append(imageNum)
                        else:
                            imageNum = (f, int(f[car]))
                            fList.append(imageNum)
                        finish = True
                            
        fList.sort(key=itemgetter(1))
        
        for f in range(len(fList)):
            self.gif.append(Image.open(fList[f][0]).convert('RGB'))
                
        if(self.args.loop == 0):
            for it in range(int(self.args.iteration)):
                for image in range(len(self.gif)):
                    self.matrix.SetImage(self.gif[image])
                    time.sleep(float(self.args.speed))
        else:
            while(True):
                for image in range(len(self.gif)):
                    self.matrix.SetImage(self.gif[image])
                    time.sleep(float(self.args.speed))

# Main function
# e.g. call with
#  sudo ./image-scroller.py --chain=4
# if you have a chain of four
if __name__ == "__main__":
    image_gif = ImageGif()
    if (not image_gif.process()):
        image_gif.print_help()
