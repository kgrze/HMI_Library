/**
 * @file Gui.h
 *
 * @brief Gui module API.
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#ifndef GUI_H_
#define GUI_H_

#include "../Graphics/Graphics.h"
#include <stdlib.h>

//! Number of Graph data point in the buffer
#define GUI_NUM_OF_GRAPH_DATA		255

//! Maximum absolute graph point value
#define GUI_GRAPH_MAX_VALUE			127

//! Graph refresh rate
#define GUI_GRAPH_REFRESH_RATE		(24/25)		// 25 ms refresh rate

//! Declaration of Event type
typedef void (* GUI_EVENT_TYPE)(void);

//! Text Alignment type, right, left or center
typedef enum
{
	ALIGN_RIGHT = 0,
	ALIGN_LEFT,
	ALIGN_CENTER
} ALIGNMENT_TYPE;

//! Orientation type Horizontal or vertical
typedef enum
{
	HORIZONTAL = 0,
	VERTICAL
} ORIENTATION_TYPE;

//! Event type Click or Release
typedef enum
{
	EVENT_TOUCH_IDLE = 0,
	EVENT_TOUCH_CLICK,
	EVENT_TOUCH_RELEASE,
} TOUCH_EVENT_TYPE;

//! Label type definition
typedef struct
{
	char *String;
	FONT_SIZE_TYPE FontSize;
	unsigned int FontColor;
	bool IsBackground;
	ALIGNMENT_TYPE Align;
	unsigned int BackgroundColor;
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned short Width;
	unsigned short Height;
} GUI_LABEL_TYPE;

//! Default Label type values
#define LABEL_DEFAULT	(GUI_LABEL_TYPE){"", FONT_8P, 0x0000, FALSE, ALIGN_RIGHT, 0xFFFF, 0, 0, 0, 0, 0}

//! Label linked list structure definition
struct LabelListNode
{
	GUI_LABEL_TYPE LabelElement;
	struct LabelListNode *Next;
};
typedef struct LabelListNode GUI_LABEL_LIST_TYPE;

//! Button type definition
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned short Width;
	unsigned short Height;
	GUI_LABEL_TYPE caption;
	unsigned int ButtonColor;
	GUI_EVENT_TYPE OnReleaseEvent;
} GUI_BUTTON_TYPE;

//! Default Button type values
#define BUTTON_DEFAULT	(GUI_BUTTON_TYPE){0, 0, 0, 0, 0, LABEL_DEFAULT, 0x0000, NULL}

//! Button linked list definition
struct ButtonListNode
{
	GUI_BUTTON_TYPE ButtonElement;
	struct ButtonListNode *Next;
};
typedef struct ButtonListNode GUI_BUTTON_LIST_TYPE;

//! Slider button type definition
typedef struct
{
	unsigned short XStart;
	unsigned short XEnd;
	unsigned short YStart;
	unsigned short YEnd;
} GUI_SLIDER_BUTTON_TYPE;

//! Slider button type default values
#define SLIDER_BUTTON_DEFAULT	(GUI_SLIDER_BUTTON_TYPE){0, 0, 0, 0}

//! Slider type definition
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned char Value;
	unsigned short Width;
	unsigned short Height;
	ORIENTATION_TYPE Orientation;
	GUI_SLIDER_BUTTON_TYPE SliderButton;
	unsigned int Color;
	GUI_EVENT_TYPE OnSliderChangeEvent;
} GUI_SLIDER_TYPE;

//! Slider type default values
#define	SLIDER_DEFAULT	(GUI_SLIDER_TYPE){0, 0, 0, 0, 0, 0, HORIZONTAL, SLIDER_BUTTON_DEFAULT, 0x0000, NULL}

//! Slider linker list definition
struct SliderListNode
{
	GUI_SLIDER_TYPE SliderElement;
	struct SliderListNode *Next;
};
typedef struct SliderListNode GUI_SLIDER_LIST_TYPE;

//! Checkbox type definition
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	bool IsChecked;
	unsigned short Size;	//Width = Height
	GUI_EVENT_TYPE OnCheckboxChangeEvent;
} GUI_CHECKBOX_TYPE;

//! Checkbox type default values
#define CHECKBOX_DEFAULT	(GUI_CHECKBOX_TYPE){0, 0, 0, FALSE, 0, NULL}

//! Checkbox linked list definition
struct CheckboxListNode
{
	GUI_CHECKBOX_TYPE CheckboxElement;
	struct CheckboxListNode *Next;
};
typedef struct CheckboxListNode GUI_CHECKBOX_LIST_TYPE;

//!Led type definition
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	bool IsOn;
	unsigned short Size;
} GUI_LED_TYPE;

//! Led type default values
#define LED_DEFAULT		(GUI_LED_TYPE){0, 0, 0, FALSE, 0}

//! Led type linked list definition
struct LedListNode
{
	GUI_LED_TYPE LedElement;
	struct LedListNode *Next;
};
typedef struct LedListNode GUI_LED_LIST_TYPE;

//! Panel type definition
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned short Width;
	unsigned short Height;
	unsigned int Color;
} GUI_PANEL_TYPE;

//! Panel type default values
#define PANEL_DEFAULT	(GUI_PANEL_TYPE){0, 0, 0, 0, 0, 0x0000}

//! Panel type linked list definition
struct PanelListNode
{
	GUI_PANEL_TYPE PanelElement;
	struct PanelListNode *Next;
};
typedef struct PanelListNode GUI_PANEL_LIST_TYPE;

//! TextBox type definition
#define GUI_TEXTBOX_MAX_SIZE		1023		//1kb for textbox string size
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned short Width;
	unsigned short Height;
	char *String;
	unsigned short ScrollIndex;
	FONT_SIZE_TYPE FontSize;
	unsigned int BackgroundColor;
	unsigned int FontColor;
} GUI_TEXTBOX_TYPE;

//! TextBox type default values
#define TEXTBOX_DEFAULT		(GUI_TEXTBOX_TYPE){0, 0, 0, 0, 0, "", 0, FONT_8P, 0xFFFF, 0x0000}

//! Graph type
typedef struct
{
	unsigned char Id;
	unsigned short XPos;
	unsigned short YPos;
	unsigned char Scale;		//0 - 100 %
	unsigned char GraphData[GUI_NUM_OF_GRAPH_DATA];
} GUI_GRAPH_TYPE;

//! Graph type default values
#define GRAPH_DEFAULT	(GUI_GRAPH_TYPE){0, 0, 0, 0, NULL}

//! View type definition is a container of all GUI element lists that can be dynamically changed
typedef struct
{
	bool IsCreated;
	GUI_GRAPH_TYPE *Graph;
	GUI_TEXTBOX_TYPE *TextBox;
	GUI_LABEL_LIST_TYPE *LabelList;
	GUI_BUTTON_LIST_TYPE *ButtonList;
	GUI_PANEL_LIST_TYPE *PanelList;
	GUI_SLIDER_LIST_TYPE *SliderList;
	GUI_CHECKBOX_LIST_TYPE *CheckboxList;
	GUI_LED_LIST_TYPE *LedList;
} GUI_VIEW_TYPE;

//! View type default values
#define VIEW_DEFAULT	(GUI_VIEW_TYPE){FALSE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

GUI_BUTTON_TYPE* 	Gui_NewButton(GUI_VIEW_TYPE *View);
GUI_LABEL_TYPE* 	Gui_NewLabel(GUI_VIEW_TYPE *View);
GUI_SLIDER_TYPE* 	Gui_NewSlider(GUI_VIEW_TYPE *View);
GUI_CHECKBOX_TYPE* 	Gui_NewCheckbox(GUI_VIEW_TYPE *View);
GUI_LED_TYPE*		Gui_NewLed(GUI_VIEW_TYPE *View);
GUI_PANEL_TYPE* 	Gui_NewPanel(GUI_VIEW_TYPE *View);
GUI_GRAPH_TYPE*		Gui_NewGraph(GUI_VIEW_TYPE *View);
GUI_TEXTBOX_TYPE*	Gui_NewTextBox(GUI_VIEW_TYPE *View);

void				Gui_DeleteView(GUI_VIEW_TYPE *View);

void 				Gui_DrawLabel(GUI_LABEL_TYPE *Label);
void 				Gui_DrawButton(GUI_BUTTON_TYPE *Button);
void 				Gui_DrawSlider(GUI_SLIDER_TYPE *Slider);
void 				Gui_DrawCheckbox(GUI_CHECKBOX_TYPE *Checkbox);
void				Gui_DrawLed(GUI_LED_TYPE *Led);
void 				Gui_DrawPanel(GUI_PANEL_TYPE *Panel);
void				Gui_DrawGraph(GUI_GRAPH_TYPE *Graph);
void 				Gui_DrawTextBox(GUI_TEXTBOX_TYPE *TextBox);
void 				Gui_DrawView(GUI_VIEW_TYPE *View);

void				Gui_AddDataToGraph(GUI_GRAPH_TYPE *Graph, unsigned char Data);

void 				Gui_TextBoxClearString(GUI_TEXTBOX_TYPE *TextBox);
void				Gui_TextBoxSetString(GUI_TEXTBOX_TYPE *TextBox, char *string);
void				Gui_TextBoxAddToString(GUI_TEXTBOX_TYPE *TextBox, char *string);
char*				Gui_TextBoxGetStringPointer(void);

void 				Gui_Task(GUI_VIEW_TYPE *View);

char*				Gui_IntToString(char *string, int num);
unsigned int 		Gui_RGB888To565(unsigned char red, unsigned char green, unsigned char blue);

#endif /* GUI_H_ */
