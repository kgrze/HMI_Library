/**
 * @file GraphicDriver.h
 *
 * @brief GraphicDriver module API.
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#ifndef GRAPHICDRIVER_H_
#define GRAPHICDRIVER_H_

//! Horizontal resolution in pixel unit
#define H_RES   320

//! Vertical resolution in pixel unit
#define V_RES   240

void GraphicDriver_Initialize(void);
void GraphicDriver_DrawPoint(unsigned short x, unsigned short y, unsigned int color);
unsigned int GraphicDriver_GetPoint(unsigned short x, unsigned short y);

#endif /* GRAPHICDRIVER_H_ */
