#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <URTouch.h>

#define TFT_DC PB1
#define TFT_CS PB10
#define TFT_RST PB0

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);  ////////// SCK - PA5 // MISO - PA6 // MOSI - PA7 // 

URTouch  myTouch( PB11, PA9, PA8, PB15, PB14);
///////////////////////////////////////////
int chooseColor[7][12];
bool colorHover = false;
bool startHover = false;

int page=0;
int newPage=2;
int mode=1;
int newMode=1;
int color=tft.color565(5*51, 5*51, 0);
bool L1=true,L2=true,L3=true;
bool newL1=false,newL2=false,newL3=false;
bool all=true, newAll=false;
bool global=true,newGlobal=false;
int clickTime=millis();
int ind=0;
int offTime=millis();
int x = -1, y = -1;
////////////////////////////////    



void setup() 
{
  
  Serial.begin(115200);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_EXTREME);
  tft.begin();
  yield();
 
  setColorArray();
  loading();
}

void loop() 
{

  readTouch();

  operateTouch();

  turnOff();

}



void turnOff()
{
  
  if(millis()-offTime>60000)
  {
      newPage=2;
  }
  
}

void operateTouch()
{
  if(x!=-1&&y!=-1)
  {
    offTime=millis();
    //////ekran glowny/////////

    if(x>10&&x<70&&y>90&&y<160)
    {
      startHover=true;
      newPage=0;
    }
    else if(x>10&&x<70&&y>10&&y<70)
    {
      colorHover=true;
      newPage=1;
    }
    else if(x>10&&x<70&&y>175&&y<230)
    {
      colorHover=true;
      newPage=2;
    }
    else
    {
      newPage=page;
    }
    
    if(page==0)
    {
      if(x>120&&x<170&&y>150&&y<190)
      {
        if(!newL1)
        {
          L1=!L1;
        }
        newL1=true;
      }
      else if(x>185&&x<240&&y>185&&y<239)
      {
        if(!newL2)
        {
          L2=!L2;
        }
        newL2=true;
      }
      else if(x>255&&x<310&&y>150&&y<190)
      {
        if(!newL3)
        {
          L3=!L3;
        }
        
        newL3=true;
      }
      else if(x>180&&x<245&&y>95&&y<160)
      {
        if(!newAll)
        {
          all=!all;
        }
        newAll=true; 
  
      }
      else if(x>120&&x<170&&y>50&&y<105)
      {
        newMode=1;
      }
      else if(x>185&&x<240&&y>12&&y<67)
      {
        newMode=2;       
      }
      else if(x>255&&x<310&&y>50&&y<105)
      {
        newMode=3;       
      }
      
      else
      {
        if(newL1)
        {
          L1=!L1;     
        }
         if(newL2)
        {
          L2=!L2;     
        }
         if(newL3)
        {
          L3=!L3;     
        }  
         if(newAll)
        {
          all=!all; 
        }                       
        newL1=false;
        newL2=false;
        newL3=false; 
        newAll=false; 
        newMode=mode;              
      }
    }
    ////////////////////////// color Page ///////////////////////////////////////////
    else if(page==1)
    {
    for(int j = 0; j < 12; j++)
    {
       for(int i = 0; i < 7; i++)  
       {

          if(x>(90+18*j)&&x<(90 + 18*j + 14)&&(240 - y)>(90 + 18*i)&&(240-y)<(90 + 18*i + 14))
          {
              color=chooseColor[i][j];
              tft.fillRoundRect(90, 15, 70, 50, 10, color);
          }
          // tft.fillRect(90+18*j, 90 + 18*i, 14, 14,  chooseColor[i][j]); 
       }
    }
    if(x>90&&x<305&&y>174&&y<222)
    {
        if(!newGlobal)
        {
          global=!global;
        }
        newGlobal=true;
    }
    else
    {
        if(newGlobal)
        {
          global=!global;     
        }
        newGlobal=false;
    }
    
    }
      
    ////////// wygaszanie ekranu     /////////////////
     if(page==2)
     {
       newPage=0;
     }
  }
  else
  {
    if(page!=newPage)
    {
      if(newPage==0)
      {
        startScreen();
        page=newPage;
      }
      else if(newPage==1)
      {
         colorScreen();
         page=newPage;    
      }    
      else if(newPage==2)
      {
         tft.fillScreen(ILI9341_BLACK);
         page=newPage;   
      }   
                
    }
    if(newAll)
    { 
        if(all)
        {
          tft.setRotation(2);
          tft.fillCircle(119,110,30, tft.color565(230, 0, 0));
          tft.setRotation(1);          
          tft.setCursor(194, 112);
          tft.println("All");            
          L1=true;
          L2=true;
          L3=true;
          newL1=true;
          newL2=true;
          newL3=true;    
        }
        else
        {
          tft.setRotation(2);
          tft.fillCircle(119,110,30, tft.color565(0, 230, 0));
          tft.setRotation(1);          
          tft.setCursor(194, 112);
          tft.println("All");  
          L1=false;
          L2=false;
          L3=false;  
          newL1=true;
          newL2=true;
          newL3=true;                  
        }      
      newAll=false;
    }
      
      if(newL1)
      {
        if(L1)
        {
          tft.setRotation(2);
          tft.fillRoundRect(47, 150, 54, 54, 10, tft.color565(0, 230, 0));    //L3    
          tft.setRotation(1);
          tft.setCursor(134, 68);
          tft.println("L1"); 
        }
        else
        {
           tft.setRotation(2);
           tft.fillRoundRect(47, 150, 54, 54, 10, tft.color565(230, 0, 0));    //L3 
           tft.setRotation(1);
           tft.setCursor(134, 68);
           tft.println("L1");   
        }        
        newL1=false;
      }
           
      if(newL2)
      {
        if(L2)
        {
          tft.setRotation(2);
          tft.fillRoundRect(7, 83, 54, 54, 10, tft.color565(0, 230, 0));      //L2   
          tft.setRotation(1);
          tft.setCursor(200, 28);
          tft.println("L2"); 

        }
        else
        {
          tft.setRotation(2);
          tft.fillRoundRect(7, 83, 54, 54, 10, tft.color565(230, 0, 0));      //L2  
          tft.setRotation(1);
          tft.setCursor(200, 28);
          tft.println("L2"); 
        }
        newL2=false;
      } 
      
      if(newL3)
      {
        if(L3)
        {
          tft.setRotation(2);
          tft.fillRoundRect(47, 17, 54, 54, 10, tft.color565(0, 230, 0));     //L3
          tft.setRotation(1);
          tft.setCursor(265, 68);
          tft.println("L3");  
        }
        else
        {
          tft.setRotation(2);
          tft.fillRoundRect(47, 17, 54, 54, 10, tft.color565(230, 0, 0));     //L3
          tft.setRotation(1);          
          tft.setCursor(265, 68);
          tft.println("L3"); 
        }
        newL3=false;
      }  
    if(mode!=newMode)
    {
      mode=newMode;
      tft.setRotation(2);  
      if(mode==1)
      {
         tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(230, 0, 0));      //M3
         tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(230, 0, 0));      //M2
         tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(0, 230, 0));     //M1
      }
      if(mode==2)
      {
         tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(230, 0, 0));      //M3
         tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(0, 230, 0));      //M2
         tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(230, 0, 0));     //M1
      }
      if(mode==3)
      {
         tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(0, 230, 0));      //M3
         tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(230, 0, 0));      //M2
         tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(230, 0, 0));     //M1        
      } 
      
      tft.setRotation(1);       
      tft.setCursor(134, 156);
      tft.println("M1"); 
      tft.setCursor(200, 198);
      tft.println("M2"); 
      tft.setCursor(265, 156);
      tft.println("M3");                    
    }

    if(newGlobal)
    {
      tft.fillRoundRect(180, 15, 120, 50, 10, tft.color565(27, 27, 212));
      
      if(global)
      {
        tft.setCursor(206, 32);
        tft.println("Global");
      }
      else
      {
         tft.setCursor(212, 32);
         tft.println("Local");      
      }
      newGlobal=false;
    }
    
  }
}

void readTouch() {

  if (myTouch.dataAvailable())
  {
    myTouch.read();
    int x0 = myTouch.getY();
    int y0 = myTouch.getX();
    if(x0!=-1&&y0!=-1)
    {
    y = x0+5;
    x = 330-y0;

    if(y<0)y=0;
    if(y>239)y=239;
    if(x<0)x=0;
    if(x>319)x=319;
//    Serial.print(x);
//    Serial.print("  ");
//    Serial.println(y);
  //  tft.setRotation(1);
   // tft.drawPixel(x,239- y, ILI9341_WHITE);
    //yield();
    }
    else
    {
      x=-1;
      y=-1;
    }
  }
  else
  {
      x=-1;
      y=-1;
  }
}



void loading()
{  

   tft.fillScreen(ILI9341_BLACK);
   delay(50);
   for(int i=319;i>=0;i--)
   {
     tft.drawPixel(0, i, ILI9341_BLUE);
     tft.drawPixel(1, i, ILI9341_BLUE);
     tft.drawPixel(2, i, ILI9341_BLUE);
     tft.drawPixel(3, i, ILI9341_BLUE);
     tft.drawPixel(3, i, ILI9341_BLUE);    
      delay(1);
   }
    delay(100);
}

void startScreen()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(2);

  tft.fillRoundRect(7, 248, 64, 64, 10, tft.color565(250, 10, 0));
  tft.fillRoundRect(87, 248, 64, 64, 10, tft.color565(130, 130, 130)); 
  tft.fillRoundRect(166, 248, 64, 64, 10, tft.color565(201, 111, 0));
      
  tft.fillRect(176, 257, 20, 20,  tft.color565(100, 230, 14));    //Gp
  tft.fillRect(200, 257, 20, 20,  tft.color565(255, 255, 8));     //DP
  tft.fillRect(200, 281, 20, 20,  tft.color565(0, 95, 247));      //GP
  tft.fillRect(176, 281, 20, 20,  tft.color565(230, 0, 0));    //gl
  
  tft.fillCircle(119,280,25, tft.color565(230, 230, 230));
  tft.fillCircle(119,280,10, tft.color565(130, 130, 130));      


  if(L1)
  {
    tft.fillRoundRect(47, 150, 54, 54, 10, tft.color565(0, 230, 0));       
  }
  else
  {
     tft.fillRoundRect(47, 150, 54, 54, 10, tft.color565(230, 0, 0));    
  }        

  if(L2)
  {
    tft.fillRoundRect(7, 83, 54, 54, 10, tft.color565(0, 230, 0));       
  }
  else
  {
    tft.fillRoundRect(7, 83, 54, 54, 10, tft.color565(230, 0, 0));      
  }   

  if(L3)
  {
    tft.fillRoundRect(47, 17, 54, 54, 10, tft.color565(0, 230, 0));    
  }
  else
  {
    tft.fillRoundRect(47, 17, 54, 54, 10, tft.color565(230, 0, 0));   
  }


  if(mode==1)
  {
     tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(230, 0, 0));      //M3
     tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(230, 0, 0));      //M2
     tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(0, 230, 0));     //M1
  }
  if(mode==2)
  {
     tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(230, 0, 0));      //M3
     tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(0, 230, 0));      //M2
     tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(230, 0, 0));     //M1
  }
  if(mode==3)
  {
     tft.fillRoundRect(137, 17, 54, 54, 10, tft.color565(0, 230, 0));      //M3
     tft.fillRoundRect(177, 83, 54, 54, 10, tft.color565(230, 0, 0));      //M2
     tft.fillRoundRect(137, 150, 54, 54, 10, tft.color565(230, 0, 0));     //M1        
  } 


  if(all)
  {
    tft.fillCircle(119,110,30, tft.color565(230, 0, 0));       
  }
  else
  {
    tft.fillCircle(119,110,30, tft.color565(0, 230, 0));               
  }   
    
  tft.setRotation(1);
  tft.setCursor(22, 32);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2.5);
  tft.println("Off");

  
   tft.setCursor(134, 156);
   tft.println("M1"); 
   tft.setCursor(200, 198);
   tft.println("M2"); 
   tft.setCursor(265, 156);
   tft.println("M3");  

   tft.setCursor(134, 68);
   tft.println("L1"); 
   tft.setCursor(200, 28);
   tft.println("L2"); 
   tft.setCursor(265, 68);
   tft.println("L3");  
   tft.setCursor(194, 112);
   tft.println("All");  
}
void colorScreen()
{
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRoundRect(7, 248, 64, 64, 10, tft.color565(250, 10, 0));
  tft.fillRoundRect(87, 248, 64, 64, 10, tft.color565(130, 130, 130)); 
  tft.fillRoundRect(166, 248, 64, 64, 10, tft.color565(201, 111, 0));

  tft.fillRect(176, 257, 20, 20,  tft.color565(100, 230, 14));    //Gp
  tft.fillRect(200, 257, 20, 20,  tft.color565(255, 255, 8));     //DP
  tft.fillRect(200, 281, 20, 20,  tft.color565(0, 95, 247));      //GP
  tft.fillRect(176, 281, 20, 20,  tft.color565(230, 0, 0));    //gl
  
  tft.fillCircle(119,280,25, tft.color565(230, 230, 230));
  tft.fillCircle(119,280,10, tft.color565(130, 130, 130));      


  tft.setRotation(1);
  /////////////////// global/local////////////////////////
  tft.fillRoundRect(180, 15, 120, 50, 10, tft.color565(27, 27, 212));
      
  if(global)
  {
    tft.setCursor(206, 32);
    tft.println("Global");
  }
  else
  {
     tft.setCursor(212, 32);
     tft.println("Local");      
  }
  ///////////////////////show color////////////////////
  tft.fillRoundRect(90, 15, 70, 50, 10, color); 


  for(int j = 0; j < 12; j++)
    {
     for(int i = 0; i < 7; i++)  
     {
         tft.fillRect(90+18*j, 90 + 18*i, 14, 14,  chooseColor[i][j]); 
     }
  }

   
  tft.setCursor(22, 32);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2.5);
  tft.println("Off");

}

void setColorArray()
{
    chooseColor[0][0]=tft.color565(2*51, 0, 0);
    chooseColor[1][0]=tft.color565(3*51, 0, 0);
    chooseColor[2][0]=tft.color565(4*51, 0, 0);
    chooseColor[3][0]=tft.color565(5*51, 0, 0);
    chooseColor[4][0]=tft.color565(5*51, 1*51, 1*51);
    chooseColor[5][0]=tft.color565(5*51, 2*51, 2*51);
    chooseColor[6][0]=tft.color565(5*51, 3*51, 3*51);
    
    chooseColor[0][1]=tft.color565(2*51, 51, 0);
    chooseColor[1][1]=tft.color565(3*51, 76, 0);
    chooseColor[2][1]=tft.color565(4*51, 102, 0);
    chooseColor[3][1]=tft.color565(5*51, 128, 0);
    chooseColor[4][1]=tft.color565(5*51, 3*51, 1*51);
    chooseColor[5][1]=tft.color565(5*51, 178, 2*51);
    chooseColor[6][1]=tft.color565(5*51, 4*51, 3*51);
    
    chooseColor[0][2]=tft.color565(2*51, 2*51, 0);
    chooseColor[1][2]=tft.color565(3*51, 3*51, 0);
    chooseColor[2][2]=tft.color565(4*51, 4*51, 0);
    chooseColor[3][2]=tft.color565(5*51, 5*51, 0);
    chooseColor[4][2]=tft.color565(5*51, 5*51, 1*51);
    chooseColor[5][2]=tft.color565(5*51, 5*51, 2*51);
    chooseColor[6][2]=tft.color565(5*51, 5*51, 3*51);
    
    chooseColor[0][3]=tft.color565(51, 2*51, 0);
    chooseColor[1][3]=tft.color565(76, 3*51, 0);
    chooseColor[2][3]=tft.color565(2*51, 4*51, 0);
    chooseColor[3][3]=tft.color565(128, 5*51, 0);
    chooseColor[4][3]=tft.color565(3*51, 5*51, 1*51);
    chooseColor[5][3]=tft.color565(178, 5*51, 2*51);
    chooseColor[6][3]=tft.color565(4*51, 5*51, 3*51);
    
    chooseColor[0][4]=tft.color565(0, 2*51, 0);
    chooseColor[1][4]=tft.color565(0, 3*51, 0);
    chooseColor[2][4]=tft.color565(0, 4*51, 0);
    chooseColor[3][4]=tft.color565(0, 5*51, 0);
    chooseColor[4][4]=tft.color565(51, 5*51, 1*51);
    chooseColor[5][4]=tft.color565(2*51, 5*51, 2*51);
    chooseColor[6][4]=tft.color565(3*51, 5*51, 3*51);
    
    chooseColor[0][5]=tft.color565(0, 2*51, 51);
    chooseColor[1][5]=tft.color565(0, 3*51, 76);
    chooseColor[2][5]=tft.color565(0, 4*51, 2*51);
    chooseColor[3][5]=tft.color565(0, 5*51, 128);
    chooseColor[4][5]=tft.color565(51, 5*51, 3*51);
    chooseColor[5][5]=tft.color565(2*51, 5*51, 178);
    chooseColor[6][5]=tft.color565(3*51, 5*51, 4*51);
    
    chooseColor[0][6]=tft.color565(0, 2*51, 2*51);
    chooseColor[1][6]=tft.color565(0, 3*51, 3*51);
    chooseColor[2][6]=tft.color565(0, 4*51, 4*51);
    chooseColor[3][6]=tft.color565(0, 5*51, 5*51);
    chooseColor[4][6]=tft.color565(51, 5*51, 5*51);
    chooseColor[5][6]=tft.color565(2*51, 5*51, 5*51);
    chooseColor[6][6]=tft.color565(3*51, 5*51, 5*51);
    
    chooseColor[0][7]=tft.color565(0, 51, 2*51);
    chooseColor[1][7]=tft.color565(0, 76, 3*51);
    chooseColor[2][7]=tft.color565(0, 2*51, 4*51);
    chooseColor[3][7]=tft.color565(0, 128, 5*51);
    chooseColor[4][7]=tft.color565(51, 3*51, 5*51);
    chooseColor[5][7]=tft.color565(2*51, 178, 5*51);
    chooseColor[6][7]=tft.color565(3*51, 4*51, 5*51);
    
    chooseColor[0][8]=tft.color565(0, 0, 2*51);
    chooseColor[1][8]=tft.color565(0, 0, 3*51);
    chooseColor[2][8]=tft.color565(0, 0, 4*51);
    chooseColor[3][8]=tft.color565(0, 0, 5*51);
    chooseColor[4][8]=tft.color565(51, 51, 5*51);
    chooseColor[5][8]=tft.color565(2*51, 2*51, 5*51);
    chooseColor[6][8]=tft.color565(3*51, 3*51, 5*51);
    
    chooseColor[0][9]=tft.color565(51, 0, 2*51);
    chooseColor[1][9]=tft.color565(76, 0, 3*51);
    chooseColor[2][9]=tft.color565(2*51, 0, 4*51);
    chooseColor[3][9]=tft.color565(127, 0, 5*51);
    chooseColor[4][9]=tft.color565(3*51, 51, 5*51);
    chooseColor[5][9]=tft.color565(178, 2*51, 5*51);
    chooseColor[6][9]=tft.color565(4*51, 3*51, 5*51);
    
    chooseColor[0][10]=tft.color565(2*51, 0, 2*51);
    chooseColor[1][10]=tft.color565(3*51, 0, 3*51);
    chooseColor[2][10]=tft.color565(4*51, 0, 4*51);
    chooseColor[3][10]=tft.color565(5*51, 0, 5*51);
    chooseColor[4][10]=tft.color565(5*51, 51, 5*51);
    chooseColor[5][10]=tft.color565(5*51, 2*51, 5*51);
    chooseColor[6][10]=tft.color565(5*51, 3*51, 5*51);
    
    chooseColor[0][11]=tft.color565(2*51, 0, 51);
    chooseColor[1][11]=tft.color565(3*51, 0, 76);
    chooseColor[2][11]=tft.color565(4*51, 0, 2*51);
    chooseColor[3][11]=tft.color565(5*51, 0, 127);
    chooseColor[4][11]=tft.color565(5*51, 51, 3*51);
    chooseColor[5][11]=tft.color565(5*51, 2*51, 178);
    chooseColor[6][11]=tft.color565(5*51, 3*51, 4*51);
}
