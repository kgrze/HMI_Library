/**
 * @file TouchDriver.c
 *
 * @brief This module implements 4-wire resistive touchscreen data reading
 *
 * @details This module needs hardware support from MCU side, example implementation is for STM32 micro
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#include "TouchDriver.h"

#define TOUCH_ALPHA_BITS		2
#define TOUCH_FILTER_DEBOUNCE	40		//40 [ms]

//TODO define here proper GPIO's for 4-wire resistive touchscreen. Example on STM32 Cortex-M3
//#define   YU    GPIO_Pin_1
//#define   XL    GPIO_Pin_0
//#define   YD    GPIO_Pin_3
//#define   XR    GPIO_Pin_2

//TODO define here proper ADC channels to read voltage from touchscreen
//#define   Touch_XL	ADC_Channel_10
//#define   Touch_YU 	ADC_Channel_11
//#define   Touch_XR 	ADC_Channel_12
//#define   Touch_YD 	ADC_Channel_13

//! Offset values to read absolute linear x position.
//! It was established empirically and will vary from touchscreen resistance value
#define   TOUCH_X_LOWEST_VALID_VALUE	300
#define   TOUCH_X_HIGHEST_VALID_VALUE	3820

//! Offset values to read absolute linear y position.
//! It was established empirically and will vary from touchscreen resistance value
#define   TOUCH_Y_LOWEST_VALID_VALUE	550
#define   TOUCH_Y_HIGHEST_VALID_VALUE	3630

static TOUCH_DRIVIER_TYPE TouchData;
static volatile unsigned short RawXData;			//!< Holds raw non filtered X coordinate
static volatile unsigned short RawYData;			//!< Holds raw non filtered Y coordinate
static volatile unsigned short FilteredXData;		//!< Holds filtered X coordinate
static volatile unsigned short FilteredYData;		//!< Holds filtered Y coordinate
static volatile unsigned short IirXData;			//!< temporary filter data for X coordinate
static volatile unsigned short IirYData;			//!< temporary filter data for Y coordinate
static volatile unsigned short Touch1msCnt;			//!< Counter that is used to debounce touch event

unsigned short TouchDriver_CalculateXCord(unsigned short filtered_x);
unsigned short TouchDriver_CalculateYCord(unsigned short filtered_y);
void TouchDriver_ConfigureToReadX(void);
void TouchDriver_ConfigureToReadY(void);
void TouchDriver_ConfigureToDetectTouch(void);
unsigned short TouchDriver_IIRFilter(volatile unsigned short *iir_value, volatile unsigned short new_value, unsigned char alpha_bits);
bool TouchDriver_DetectTouch(void);
unsigned short TouchDriver_GetAdcTouchData(void);

/**
 * @brief Initialize MCU to read analog touch screen data
 *
 * @note This function should be implemented according to proper MCU procedure
 */
void TouchDriver_Initialize(void)
{

//Example on STM32 Cortex-M3
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//    ADC_InitStructure.ADC_NbrOfChannel = 1;
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//    ADC_Init(ADC1, &ADC_InitStructure);
//
//    TouchDriver_ConfigureToReadX();
//    ADC_StartCalibration(ADC1);
//    while(ADC_GetCalibrationStatus(ADC1));
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    Touch1msCnt = 0;
    RawXData = 0;
    RawYData = 0;
    FilteredXData = 0;
    FilteredYData = 0;
    IirXData = 0;
    IirYData = 0;
    TouchData.State = TOUCH_WAITING_FOR_TOUCH;
    TouchData.IsTouchDetected = FALSE;
}

/**
 * @brief TouchDriver module periodic task
 *
 * @note This function need to be called every 1 [ms] to enable proper responsiveness.
 * This time can be increase but this implies touch event debouncing
 */
void TouchDriver_Task(void)
{
	bool is_touch_detected = FALSE;

	TouchDriver_ConfigureToDetectTouch();
	is_touch_detected = !TouchDriver_DetectTouch();

	switch(TouchData.State)
	{
		case TOUCH_WAITING_FOR_TOUCH:
			// Wait for touch event
			if( is_touch_detected == TRUE)
			{
				TouchData.State = TOUCH_DETECT_X;
			}
			break;

		case TOUCH_DETECT_X:
			if( is_touch_detected == TRUE)
			{
				Touch1msCnt++;
				if(Touch1msCnt > TOUCH_FILTER_DEBOUNCE)
				{
					Touch1msCnt = 0;
					TouchData.Xpos = TouchDriver_CalculateXCord(FilteredXData);

					TouchData.State = TOUCH_DETECT_Y;
				}
				else
				{
					TouchDriver_ConfigureToReadX();
					RawXData = TouchDriver_GetAdcTouchData();
					FilteredXData = TouchDriver_IIRFilter(&IirXData, RawXData, TOUCH_ALPHA_BITS);
				}
			}
			else
			{
				TouchData.State = TOUCH_WAITING_FOR_TOUCH;
				TouchData.IsTouchDetected = FALSE;
			}
			break;

		case TOUCH_DETECT_Y:
			if( is_touch_detected == TRUE)
			{
				Touch1msCnt++;
				if(Touch1msCnt > TOUCH_FILTER_DEBOUNCE)
				{
					Touch1msCnt = 0;
					TouchData.Ypos = TouchDriver_CalculateYCord(FilteredYData);
					TouchData.IsTouchDetected = TRUE;
					TouchData.State = TOUCH_WAITING_FOR_TOUCH;
				}
				else
				{
					TouchDriver_ConfigureToReadY();
					RawYData = TouchDriver_GetAdcTouchData();
					FilteredYData = TouchDriver_IIRFilter(&IirYData, RawYData, TOUCH_ALPHA_BITS);
				}
			}
			else
			{
				TouchData.State = TOUCH_WAITING_FOR_TOUCH;
				TouchData.IsTouchDetected = FALSE;
			}
			break;

		default:
			break;
	}
}

/**
 * @brief Check if touch event has been detected
 *
 * @return TRUE, FALSE - bool type
 */
bool TouchDriver_IsTouchDetected(void)
{
	return TouchData.IsTouchDetected;
}

/**
 * @brief Get filtered X coordinate
 *
 * @return TouchData.Xpos - unsigned short
 */
unsigned short TouchDriver_GetX(void)
{
	return TouchData.Xpos;
}

/**
 * @brief Get filtered Y coordinate
 *
 * @return TouchData.Ypos - unsigned short
 */
unsigned short TouchDriver_GetY(void)
{
	return TouchData.Ypos;
}

/**
 * @brief Get non filtered X coordinate
 *
 * @return X coordinate - unsigned short
 */
unsigned short TouchDriver_GetRawX(void)
{
	return TouchDriver_CalculateXCord(RawXData);
}

/**
 * @brief Get non filtered Y coordinate
 *
 * @return Y coordinate - unsigned short
 */
unsigned short TouchDriver_GetRawY(void)
{
	return TouchDriver_CalculateYCord(RawYData);
}

/**
 * @brief Detect touch event by hardware
 *
 * @return TRUE, FALSE - bool type
 *
 * @note This function is hardware dependent and should be implemented according to used MCU
 */
bool TouchDriver_DetectTouch(void)
{
	//TODO read GPIO pin for touch detection, example on STM32 Cortex-M3
//	return (bool) GPIO_ReadInputDataBit(GPIOC, YU);
	return FALSE;
}

/**
 * @brief Get an analog voltage value from touchscreen
 *
 * @return analog value - unsigned short
 *
 * @note This function is hardware dependent and should be implemented according to used MCU
 */
unsigned short TouchDriver_GetAdcTouchData(void)
{

	//TODO read analog voltage value from ADC, example on STM32 Cortex-M3
//	return ADC_GetConversionValue(ADC1);
	return 0;
}

/**
 * @brief Configure MCU to read X position data from touchscreen
 *
 * @details Configure XR and XL GPIO pins to output, YU pin to input analog, YD to input float
 * Set XR to high state, XL to low state, configure A/D converter to read X channel and enable conversion
 */
void TouchDriver_ConfigureToReadX(void)
{
	/*
	//Disable ADC
    ADC_Cmd(ADC1, DISABLE);
    ADC_SoftwareStartConvCmd(ADC1, DISABLE);

	// Configure XR and XL to output
    GPIO_InitStructure.GPIO_Pin = XR | XL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure YU to input analog
    GPIO_InitStructure.GPIO_Pin = YU;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure YD to input float
    GPIO_InitStructure.GPIO_Pin = YD;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //Set XR to high
    GPIO_SetBits(GPIOC, XR);

    //Set XL to low
    GPIO_ResetBits(GPIOC, XL);

    //Configure ADC to read YU
    ADC_RegularChannelConfig(ADC1, Touch_YU, 1, ADC_SampleTime_1Cycles5);

    //Enable ADC conversion
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    */
}

/**
 * @brief Configure MCU to read Y position data from touchscreen
 *
 * @details Configure YU and YD GPIO pins to output, XR pin to input analog, XL to input float
 * Set YU to high state, YD to low state, configure A/D converter to read Y channel and enable conversion
 */
void TouchDriver_ConfigureToReadY(void)
{
	/*
	//Disable ADC
    ADC_Cmd(ADC1, DISABLE);
    ADC_SoftwareStartConvCmd(ADC1, DISABLE);

	// Configure YU and YD to output
    GPIO_InitStructure.GPIO_Pin = YU | YD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure XR to input analog
    GPIO_InitStructure.GPIO_Pin = XR;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure XL to input float
    GPIO_InitStructure.GPIO_Pin = XL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //Set YU to high
    GPIO_SetBits(GPIOC, YU);

    //Set YD to low
    GPIO_ResetBits(GPIOC, YD);

    //Configure ADC to read YU
    ADC_RegularChannelConfig(ADC1, Touch_XR, 1, ADC_SampleTime_1Cycles5);

    //Enable ADC conversion
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    */
}

/**
 * @brief Configure MCU to detect touch event from touchscreen
 *
 * @details Configure XL GPIO pin to output, YU pin to input pullup, XR and YD to input float
 * Set XL to low state
 */
void TouchDriver_ConfigureToDetectTouch(void)
{
	/*
	// Configure XR and YD to input float
    GPIO_InitStructure.GPIO_Pin = XR | YD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure XL to output
    GPIO_InitStructure.GPIO_Pin = XL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    // Configure YU to input pullup
    GPIO_InitStructure.GPIO_Pin = YU;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //Set XL to low
    GPIO_ResetBits(GPIOC, XL);
    */
}

/**
 *  @brief      Determine a filtered value based on an input value.
 *  @details    The floating-point equation for an IIR filter is:
 *              <pre>
 *                  V = (alpha * new_value) + ((1 - alpha) * V)
 *                  alpha is in the range (0..1]
 *              </pre>
 *              The equation can be rewritten as:
 *              <pre>
 *                  V = (alpha * new_value) + V - (alpha * V)
 *                  V = V + (alpha * (new_value - V))
 *              </pre>
 *
 *              This function assumes that alpha is a power of 2 (i.e. 1/2, 1/4, 1/8, etc).
 *              Therefore, alpha can be fully described by the power of 2 or the number of bits
 *              involved.  Refer to the alpha_bits parameter for details.
 *
 *              This function uses fixed-point calculations.  To do this without rounding errors,
 *              the stored value must have more precision than the value used in the application.
 *              The fixed-point equation looks like this:
 *              <pre>
 *                  V = Stored Value
 *                  V = V + (new_value - (V >> alpha_bits))
 *
 *                  va = Value used by the application
 *                  va = Round(V >> alpha_bits)
 *              </pre>
 *
 *  @param      iir_value = A value that stores the current filtered value with additional precision.
 *                      The additional precision required depends on the alpha_bits.
 *  @param      new_value = An input to the filter system with normal precision.
 *  @param      alpha_bits = Exponent of alpha.  alpha = 2 ^ (-alpha_bits).
 *
 *              Sum of new_value resolution and alpha_bits must not be higher than 16 bits
 *
 *  @return     Returns the updated filtered value after rounding.
 */
unsigned short TouchDriver_IIRFilter(volatile unsigned short *iir_value, volatile unsigned short new_value, unsigned char alpha_bits)
{
    *iir_value += new_value - (((*iir_value >> (alpha_bits - 1)) + 1) >> 1);

    return (((*iir_value >> (alpha_bits - 1)) + 1) >> 1);
}

/**
 * @brief Calculate X coordinate from filtered value
 *
 * @details filtered x value need to be biased, linearized and limited
 */
unsigned short TouchDriver_CalculateXCord(unsigned short filtered_x)
{
	if(filtered_x <= TOUCH_X_LOWEST_VALID_VALUE)
	{
		filtered_x = TOUCH_X_LOWEST_VALID_VALUE;
	}
	else if(filtered_x >= TOUCH_X_HIGHEST_VALID_VALUE)
	{
		filtered_x = TOUCH_X_HIGHEST_VALID_VALUE;
	}
	filtered_x -= TOUCH_X_LOWEST_VALID_VALUE;

	return (unsigned short)(H_RES - (unsigned int)(H_RES * filtered_x)/(TOUCH_X_HIGHEST_VALID_VALUE - TOUCH_X_LOWEST_VALID_VALUE) );
}

/**
 * @brief Calculate Y coordinate from filtered value
 *
 * @details filtered y value need to be biased, linearized and limited
 */
unsigned short TouchDriver_CalculateYCord(unsigned short filtered_y)
{
	if(filtered_y <= TOUCH_Y_LOWEST_VALID_VALUE)
	{
		filtered_y = TOUCH_Y_LOWEST_VALID_VALUE;
	}
	else if(filtered_y >= TOUCH_Y_HIGHEST_VALID_VALUE)
	{
		filtered_y = TOUCH_Y_HIGHEST_VALID_VALUE;
	}
	filtered_y -= TOUCH_Y_LOWEST_VALID_VALUE;

	return (unsigned short)( (unsigned int)(V_RES * filtered_y)/(TOUCH_Y_HIGHEST_VALID_VALUE - TOUCH_Y_LOWEST_VALID_VALUE) );
}
