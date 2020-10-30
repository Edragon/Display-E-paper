
#include <stdio.h>
#include <stdlib.h>
#include "epd213B72B.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED      0
#define UNCOLORED    1

int main(void)
{

    Epd epd;
    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }
    //all white
    epd.ClearFrameMemory(0xFF);
    epd.DisplayFrame();
    epd.DelayMs(100);  


    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);
    paint.SetRotate(ROTATE_270);

    /* For simplicity, the arguments are explicit numerical coordinates */
    /* Write strings to the buffer */
    paint.DrawFilledRectangle(0, 0, 250 ,24, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawStringAt(220, 8, "--Qiyun display--", &Font16, UNCOLORED);//x,y
    paint.DrawStringAt(196, 34, "e-Paper Demo", &Font16, COLORED);//x,y

    /* Draw something to the frame_buffer */
    paint.DrawRectangle(90, 60, 130, 110, COLORED); //x1,y1,x2,y2 Diagonal point
    paint.DrawLine(90, 60, 130, 110, COLORED);//x1,y1,x2,y2  
    paint.DrawLine(130, 60, 90, 110, COLORED);//x1,y1,x2,y2  
    paint.DrawCircle(188, 85, 25, COLORED);//x,y,r
    paint.DrawFilledRectangle(30, 60, 70 ,110, COLORED);//x1,y1,x2,y2 Diagonal point
    epd.DelayMs(2000);
    /* Display the frame_buffer */
    epd.SetFrameScreen_ALL(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DelayMs(3000);
  
    //all refresh
    epd.SetFrameScreen_ALL(gImage_1, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();
    epd.DelayMs(2000);
    
     //all refresh
    epd.SetFrameScreen_ALL(gImage_2, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();
    epd.DelayMs(2000);   
    
    //all white
    epd.ClearFrameMemory(0xFF);
    epd.DisplayFrame();
    epd.DelayMs(100);    
 
    while (1) 
    return 0;
}

