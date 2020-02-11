Code to operate touch and display with TFT SPI screen. I'm using the stm bluepill stm32f103c8t6 and Arduino IDE.  

![](photos/)

You need to install 2 libraries:   
URTouch.h: https://github.com/f1rmb/URTouch/blob/master/URTouch.h  
Adafruit_ILI9341.h: https://github.com/adafruit/Adafruit_ILI9341  

You need to connect:
SCK - PA5  
MISO - PA6
MOSI - PA7

Not all stm pins are working with this screen.

Correctly working pins:
PC13  
PC14  
PC15  
PA0  
PA1  
PA2  
PA3  
PA4  
PB0  
PB1  
PB10  
PB11  
PB12  
PB13  
PB14  
PB15  
PA8  
PA9  
PA10  
PB5  
PB6  
PB7  
PB8  
PB9  
  
