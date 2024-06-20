#include "EPAPER.h"

void driver_delay_xms(unsigned long xms)	
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256*40; i++);
    }
}


void Epaper_Spi_WriteByte(unsigned char TxData)
{				   			 
	unsigned char TempData;
	unsigned char scnt;
	TempData=TxData;

  EPD_W21_CLK_0;  
	for(scnt=0;scnt<8;scnt++)
	{ 
		if(TempData&0x80)
		  EPD_W21_MOSI_1 ;
		else
		  EPD_W21_MOSI_0 ;
			EPD_W21_CLK_1;  
			EPD_W21_CLK_0;  
			TempData=TempData<<1;

  }

}

void Epaper_READBUSY(void)
{ 
  while(1)
  {	 //=1 BUSY
     if(isEPD_W21_BUSY==0) break;;
  }  
}

void Epaper_Write_Command(unsigned char cmd)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(cmd);
	EPD_W21_CS_1;
}

void Epaper_Write_Data(unsigned char data)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(data);
	EPD_W21_CS_1;
}


	
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void EPD_HW_Init(void)
{
	EPD_W21_RST_0;     
	driver_delay_xms(100); 
	EPD_W21_RST_1; //hard reset  
	driver_delay_xms(100); 
	
	Epaper_READBUSY();   
	Epaper_Write_Command(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	Epaper_Write_Command(0x01); //Driver output control      
	Epaper_Write_Data(0xC7);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);

	Epaper_Write_Command(0x11); //data entry mode       
	Epaper_Write_Data(0x01);

	Epaper_Write_Command(0x44); //set Ram-X address start/end position   
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x18);    //0x18-->(24+1)*8=200

	Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
	Epaper_Write_Data(0xC7);   //0xC7-->(199+1)=200
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00); 

	Epaper_Write_Command(0x3C); //BorderWavefrom
	Epaper_Write_Data(0x05);	
	  	
  Epaper_Write_Command(0x18); 
	Epaper_Write_Data(0x80);	

	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(0x00);
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X199;    
	Epaper_Write_Data(0xC7);
	Epaper_Write_Data(0x00);
  Epaper_READBUSY();
	
}


void EPD_W21_Init(void)
{
	EPD_W21_RST_0;     
	driver_delay_xms(100); 
	EPD_W21_RST_1; 							//hard reset  
	driver_delay_xms(100); 
}



/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{   
  Epaper_Write_Command(0x22); 
  Epaper_Write_Data(0xF7);   
  Epaper_Write_Command(0x20); 
  Epaper_READBUSY();   

}
void EPD_Part_Update(void)
{
	Epaper_Write_Command(0x22); 
	Epaper_Write_Data(0xFF);   
	Epaper_Write_Command(0x20); 
	Epaper_READBUSY(); 			
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
   unsigned int i;	
  Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
   EPD_Update();	 
}
///////////////////////////Part update//////////////////////////////////////////////
//The x axis is reduced by one byte, and the y axis is reduced by one pixel.
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
	unsigned int i;   
	const unsigned char  *datas_flag;   
	datas_flag=datas;

	
  Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
	 datas=datas_flag;
  Epaper_Write_Command(0x26);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
   EPD_Update();		 
	 
}
//mode==POS , 正显；
//mode==NEG , 负显；
//x和PART_LINE 必须是8的整数倍。
void EPD_Dis_Part(unsigned int ystart,unsigned int xstart,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode)
{
	unsigned int i;  
	unsigned int xend,ystart_H,ystart_L,yend_H,yend_L;
	
	xstart=xstart/8;//转换为字节
	xend=xstart+PART_LINE/8-1; 
	
	ystart_L=200-ystart;
		ystart_H=ystart_L/256;
		ystart_L=ystart_L%256;

	yend_L=ystart_L-PART_COLUMN;
		yend_H=yend_L/256;
		yend_L=yend_L%256;		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end
	Epaper_Write_Data(xstart);    	// RAM x address start;
	Epaper_Write_Data(xend);    		// RAM x address end
	Epaper_Write_Command(0x45);       // set RAM y address start/end
	Epaper_Write_Data(ystart_L);    	// RAM y address start Low
	Epaper_Write_Data(ystart_H);    	// RAM y address start High
	Epaper_Write_Data(yend_L);    		// RAM y address end Low
	Epaper_Write_Data(yend_H);    		// RAM y address end High


	Epaper_Write_Command(0x4E);   		// set RAM x address count
	Epaper_Write_Data(xstart); 
	Epaper_Write_Command(0x4F);   		// set RAM y address count
	Epaper_Write_Data(ystart_L);
	Epaper_Write_Data(ystart_H);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
	
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
			{                         
				if (mode==POS)
					{
						Epaper_Write_Data(*datas);
						datas++;
					}

				if (mode==NEG)
					{
						Epaper_Write_Data(~*datas);
						datas++;
					}		
					
					if (mode==OFF)
					{
						Epaper_Write_Data(0xFF);
						datas++;
					}				
			} 	

}


void EPD_DeepSleep(void)
{  	
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01); 
  driver_delay_xms(100);
}


/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_White(void)

{
   unsigned int i,k;
	 Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
	for(k=0;k<200;k++)
  {
		for(i=0;i<25;i++)
		{
			Epaper_Write_Data(0xff);
			}
  }
	 Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
	for(k=0;k<200;k++)
  {
		for(i=0;i<25;i++)
		{
			Epaper_Write_Data(0xff);
			}
  }	
	EPD_Update();
}


//////////////////////////////////////////////////////////////////////////////////////
