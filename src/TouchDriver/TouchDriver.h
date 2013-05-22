/**
 * @file TouchDriver.h
 *
 * @brief TouchDriver module API.
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_

#include "../Typedefs.h"
#include "../GraphicDriver/GraphicDriver.h"

//! Enumerated states of TouchDriver state machine
typedef enum
{
	TOUCH_WAITING_FOR_TOUCH,
	TOUCH_DETECT_X,
	TOUCH_DETECT_Y,
} TOUCH_DRIVER_STATE;

//! TouchDriver module structure
typedef struct
{
	TOUCH_DRIVER_STATE State;
	bool IsTouchDetected;
	unsigned short Xpos;
	unsigned short Ypos;
} TOUCH_DRIVIER_TYPE;

void TouchDriver_Initialize(void);
void TouchDriver_Task(void);
bool TouchDriver_IsTouchDetected(void);
unsigned short TouchDriver_GetRawY(void);
unsigned short TouchDriver_GetRawX(void);
unsigned short TouchDriver_GetX(void);
unsigned short TouchDriver_GetY(void);

#endif /* TOUCHDRIVER_H_ */
