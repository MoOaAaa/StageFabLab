#!/usr/bin/env python
from samplebase import SampleBase

class ColorViewer(SampleBase):
    def __init__(self, *args, **kwargs):
        super(ColorViewer, self).__init__(*args, **kwargs)
        
    def run(self):
        self.offscreen_canvas = self.matrix.CreateFrameCanvas()       
        
        red = 0
        green = 0
        blue = 0
        
        self.offscreen_canvas.Fill(red, green, blue)
        
        while True:
            choice = input("Afficher l'ecran entier (1)(default) ou un carre de 2x2 pixels (2)")
            print("Rentrer une couleur: ")
            
            red = input("rouge: ")
            if(int(red) < 0 or int(red) > 255):
                red = 0
						
            green = input("vert: ")
            if(int(green) < 0 or int(green) > 255):
                green = 0
						
            blue = input("bleu: ")
            if(int(blue) < 0 or int(blue) > 255):
                blue = 0
						
            if(choice == "1"):
                self.offscreen_canvas.Fill(int(red), int(green), int(blue))
                self.offscreen_canvas = self.matrix.SwapOnVSync(self.offscreen_canvas)
            elif(choice == "2"):
                self.offscreen_canvas.SetPixel(14, 14, int(red), int(green), int(blue))
                self.offscreen_canvas.SetPixel(14, 15, int(red), int(green), int(blue))
                self.offscreen_canvas.SetPixel(15, 14, int(red), int(green), int(blue))
                self.offscreen_canvas.SetPixel(15, 15, int(red), int(green), int(blue))
                self.offscreen_canvas = self.matrix.SwapOnVSync(self.offscreen_canvas)
            else:
                self.offscreen_canvas.Fill(int(red), int(green), int(blue))
                self.offscreen_canvas = self.matrix.SwapOnVSync(self.offscreen_canvas)
			      
# Main function
if __name__ == "__main__":
    color_viewer = ColorViewer()
    if (not color_viewer.process()):
        color_viewer.print_help()        
