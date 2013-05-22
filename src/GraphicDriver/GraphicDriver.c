/**
 * @file GraphicDriver.c
 *
 * @brief Set of hardware dependent functions to support basic graphic functionality
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

#include "GraphicDriver.h"

/**
 * @brief Initialize LCD module and enable it
 * @todo Add specific LCD and MCU wise implementation
 */
void GraphicDriver_Initialize(void)
{
	do{}while(0);
}

/**
 * @brief Draw one pixel with defined color on LCD
 *
 * @details Function draws point on the screen
 * x = <0, 319> px, horizontal coordinate
 * y = <0, 240> px, vertical coordinate
 * color = <0x0000, 0xFFFF> 16-bit 5-6-5 format |RRRRR-GGGGGG-BBBBB| RGB color data
 *
 * @todo Add specific LCD and MCI wise implementation
 */
void GraphicDriver_DrawPoint(unsigned short x, unsigned short y, unsigned int color)
{
	do{}while(0);
}

/**
 * @brief Get color data from pixel drawn on LCD
 *
 * @details Use LCD internal memory to read color data from given coordinates x and y
 *
 * @todo This implementation is optional.
 */
unsigned int GraphicDriver_GetPoint(unsigned short x, unsigned short y)
{
	return 0;
}
