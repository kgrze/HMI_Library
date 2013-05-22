/**
 * @file Graphics.h
 *
 * @brief Defined API for Graphics module
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "../GraphicDriver/GraphicDriver.h"
#include "../Fonts.h"

//! @def Macro for calculating absolute value
#define ABS(X) 		 ((X) > 0 ? (X) : -(X))


void Graphics_DrawRect(unsigned short x_start,
						unsigned short y_start,
						unsigned short x_end,
						unsigned short y_end,
						unsigned int color);

void Graphics_DrawLine(unsigned short x_start,
						unsigned short y_start,
						unsigned short x_end,
						unsigned short y_end,
						unsigned int color);

void Graphics_DrawChar(unsigned short x, unsigned short y, unsigned char ascii_char, FONT_SIZE_TYPE font, unsigned int color);

#endif /* GRAPHICS_H_ */
