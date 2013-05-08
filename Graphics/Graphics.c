/**
 * @file Graphics.c
 *
 * @brief Set of functions used to draw basic graphical structures like Line, Rectangle or Character
 *
 * @details User needs to implement LCD driver initialization and function that draws one-pixel point at
 * define x and y coordinate
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#include "Graphics.h"

/**
 * @brief Draw Rectangle filled with defined color
 *
 * @details Graphic below will show the meaning of function arguments
 * -------############################# x_end, y_end------------
 * -------##########################################------------
 * -------################color#####################------------
 * -------##########################################------------
 * -------x_start,y_start###########################------------
 */
void Graphics_DrawRect(unsigned short x_start,
						unsigned short y_start,
						unsigned short x_end,
						unsigned short y_end,
						unsigned int color)
{
	unsigned short x,y;

	for(y = y_start; y <  y_end; y++)
	{
		for(x = x_start; x < x_end; x++)
		{
			GraphicDriver_DrawPoint(x,y,color);
		}
	}
}

/**
 * @brief Draw line with defined color
 */
void Graphics_DrawLine(unsigned short x_start,
						unsigned short y_start,
						unsigned short x_end,
						unsigned short y_end,
						unsigned int color)
{
	signed short x_width = 0, y_width = 0, x_abs, y_abs;
	signed short delta = 0;
	unsigned short i;

	x_width = x_end - x_start;
	y_width = y_end - y_start;

	x_abs = ABS(x_width);
	y_abs = ABS(y_width);

	if( x_abs > y_abs )
	{
		//Since horizontal width is greater than vertical, incremental step will calculated from horizontal
		if(x_width >= 0)
		{
			//Line will increase x
			for(i = 0; i < x_abs; i++)
			{
				delta = (i * y_width) / x_width;
				GraphicDriver_DrawPoint(x_start + i, y_start + delta, color);
			}
		}
		else
		{
			//Line will decrease x
			for(i = 0; i < x_abs; i++)
			{
				delta = (i * y_width) / x_abs;
				GraphicDriver_DrawPoint(x_start - i, y_start + delta, color);
			}
		}
	}
	else
	{
		//Since vertical width is greater than horizontal, incremental step will calculated from vertical
		if(y_width >= 0)
		{
			//Line will increase y
			for(i = 0; i < y_abs; i++)
			{
				delta = (i * x_width) / y_width;
				GraphicDriver_DrawPoint(x_start + delta, y_start + i, color);
			}
		}
		else
		{
			//Line will decrease y
			for(i = 0; i < y_abs; i++)
			{
				delta = (i * x_width) / y_width;
				GraphicDriver_DrawPoint(x_start + delta, y_start - i, color);
			}
		}
	}
}

/**
 * @brief Draw ASCII character at defined coordinated with defined color
 *
 * @param x - x coordinate of leftmost corner to start drawing character
 * @param y - y coordinate of topmost corner to start drawing character
 * @param ascii_char - ASCII code character
 * @param font_size - FONT_SIZE_TYPE enumerated parameter defined in Fonts.h file
 * @param color - R5 G6 B5 unit color data
 */
void Graphics_DrawChar(unsigned short x, unsigned short y, unsigned char ascii_char, FONT_SIZE_TYPE font_size, unsigned int color)
{
	unsigned char height_index = 0, width_index = 0, font_height = 0, font_width = 0;
	unsigned short font_row, ascii_table_index;

	if( (font_size == FONT_8P) || (font_size == FONT_8P_BOLD) )
	{
		font_height = FONT_8P_HEIGHT;
		font_width = FONT_8P_WIDTH;
	}
	else if(font_size == FONT_12P)
	{
		font_height = FONT_12P_HEIGHT;
		font_width = FONT_12P_WIDTH;
	}
	else if(font_size == FONT_16P)
	{
		font_height = FONT_16P_HEIGHT;
		font_width = FONT_16P_WIDTH;
	}

	y += font_height;

	ascii_table_index = (ascii_char - 32) * font_height;

	for(height_index = 0; height_index < font_height; height_index++)
	{
		for(width_index = 0; width_index < font_width; width_index++)
		{
			if(font_size == FONT_16P)
			{
				font_row = Font_16p_Ascii_Table[ascii_table_index + height_index];
				if( (font_row & (0x01 << width_index)) != 0x0000 )
				{
					GraphicDriver_DrawPoint(x + width_index, y - height_index, color);
				}
			}
			else if(font_size == FONT_12P)
			{
				font_row = Font_12p_Ascii_Table[ascii_table_index + height_index];
				if( (font_row & (0x8000 >> width_index)) != 0x0000 )
				{
					GraphicDriver_DrawPoint(x + width_index, y - height_index, color);
				}
			}
			else if(font_size == FONT_8P_BOLD)
			{
				font_row = Font_8p_bold_Ascii_Table[ascii_table_index + height_index];
				if( (font_row & (0x80 >> width_index)) != 0x0000 )
				{
					GraphicDriver_DrawPoint(x + width_index, y - height_index, color);
				}
			}
			else if(font_size == FONT_8P)
			{
				font_row = Font_8p_Ascii_Table[ascii_table_index + height_index];
				if( (font_row & (0x80 >> width_index)) != 0x0000 )
				{
					GraphicDriver_DrawPoint(x + width_index, y - height_index, color);
				}
			}
		}
	}
}

