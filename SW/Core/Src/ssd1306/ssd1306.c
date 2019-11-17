#include "stm32f1xx_hal.h"

#include "ssd1306.h"
#include <math.h>


// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Screen object
static SSD1306_t SSD1306;

static UserAddressingMode addrMode = verticalAddMod;

cfs_al settingsObj;

//
//  Send a byte to the command register
//
static void ssd1306_WriteCommand(uint8_t command)
{
	uint8_t buff[2] = {
	CNTRL_BYTE_SEND_COMMAND,
	command
	};

	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT,SSD1306_I2C_ADDR,buff[0],1,&buff[1],1,10);

}
//
//  Send a data byte sequence to the GDDRAM
//
static void ssd1306_WriteData(uint8_t *buffer,uint16_t length)
{

	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT,SSD1306_I2C_ADDR,CNTRL_BYTE_SEND_DATA,1,buffer,length,100);
}
void test() {


	//volatile  char *v = u8g_GetGlyph(&settingsObj, 58);
	u8g_draw_glyph(&settingsObj,0,0,97);


	/*uint8_t buffer[127] = {0};
	for (int i=0; i<10; i++) {

		buffer[i] = 0xFF;//(uint8_t)(Font_7x10.data[((10*16)-1)+i]>>8);
	}
	uint8_t buffer2[] = { 254,10,0,96,34,23,103,128,128,128,128,128,0,128,22,51,
			  99,160,160,160,2,87,103,80,80,248,80,248,80,80,2,87,
			  103,32,112,160,112,40,112,32,2,87,103,72,168,80,32,80,
			  168,144,2,87,103,64,160,160,64,168,144,104,38,19,99,128,
			128,128,18,55,103,32,64,128,128,128,64,32,18,55,103,128};

	ssd1306_WriteCommand(0x21);
	ssd1306_WriteCommand(0x00);
	ssd1306_WriteCommand(127U);

	ssd1306_WriteCommand(0x22);
	ssd1306_WriteCommand(0x00);
	ssd1306_WriteCommand(0x07);

	ssd1306_WriteData(Font_5x8.data+(30*14),14);*/
	/*ssd1306_WriteData(buffer,1);
	ssd1306_WriteData(buffer,1);*/
//	ssd1306_WriteCommand(0xA5);
}
//
//	Initialize the oled screen
//
uint8_t ssd1306_Init(void)
{
	// Wait for the screen to boot
	HAL_Delay(100);

	/* Init LCD */

	ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
	ssd1306_WriteCommand(0x3F); //
	ssd1306_WriteCommand(0xD3); //-set display offset
	ssd1306_WriteCommand(0x00); //-not offset
	ssd1306_WriteCommand(0x40); //--set start line address(RESET:0b0)
	ssd1306_WriteCommand(0xA0); //--set segment re-map,A0 SEG0 is mapped to col0
	ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction (vertically flipped)
	ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration
	ssd1306_WriteCommand(0x12);
	ssd1306_WriteCommand(0x81); //--set contrast control register
	ssd1306_WriteCommand(0x7F);
	ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssd1306_WriteCommand(0xA6); //--set normal display, A7 invert color
	ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306_WriteCommand(0x80); //--set divide ratio
    ssd1306_WriteCommand(0x8D); //--set DC-DC enable
    ssd1306_WriteCommand(0x14); //
    ssd1306_WriteCommand(0x20);
    ssd1306_WriteCommand(verticalAddMod);
    ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel

	/*ssd1306_WriteCommand(0xAE); //display off
	//ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode
	//ssd1306_WriteCommand(addrMode); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid






	//ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction

	ssd1306_WriteCommand(0x00); //---set low column address
	ssd1306_WriteCommand(0x10); //---set high column address
	ssd1306_WriteCommand(0x40); //--set start line address(RESET:0b0)

	ssd1306_WriteCommand(0x81); //--set contrast control register
	ssd1306_WriteCommand(0xFF);
	ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127
	ssd1306_WriteCommand(0xA6); //--set normal display

	ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

	ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
	ssd1306_WriteCommand(0xF0); //--set divide ratio
	ssd1306_WriteCommand(0xD9); //--set pre-charge period
	ssd1306_WriteCommand(0x22); //
	ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration
	ssd1306_WriteCommand(0x12);
	ssd1306_WriteCommand(0xDB); //--set vcomh
	ssd1306_WriteCommand(0x20); //0x20,0.77xVcc
	ssd1306_WriteCommand(0x8D); //--set DC-DC enable
	ssd1306_WriteCommand(0x14); //
	ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel*/

	// Clear screen
	//ssd1306_Fill(Black);

	// Flush buffer to screen
	//ssd1306_UpdateScreen();
	clearDisplay();
	// Set default values for screen object
	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;

	SSD1306.Initialized = 1;

	settingsObj.font = Font_5x8.data;

	return 1;
}

/* Clear Display */
void clearDisplay(void) {

	for(int i=0;i<8;i++) {

		ssd1306_WriteCommand(commandColAddress); // set col start and end address
		ssd1306_WriteCommand(0x00);
		ssd1306_WriteCommand(127U);
		ssd1306_WriteCommand(commandPageAddress); // set page start and end address
		ssd1306_WriteCommand(i);
		ssd1306_WriteCommand(i);
		uint8_t buffer[128]={0};
		memset(buffer,0x00,128);
		ssd1306_WriteData(buffer,128);

	}


}
//
//  Fill the whole screen with the given color
//
void ssd1306_Fill(SSD1306_COLOR color)
{
	/* Set memory */
	uint32_t i;

	for(i = 0; i < sizeof(SSD1306_Buffer); i++)
	{
		SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

//
//  Write the screenbuffer with changes to the screen
//
void ssd1306_UpdateScreen(void)
{
	uint8_t i;

	for (i = 0; i < 8; i++) {
		ssd1306_WriteCommand((uint8_t)(0xB0 + i));
		ssd1306_WriteCommand((uint8_t)0x00);
		ssd1306_WriteCommand((uint8_t)0x10);

		ssd1306_WriteData(&SSD1306_Buffer[SSD1306_WIDTH * i],SSD1306_WIDTH);
	}
}

//
//	Draw one pixel in the screenbuffer
//	X => X Coordinate
//	Y => Y Coordinate
//	color => Pixel color
//
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color)
{
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		// Don't write outside the buffer
		return;
	}

	// Check if pixel should be inverted
	if (SSD1306.Inverted)
	{
		color = (SSD1306_COLOR)!color;
	}

	// Draw in the right color
	if (color == White)
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	}
	else
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

void ssd1306_DrawGlyph(const char ch, FontDef Font)
{
	uint8_t width = Font.data + 0 ;
	uint8_t height = Font.data + 1 ;
	uint8_t firstAvailableASCII = Font.data + 2;
	uint8_t AvailableASCII = Font.data + 3;

	if((ch<firstAvailableASCII)||(ch>(firstAvailableASCII+AvailableASCII))) { return 0; /* TODO error Code*/}

	uint16_t glyphStartPositionInArray = (( (((ch - 32)*4)+4 ) << 8  ) | (((ch - 32)*4)+5) & 0x00FF );
	uint8_t glyphNumOfEllements;


}

//
//  Draw 1 char to the screen buffer
//	ch 		=> char om weg te schrijven
//	Font 	=> Font waarmee we gaan schrijven
//	color 	=> Black or White
//
char ssd1306_WriteGlyph(char ch,uint8_t *buffer,uint8_t bufferSize,uint8_t wglyph,uint8_t hglyph)
{
	uint32_t i, b, j;

	// Check remaining space on current line
	if (SSD1306_WIDTH <= (SSD1306.CurrentX + wglyph) ||
		SSD1306_HEIGHT <= (SSD1306.CurrentY + hglyph))
	{
		// Not enough space on current line
		return 0; /* TODO Error Code */
	}

	/*Find the in which page should be written the char*/
	if((SSD1306.CurrentY>64)||(SSD1306.CurrentY<0)) { return 0; /* TODO error code*/}

	int8_t startPage = ( ((int8_t)(ceilf( (float)SSD1306.CurrentY / 8))) - 1);
	/* variable = condition ? value_if_true : value_if_false*/
	if (startPage < 0) {startPage = 0;}

	if(startPage>7) { return 0; /* TODO error code */}

	int8_t endPage = ( ((int8_t)(ceilf( (float)hglyph/ 8))) - 1) + startPage;

	if (endPage < 0) {endPage = 0;}

	if((startPage+endPage)>7) { return 0; /* TODO error code */ }

	/*Find the col start and end address */

	uint8_t startCol = SSD1306.CurrentX;

	uint8_t endCol = startCol + wglyph;

	if(endCol>127) { return 0; /* TODO error code */ }
	/* Write the char in display  */

	ssd1306_WriteCommand(commandColAddress); // set col start and end address
	ssd1306_WriteCommand(startCol);
	ssd1306_WriteCommand(endCol);
	ssd1306_WriteCommand(commandPageAddress); // set page start and end address
	ssd1306_WriteCommand(startPage);
	ssd1306_WriteCommand(endPage);

	ssd1306_WriteData(buffer,bufferSize);

	// The current space is now taken
	SSD1306.CurrentX += wglyph;

	// Return written char for validation
	return ch;
}

//
//  Write full string to screenbuffer
//
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color)
{
	// Write until null-byte
	while (*str)
	{
		if (ssd1306_WriteChar(*str, Font, color) != *str)
		{
			// Char could not be written
			return *str;
		}

		// Next char
		str++;
	}

	// Everything ok
	return *str;
}

//
//	Position the cursor
//
void ssd1306_SetCursor(uint8_t x, uint8_t y)
{
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}


/* 4x6
-**-----DEC: 96 HEX: 60
*--*----DEC: 144 HEX: 90
---*----DEC: 16 HEX: 10
-**-----DEC: 96 HEX: 60
*-------DEC: 128 HEX: 80
****----DEC: 240 HEX: F0*/

int8_t u8g_draw_glyph(cfs_al *u8g, uint8_t x, uint8_t y, uint8_t encoding)
{
  const uint8_t *data;
  uint8_t w, h;
  uint8_t bitInGlyphRow,bitInbuffer;
  uint8_t ix, iy;
  uint8_t bytesInGlyph=0;
  uint8_t *buffer; volatile uint8_t buf;

  {
	  void * g = u8g_GetGlyph(u8g, encoding);

      if ( g == NULL  ) { return 0; /* TODO error message */ }

      data = u8g_font_GetGlyphDataStart(u8g->font, g);
  }

  w = u8g->glyph_width;
  h = u8g->glyph_height;
  bytesInGlyph = w; /*  ceilf( (float)(w * h) / 8); */
  // Dynamically allocate memory using calloc()
  buffer = (uint8_t*)calloc(bytesInGlyph, sizeof(uint8_t));
  // Check if the memory has been successfully
  // allocated by calloc or not
  if (buffer == NULL) {

          return(0); /*TODO Error message*/
      }

  bitInGlyphRow=7;

  for(int k=0;k<bytesInGlyph;k++) {
  bitInbuffer=7;

	  for(int i=0;i<h;i++) {


		  uint8_t bitInData = (*(data+i))&(1<<bitInGlyphRow);
		  bitInData=bitInData==0 ?0:1;

		  buffer[k] |= bitInData<<bitInbuffer;

		  bitInbuffer--;

		  if(bitInbuffer<w) {


			  	  	  	  break;

		  	  	  	  	  	  } /*if glyph width is ended then stop the loop*/

	  }
	  bitInGlyphRow--;
  }

  ssd1306_WriteGlyph(encoding,buffer,bytesInGlyph,w,h);
  /* w = u8g->glyph_width;
  h = u8g->glyph_height;

  x += u8g->glyph_x;
  y -= u8g->glyph_y;
  y--;

  if ( u8g_IsBBXIntersection(u8g, x, y-h+1, w, h) == 0 )
    return u8g->glyph_dx;

   now, w is reused as bytes per line
  w += 7;
  w /= 8;

  iy = y;
  iy -= h;
  iy++;

  for( j = 0; j < h; j++ )
  {
    ix = x;
    for( i = 0; i < w; i++ )
    {
      u8g_Draw8Pixel(u8g, ix, iy, 0, u8g_pgm_read(data));
      data++;
      ix+=8;
    }
    iy++;
  }*/
  free(buffer);
  return u8g->glyph_dx;
}

/*
  Find (with some speed optimization) and return a pointer to the glyph data structure
  Also uncompress (format 1) and copy the content of the data structure to the u8g structure
*/
void * u8g_GetGlyph(cfs_al *u8g, uint8_t requested_encoding)
{
  uint8_t *p = (uint8_t *)(u8g->font);
  uint8_t font_format = u8g_font_GetFormat(u8g->font);
  uint8_t data_structure_size = u8g_font_GetFontGlyphStructureSize(u8g->font);
  uint8_t start, end;
  uint16_t pos;
  uint8_t i;
  uint8_t mask = 255;

  if ( font_format == 1 )
    mask = 15; //0b1111

  start = u8g_font_GetFontStartEncoding(u8g->font); //32
  end = u8g_font_GetFontEndEncoding(u8g->font); //255

  pos = u8g_font_GetEncoding97Pos(u8g->font); //3 font(index:8)
  if ( requested_encoding >= 97 && pos > 0 ) // a = 97 b =98
  {
    p+= pos; //+3
    start = 97;
  }
  else
  {
    pos = u8g_font_GetEncoding65Pos(u8g->font); // pos=1 font(index:6)
    if ( requested_encoding >= 65 && pos > 0 ) //A =65 B= 66
    {
      p+= pos;
      start = 65;
    }
    else
      p += U8G_FONT_DATA_STRUCT_SIZE;  //17     // skip font general information
  }

  if ( requested_encoding > end )
  {
    u8g_FillEmptyGlyphCache(u8g);
    return NULL;                     //  not found
  }

  i = start;
  if ( i <= end )
  {
    for(;;)
    {
      if ( *p == 255 )
      {
        p += 1;
      }
      else
      {
        if ( i == requested_encoding )
        {
          u8g_CopyGlyphDataToCache(u8g, p);
          return p;
        }
        p += (*(p + 2)) & mask;
        p += data_structure_size;
      }
      if ( i == end )
        break;
      i++;
    }
  }

  u8g_FillEmptyGlyphCache(u8g);

  return NULL;
}

/* return the data start for a font and the glyph pointer*/
uint8_t *u8g_font_GetGlyphDataStart(const void *font, void * g)
{
  return  (g + u8g_font_GetFontGlyphStructureSize(font));
}

/*
 calculate the overall length of the font, only used to create the picture for the google wiki
size_t u8g_font_GetSize(const void *font)
{
  uint8_t *p = (uint8_t *)(font);
  uint8_t font_format = u8g_font_GetFormat(font);
  uint8_t data_structure_size = u8g_font_GetFontGlyphStructureSize(font);
  uint8_t start, end;
  uint8_t i;
  uint8_t mask = 255;

  start = u8g_font_GetFontStartEncoding(font);
  end = u8g_font_GetFontEndEncoding(font);

  if ( font_format == 1 )
    mask = 15;

  p += U8G_FONT_DATA_STRUCT_SIZE;        skip font general information

  i = start;
  for(;;)
  {
    if ((uint8_t *)(p) == 255 )
    {
      p += 1;
    }
    else
    {
      if ( font_format == 1 ){

    	  uint32_t byte3 = (mask & 0xff00) >> 8;

    	  p +=  ((uint8_t *)(p + 2 )) & (15);
      }
      else {
    	  p +=  ((uint8_t *)(p + 2 )) & (255);
      }
      p += data_structure_size;
    }
    if ( i == end )
      break;
    i++;
  }

  return p - (uint8_t *)font;
}*/

uint8_t u8g_font_GetFontStartEncoding(const void *font)
{
  return u8g_font_get_byte(font, 10);
}

uint8_t u8g_font_GetFontEndEncoding(const void *font)
{
  return u8g_font_get_byte(font, 11);
}

uint8_t u8g_font_GetFontGlyphStructureSize(const uint8_t *font)
{
  switch(u8g_font_GetFormat(font))
  {
    case 0: return 6;
    case 1: return 3;
    case 2: return 6;
  }
  return 3;
}
uint16_t u8g_font_GetEncoding97Pos(const void *font)
{
	char *p = (char *)font;
    return ( *(p+8) << 8  ) | (*(p+9) & 0x00FF );
}
uint16_t u8g_font_GetEncoding65Pos(const void *font)
{
	char *p = (char *)font;
    return ( *(p+6) << 8  ) | (*(p+7) & 0x00FF );
}
uint8_t u8g_font_GetFormat(const uint8_t *font)
{
  return u8g_font_get_byte(font, 0);
}

void u8g_CopyGlyphDataToCache(cfs_al *u8g, const uint8_t *g)
{
  uint8_t tmp =  0;
  switch(u8g_font_GetFormat(u8g->font) )
  {
    case 0:
    case 2:
  /*
    format 0
    glyph information
    offset
    0             BBX width                                       unsigned
    1             BBX height                                      unsigned
    2             data size                                          unsigned    (BBX width + 7)/8 * BBX height
    3             DWIDTH                                          signed
    4             BBX xoffset                                    signed
    5             BBX yoffset                                    signed
  byte 0 == 255 indicates empty glyph
  */
      u8g->glyph_width =   *(g + 0) ;
      u8g->glyph_height =   *(g + 1);
      u8g->glyph_dx =   *(g + 3) ;
      u8g->glyph_x =    *(g + 4) ;
      u8g->glyph_y =    *(g + 5) ;
      break;
    case 1:
    default:
      /*
format 1
  0             BBX xoffset (my change: this is y offset)       signed   --> upper 4 Bit
  0             BBX yoffset (my change: this is x offset)       signed --> lower 4 Bit
  1             BBX width                                       unsigned --> upper 4 Bit
  1             BBX height                                      unsigned --> lower 4 Bit
  2             data size                                           unsigned -(BBX width + 7)/8 * BBX height  --> lower 4 Bit
  2             DWIDTH                                          signed --> upper  4 Bit
  byte 0 == 255 indicates empty glyph
      */

      tmp = *(g + 0) ;
      /* high 4 bits*/
      u8g->glyph_y =  (tmp>>4) & (0b1111);
      //u8g->glyph_y-=2;
      //tmp >>= 4;
      u8g->glyph_x =  tmp & (0b00001111);;

      tmp =  *(g + 1) ;
      u8g->glyph_height =  tmp & 15;
      tmp >>= 4;
      u8g->glyph_width =  tmp;

      tmp =  *(g + 2);
      tmp >>= 4;
      u8g->glyph_dx = tmp;


      break;
  }
}
void u8g_FillEmptyGlyphCache(cfs_al *u8g)
{
  u8g->glyph_dx = 0;
  u8g->glyph_width = 0;
  u8g->glyph_height = 0;
  u8g->glyph_x = 0;
  u8g->glyph_y = 0;
}

uint8_t u8g_font_get_byte(const uint8_t *font, uint8_t offset)
{
  font += offset;
  return ( *font );
}
