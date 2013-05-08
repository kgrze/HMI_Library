/**
 * @file Gui.c
 *
 * @brief This module implements basic set of GUI elements
 *
 * @details Implementation of Button, Label, Panel, CheckBox, Slider, Led, TextBox and Graph
 *
 * @author Krzysztof Grzeszczak
 *
 * @version 1.0
 *
 * @date 2012-2013
 *
 * @copyright GNU Public License
 */

#ifndef GUI_C_
#define GUI_C_

#include "Gui.h"
#include <string.h>

//! Variable holds constant memory buffer for Integer to String conversion
static char DigitCaption[] = "";

//! Buffer holds constant memory buffer for TextBox
static char StringData[GUI_TEXTBOX_MAX_SIZE];

//! Backup buffer for string in TextBox
static char buff[GUI_TEXTBOX_MAX_SIZE];

static void Gui_DeleteButtonList(GUI_VIEW_TYPE *View);
static void Gui_DeleteLabelList(GUI_VIEW_TYPE *View);
static void Gui_DeleteSliderList(GUI_VIEW_TYPE *View);
static void Gui_DeleteCheckboxList(GUI_VIEW_TYPE *View);
static void Gui_DeleteLedList(GUI_VIEW_TYPE *View);
static void Gui_DeletePanelList(GUI_VIEW_TYPE *View);
static void Gui_DeleteGraph(GUI_VIEW_TYPE *View);
static void Gui_DeleteTextBox(GUI_VIEW_TYPE *View);
static void Gui_DrawSelectedButton(GUI_BUTTON_TYPE *Button);
static unsigned short Gui_GetStringLength(char *string);
static void Gui_ScanButtons(GUI_BUTTON_LIST_TYPE *ButtonList);
static void Gui_ScanSlider(GUI_SLIDER_LIST_TYPE *SliderList);
static void Gui_ScanCheckbox(GUI_CHECKBOX_LIST_TYPE *CheckboxList);
static void Gui_ScanTextBox(GUI_TEXTBOX_TYPE *TextBox);
static char *Gui_itoa(int i, char *s);
static void Gui_RefreshGraph(GUI_GRAPH_TYPE *Graph);

/**
 * @brief Draw a Label type element
 *
 * @param Label - pointer to GUI_LABEL_TYPE type
 */
void Gui_DrawLabel(GUI_LABEL_TYPE *Label)
{
	unsigned short x_step = 0;
	unsigned char i = 0;

	if(Label->IsBackground == TRUE)
	{
		//Draw border
		Graphics_DrawLine(Label->XPos,
						Label->YPos,
						Label->XPos + Label->Width - 1,
						Label->YPos,
						0xFFFF);

		Graphics_DrawLine(Label->XPos + Label->Width - 1,
						Label->YPos,
						Label->XPos + Label->Width - 1,
						Label->YPos + Label->Height - 1,
						0xFFFF);

		Graphics_DrawLine(Label->XPos,
						Label->YPos + Label->Height - 1,
						Label->XPos + Label->Width,
						Label->YPos + Label->Height - 1,
						0x0000);

		Graphics_DrawLine(Label->XPos,
						Label->YPos,
						Label->XPos,
						Label->YPos + Label->Height,
						0x0000);

		//Draw a background Label with a button shape
		Graphics_DrawRect(Label->XPos + 1,
						Label->YPos + 1,
						Label->XPos + Label->Width - 1,
						Label->YPos + Label->Height - 1,
						Label->BackgroundColor);
	}

	if(Label->FontSize == FONT_16P)
	{
		if(Label->Align == ALIGN_LEFT)
		{
			for(x_step = 0, i = 0; Label->String[i] != '\0'; x_step += FONT_16P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 4, Label->String[i], FONT_16P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_RIGHT)
		{
			for(x_step = Label->Width - (FONT_16P_WIDTH * Gui_GetStringLength(Label->String)), i = 0; Label->String[i] != '\0'; x_step += FONT_16P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 4, Label->String[i], FONT_16P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_CENTER)
		{
			for(x_step = Label->Width/2 - (FONT_16P_WIDTH * Gui_GetStringLength(Label->String) / 2), i = 0; Label->String[i] != '\0'; x_step += FONT_16P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 4, Label->String[i], FONT_16P, Label->FontColor);
			}
		}
	}
	else if(Label->FontSize == FONT_12P)
	{
		if(Label->Align == ALIGN_LEFT)
		{
			for(x_step = 0, i = 0; Label->String[i] != '\0'; x_step += FONT_12P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_12P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_RIGHT)
		{
			for(x_step = Label->Width - (FONT_12P_WIDTH * Gui_GetStringLength(Label->String)), i = 0; Label->String[i] != '\0'; x_step += FONT_12P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_12P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_CENTER)
		{
			for(x_step = Label->Width/2 - (FONT_12P_WIDTH * Gui_GetStringLength(Label->String) / 2), i = 0; Label->String[i] != '\0'; x_step += FONT_12P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_12P, Label->FontColor);
			}
		}
	}
	else if(Label->FontSize == FONT_8P)
	{
		if(Label->Align == ALIGN_LEFT)
		{
			for(x_step = 0, i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos, Label->String[i], FONT_8P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_RIGHT)
		{
			for(x_step = Label->Width - (FONT_8P_WIDTH * Gui_GetStringLength(Label->String)), i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos, Label->String[i], FONT_8P, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_CENTER)
		{
			for(x_step = Label->Width/2 - (FONT_8P_WIDTH * Gui_GetStringLength(Label->String) / 2), i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos, Label->String[i], FONT_8P, Label->FontColor);
			}
		}
	}
	else if(Label->FontSize == FONT_8P_BOLD)
	{
		if(Label->Align == ALIGN_LEFT)
		{
			for(x_step = 0, i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_8P_BOLD, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_RIGHT)
		{
			for(x_step = Label->Width - (FONT_8P_WIDTH * Gui_GetStringLength(Label->String)), i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_8P_BOLD, Label->FontColor);
			}
		}
		else if(Label->Align == ALIGN_CENTER)
		{
			for(x_step = Label->Width/2 - (FONT_8P_WIDTH * Gui_GetStringLength(Label->String) / 2), i = 0; Label->String[i] != '\0'; x_step += FONT_8P_WIDTH, i++)
			{
				Graphics_DrawChar(Label->XPos + x_step, Label->YPos - 2, Label->String[i], FONT_8P_BOLD, Label->FontColor);
			}
		}
	}
}

/**
 * @brief Draw a Button type element
 *
 * @param Button - pointer to GUI_BUTTON_TYPE type
 */
void Gui_DrawButton(GUI_BUTTON_TYPE *Button)
{
	//First draw border of a Button
	Graphics_DrawLine(Button->XPos,
					Button->YPos,
					Button->XPos + Button->Width - 1,
					Button->YPos,
					0x0000);

	Graphics_DrawLine(Button->XPos + Button->Width - 1,
					Button->YPos,
					Button->XPos + Button->Width - 1,
					Button->YPos + Button->Height - 1,
					0x0000);

	Graphics_DrawLine(Button->XPos,
					Button->YPos + Button->Height - 1,
					Button->XPos + Button->Width,
					Button->YPos + Button->Height - 1,
					0xFFFF);

	Graphics_DrawLine(Button->XPos,
					Button->YPos,
					Button->XPos,
					Button->YPos + Button->Height,
					0xFFFF);

	//Draw a filler rectangle with a button shape
	Graphics_DrawRect(Button->XPos + 1,
					Button->YPos + 1,
					Button->XPos + Button->Width - 1,
					Button->YPos + Button->Height - 1,
					Button->ButtonColor);

	Button->caption.Align = ALIGN_LEFT;

	//Put a caption label directly in the center of button
	if(Button->caption.FontSize == FONT_16P)
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_16P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2);
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_16P_HEIGHT/2;
	}
	else if(Button->caption.FontSize == FONT_12P)
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_12P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2);
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_12P_HEIGHT/2;
	}
	else if( (Button->caption.FontSize == FONT_8P) || (Button->caption.FontSize == FONT_8P_BOLD) )
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_8P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2);
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_8P_HEIGHT/2;
	}
	Gui_DrawLabel(&Button->caption);
}

/**
 * @brief Draw a selected Button element
 *
 * @param Button - pointer to GUI_BUTTON_TYPE type
 */
void Gui_DrawSelectedButton(GUI_BUTTON_TYPE *Button)
{
	//First draw border of a Button
	Graphics_DrawLine(Button->XPos,
					Button->YPos,
					Button->XPos + Button->Width - 1,
					Button->YPos,
					0x0000);

	Graphics_DrawLine(Button->XPos,
					Button->YPos + 1,
					Button->XPos + Button->Width - 1,
					Button->YPos + 1,
					0x0000);

	Graphics_DrawLine(Button->XPos + Button->Width - 1,
					Button->YPos,
					Button->XPos + Button->Width - 1,
					Button->YPos + Button->Height - 1,
					0x0000);

	Graphics_DrawLine(Button->XPos + Button->Width - 2,
					Button->YPos,
					Button->XPos + Button->Width - 2,
					Button->YPos + Button->Height - 1,
					0x0000);

	Graphics_DrawLine(Button->XPos,
					Button->YPos + Button->Height - 1,
					Button->XPos + Button->Width,
					Button->YPos + Button->Height - 1,
					0x0000);

	Graphics_DrawLine(Button->XPos,
					Button->YPos + Button->Height - 2,
					Button->XPos + Button->Width - 2,
					Button->YPos + Button->Height - 2,
					0xFFFF);

	Graphics_DrawLine(Button->XPos,
					Button->YPos,
					Button->XPos,
					Button->YPos + Button->Height,
					0x0000);

	Graphics_DrawLine(Button->XPos + 1,
					Button->YPos + 2,
					Button->XPos + 1,
					Button->YPos + Button->Height - 1,
					0xFFFF);

	//Draw a filler rectangle with a button shape
	Graphics_DrawRect(Button->XPos + 2,
					Button->YPos + 2,
					Button->XPos + Button->Width - 2,
					Button->YPos + Button->Height - 2,
					Button->ButtonColor);

	//Put a caption label directly in the center of button
	if(Button->caption.FontSize == FONT_16P)
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_16P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2) + 1;
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_16P_HEIGHT/2 - 1;
	}
	else if(Button->caption.FontSize == FONT_12P)
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_12P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2) + 1;
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_12P_HEIGHT/2 - 1;
	}
	else if( (Button->caption.FontSize == FONT_8P) || (Button->caption.FontSize == FONT_8P_BOLD) )
	{
		Button->caption.XPos = Button->XPos + Button->Width/2 - (FONT_8P_WIDTH * Gui_GetStringLength(Button->caption.String) / 2) + 1;
		Button->caption.YPos = Button->YPos + Button->Height/2 - FONT_8P_HEIGHT/2 - 1;
	}
	Gui_DrawLabel(&Button->caption);
}

/**
 * @brief Draw a Slider type element
 *
 * @param Slider - pointer to GUI_SLIDER_TYPE type
 */
void Gui_DrawSlider(GUI_SLIDER_TYPE *Slider)
{
	unsigned short slider_length = 0;
	unsigned short slider_position = 0;
	unsigned short slider_outline_x_start = 0;
	unsigned short slider_outline_y_start = 0;
	unsigned short slider_outline_x_end = 0;
	unsigned short slider_outline_y_end = 0;
	unsigned short slider_center_line_x_start = 0;
	unsigned short slider_center_line_y_start = 0;
	unsigned short slider_center_line_x_end = 0;
	unsigned short slider_center_line_y_end = 0;

	if(Slider->Orientation == HORIZONTAL)
	{
		slider_outline_x_start = Slider->XPos + 5;
		slider_outline_y_start = Slider->YPos + ( (Slider->Height/2) - 2);
		slider_outline_x_end = Slider->XPos + (Slider->Width - 5);
		slider_outline_y_end = Slider->YPos + ( (Slider->Height/2) + 2);

		slider_center_line_x_start = Slider->XPos + 7;
		slider_center_line_y_start = Slider->YPos + (Slider->Height/2);
		slider_center_line_x_end = Slider->XPos + (Slider->Width - 7);
		slider_center_line_y_end = Slider->YPos + (Slider->Height/2);

		slider_length = slider_outline_x_end - slider_outline_x_start;
		slider_position = (Slider->Value * slider_length + 1) / 100;

		Slider->SliderButton.XStart = Slider->XPos + slider_position;
		Slider->SliderButton.XEnd = Slider->XPos + slider_position + 10;
		Slider->SliderButton.YStart = Slider->YPos;
		Slider->SliderButton.YEnd = Slider->YPos + Slider->Height - 1;
	}
	else
	{
		//Slider->Orientation = VERTICAL
		slider_outline_x_start = Slider->XPos + ( (Slider->Width/2) - 2);
		slider_outline_y_start = Slider->YPos + 5;
		slider_outline_x_end = Slider->XPos + ( (Slider->Width/2) + 2);
		slider_outline_y_end = Slider->YPos + (Slider->Height - 5);

		slider_center_line_x_start = Slider->XPos + (Slider->Width/2);
		slider_center_line_y_start = Slider->YPos + 7;
		slider_center_line_x_end = Slider->XPos + (Slider->Width/2);
		slider_center_line_y_end = Slider->YPos + (Slider->Height - 7);

		slider_length = slider_outline_y_end - slider_outline_y_start;
		slider_position = (Slider->Value * slider_length + 1) / 100;

		Slider->SliderButton.XStart = Slider->XPos;
		Slider->SliderButton.YStart = Slider->YPos + slider_position;
		Slider->SliderButton.XEnd = Slider->XPos + Slider->Width - 1;
		Slider->SliderButton.YEnd = Slider->YPos + slider_position + 10;
	}

	//First draw Slider background
	Graphics_DrawRect(Slider->XPos,
						Slider->YPos,
						Slider->XPos + Slider->Width + 1,
						Slider->YPos + Slider->Height + 1,
						Slider->Color);

	//Calculate slider line postion, width and height
	Graphics_DrawLine(slider_outline_x_start,
						slider_outline_y_start,
						slider_outline_x_start,
						slider_outline_y_end,
						0x0000);

	Graphics_DrawLine(slider_outline_x_start,
						slider_outline_y_end,
						slider_outline_x_end,
						slider_outline_y_end,
						0x0000);

	Graphics_DrawLine(slider_outline_x_end,
						slider_outline_y_end,
						slider_outline_x_end,
						slider_outline_y_start,
						0xFFFF);

	Graphics_DrawLine(slider_outline_x_end,
						slider_outline_y_start,
						slider_outline_x_start,
						slider_outline_y_start,
						0xFFFF);
	//Draw a center line
	Graphics_DrawLine(slider_center_line_x_start,
						slider_center_line_y_start,
						slider_center_line_x_end,
						slider_center_line_y_end,
						0x0000);

	//Draw slider button

	Graphics_DrawLine(Slider->SliderButton.XStart,
						Slider->SliderButton.YStart,
						Slider->SliderButton.XEnd,
						Slider->SliderButton.YStart,
						0x0000);

	Graphics_DrawLine(Slider->SliderButton.XEnd,
						Slider->SliderButton.YStart,
						Slider->SliderButton.XEnd,
						Slider->SliderButton.YEnd,
						0x0000);

	Graphics_DrawLine(Slider->SliderButton.XEnd,
						Slider->SliderButton.YEnd,
						Slider->SliderButton.XStart,
						Slider->SliderButton.YEnd,
						0xFFFF);

	Graphics_DrawLine(Slider->SliderButton.XStart,
						Slider->SliderButton.YEnd,
						Slider->SliderButton.XStart,
						Slider->SliderButton.YStart,
						0xFFFF);

	Graphics_DrawRect(Slider->SliderButton.XStart + 1,
						Slider->SliderButton.YStart + 1,
						Slider->SliderButton.XEnd,
						Slider->SliderButton.YEnd,
						Slider->Color);
}

/**
 * @brief Draw a CheckBox type element
 *
 * @param Checkbox - pointer to GUI_CHECKBOX_TYPE type
 */
void Gui_DrawCheckbox(GUI_CHECKBOX_TYPE *Checkbox)
{
	//Draw outline of two black lines on the left and upper side of checkbox
	Graphics_DrawLine(Checkbox->XPos,
						Checkbox->YPos,
						Checkbox->XPos,
						Checkbox->YPos + Checkbox->Size,
						0x0000);

	Graphics_DrawLine(Checkbox->XPos,
						Checkbox->YPos + Checkbox->Size,
						Checkbox->XPos + Checkbox->Size,
						Checkbox->YPos + Checkbox->Size,
						0x0000);

	//Draw rectangle filled with white color
	Graphics_DrawRect(Checkbox->XPos + 1,
						Checkbox->YPos,
						Checkbox->XPos + Checkbox->Size,
						Checkbox->YPos + Checkbox->Size - 1,
						0xFFFF);

	//If checkbox is checked an 'x' mark in the center
	if(Checkbox->IsChecked == TRUE)
	{
		Graphics_DrawLine(Checkbox->XPos + 3,
							Checkbox->YPos + 3,
							Checkbox->XPos + Checkbox->Size - 3,
							Checkbox->YPos + Checkbox->Size - 3,
							0x0000);
		Graphics_DrawLine(Checkbox->XPos + 4,
							Checkbox->YPos + 3,
							Checkbox->XPos + Checkbox->Size - 2,
							Checkbox->YPos + Checkbox->Size - 3,
							0x0000);

		Graphics_DrawLine(Checkbox->XPos + Checkbox->Size - 3,
							Checkbox->YPos + 3,
							Checkbox->XPos + 3,
							Checkbox->YPos + Checkbox->Size - 3,
							0x0000);
		Graphics_DrawLine(Checkbox->XPos + Checkbox->Size - 4,
							Checkbox->YPos + 3,
							Checkbox->XPos + 2,
							Checkbox->YPos + Checkbox->Size - 3,
							0x0000);
	}
}

/**
 * @brief Draw a Led type element
 *
 * @param Led - pointer to GUI_LED_TYPE type
 */
void Gui_DrawLed(GUI_LED_TYPE *Led)
{
	unsigned int color = 0;

	//Draw outline of two black lines on the left and upper side of checkbox
	Graphics_DrawLine(Led->XPos,
						Led->YPos,
						Led->XPos,
						Led->YPos + Led->Size,
						0x0000);

	Graphics_DrawLine(Led->XPos,
						Led->YPos + Led->Size,
						Led->XPos + Led->Size,
						Led->YPos + Led->Size,
						0x0000);

	Graphics_DrawLine(Led->XPos + Led->Size,
						Led->YPos + Led->Size,
						Led->XPos + Led->Size,
						Led->YPos,
						0xFFFF);

	Graphics_DrawLine(Led->XPos + Led->Size,
						Led->YPos,
						Led->XPos,
						Led->YPos,
						0xFFFF);

	//Draw rectangle filled with background color
	Graphics_DrawRect(Led->XPos + 1,
						Led->YPos + 1,
						Led->XPos + Led->Size - 1,
						Led->YPos + Led->Size - 1,
						Gui_RGB888To565(0xCC, 0xCC, 0xCC));

	//Draw inner line of two white lines on the left and upper side of checkbox
	Graphics_DrawLine(Led->XPos + 3,
						Led->YPos + 3,
						Led->XPos + 3,
						Led->YPos + Led->Size - 3,
						0x0000);

	Graphics_DrawLine(Led->XPos + 3,
						Led->YPos + Led->Size - 3,
						Led->XPos + Led->Size - 3,
						Led->YPos + Led->Size - 3,
						0x0000);

	Graphics_DrawLine(Led->XPos + Led->Size - 3,
						Led->YPos + Led->Size - 3,
						Led->XPos + Led->Size - 3,
						Led->YPos + 2,
						0x0000);

	Graphics_DrawLine(Led->XPos + Led->Size - 3,
						Led->YPos + 3,
						Led->XPos + 3,
						Led->YPos + 3,
						0x0000);

	//Draw rectangle filled with green color according to IsOn state
	if(Led->IsOn == FALSE)
	{
		color = Gui_RGB888To565(0x00, 0x64, 0x00);	//Led is off, dark green
	}
	else
	{
		color = Gui_RGB888To565(0x00, 0xFF, 0x00);	//Led is on, normal green
	}
	Graphics_DrawRect(Led->XPos + 4,
						Led->YPos + 4,
						Led->XPos + Led->Size - 3,
						Led->YPos + Led->Size - 3,
						color);
}

/**
 * @brief Draw a Panel type element
 *
 * @param Panel - pointer to GUI_PANEL_TYPE type
 */
void Gui_DrawPanel(GUI_PANEL_TYPE *Panel)
{
	//Draw border
	Graphics_DrawLine(Panel->XPos,
					Panel->YPos,
					Panel->XPos + Panel->Width - 1,
					Panel->YPos,
					0xFFFF);

	Graphics_DrawLine(Panel->XPos + Panel->Width - 1,
					Panel->YPos,
					Panel->XPos + Panel->Width - 1,
					Panel->YPos + Panel->Height - 1,
					0xFFFF);

	Graphics_DrawLine(Panel->XPos,
					Panel->YPos + Panel->Height - 1,
					Panel->XPos + Panel->Width,
					Panel->YPos + Panel->Height - 1,
					0x0000);

	Graphics_DrawLine(Panel->XPos,
					Panel->YPos,
					Panel->XPos,
					Panel->YPos + Panel->Height,
					0x0000);

	//Draw a background Label with a button shape
	Graphics_DrawRect(Panel->XPos + 1,
					Panel->YPos + 1,
					Panel->XPos + Panel->Width - 1,
					Panel->YPos + Panel->Height - 1,
					Panel->Color);
}

/**
 * @brief Draw a Graph type element
 *
 * @param Graph - pointer to GUI_GRAPH_TYPE type
 */
void Gui_DrawGraph(GUI_GRAPH_TYPE *Graph)
{
	//Draw Graph outline
	Graphics_DrawRect(Graph->XPos,
						Graph->YPos,
						Graph->XPos + GUI_NUM_OF_GRAPH_DATA,
						Graph->YPos + GUI_GRAPH_MAX_VALUE + 1,
						Gui_RGB888To565(0xCC, 0xCC, 0xCC));

	Graphics_DrawLine(Graph->XPos - 1,
							Graph->YPos - 1,
							Graph->XPos - 1,
							Graph->YPos + GUI_GRAPH_MAX_VALUE + 1,
							0x0000);

	Graphics_DrawLine(Graph->XPos - 1,
						Graph->YPos + GUI_GRAPH_MAX_VALUE + 1,
						Graph->XPos + GUI_NUM_OF_GRAPH_DATA,
						Graph->YPos + GUI_GRAPH_MAX_VALUE + 1,
						0x0000);

	Graphics_DrawLine(Graph->XPos + GUI_NUM_OF_GRAPH_DATA,
						Graph->YPos + GUI_GRAPH_MAX_VALUE + 1,
						Graph->XPos + GUI_NUM_OF_GRAPH_DATA,
						Graph->YPos - 1,
						0x0000);

	Graphics_DrawLine(Graph->XPos + GUI_NUM_OF_GRAPH_DATA,
						Graph->YPos - 1,
						Graph->XPos - 1,
						Graph->YPos - 1,
						0x0000);
}

/**
 * @brief Draw a TextBox type element
 *
 * @param Graph - pointer to GUI_TEXTBOX_TYPE type
 */
void Gui_DrawTextBox(GUI_TEXTBOX_TYPE *TextBox)
{
	unsigned short start_visible_char_index = 0;
	unsigned short end_visible_char_index = 0;
	unsigned short num_of_char_per_line = 0;
	unsigned short num_of_visible_lines = 0;
	unsigned char font_width = 0;
	unsigned char font_height = 0;
	unsigned char font_gap = 0;
	unsigned short x_step = 0;
	unsigned short y_step = 0;
	unsigned short i = 0;

	//Draw border
	Graphics_DrawLine(TextBox->XPos,
					TextBox->YPos,
					TextBox->XPos + TextBox->Width - 1,
					TextBox->YPos,
					0xFFFF);

	Graphics_DrawLine(TextBox->XPos + TextBox->Width - 1,
					TextBox->YPos,
					TextBox->XPos + TextBox->Width - 1,
					TextBox->YPos + TextBox->Height - 1,
					0xFFFF);

	Graphics_DrawLine(TextBox->XPos,
					TextBox->YPos + TextBox->Height - 1,
					TextBox->XPos + TextBox->Width,
					TextBox->YPos + TextBox->Height - 1,
					0x0000);

	Graphics_DrawLine(TextBox->XPos,
					TextBox->YPos,
					TextBox->XPos,
					TextBox->YPos + TextBox->Height,
					0x0000);

	//Draw a background Label with a button shape
	Graphics_DrawRect(TextBox->XPos + 1,
					TextBox->YPos + 1,
					TextBox->XPos + TextBox->Width - 1,
					TextBox->YPos + TextBox->Height - 1,
					TextBox->BackgroundColor);

	switch(TextBox->FontSize)
	{
	case FONT_8P:
		font_width = FONT_8P_WIDTH;
		font_height = FONT_8P_HEIGHT;
		font_gap = 0;
		break;
	case FONT_8P_BOLD:
		font_width = FONT_8P_WIDTH;
		font_height = FONT_8P_HEIGHT;
		font_gap = 2;
		break;
	case FONT_12P:
		font_width = FONT_12P_WIDTH;
		font_height = FONT_12P_HEIGHT;
		font_gap = 2;
		break;
	case FONT_16P:
		font_width = FONT_16P_WIDTH;
		font_height = FONT_16P_HEIGHT;
		font_gap = 4;
		break;
	}

	num_of_visible_lines = TextBox->Height / font_height;
	num_of_char_per_line = TextBox->Width / font_width;
	start_visible_char_index = TextBox->ScrollIndex * num_of_char_per_line;
	end_visible_char_index = (num_of_visible_lines + TextBox->ScrollIndex) * num_of_char_per_line;

	for(x_step = 0, i = start_visible_char_index;
			(TextBox->String[i] != '\0') && (i < end_visible_char_index);
			x_step += font_width, i++)
	{
		//Draw only visible part of text
		if( (i % num_of_char_per_line) == 0)
		{
			//Jum to beginning of new line
			y_step += font_height;
			x_step = 0;
		}

		Graphics_DrawChar(TextBox->XPos + x_step + 2,
							TextBox->YPos + TextBox->Height - font_gap - y_step,
							TextBox->String[i],
							TextBox->FontSize,
							TextBox->FontColor);
	}
}

/**
 * @brief Clear all elements of string in TextBox
 *
 * @param TextBox - pointer to GUI_TEXTBOX_TYPE type
 *
 * @result All elements of TextBox->String[] will have value of 0.
 */
void Gui_TextBoxClearString(GUI_TEXTBOX_TYPE *TextBox)
{
	memset(TextBox->String, 0, GUI_TEXTBOX_MAX_SIZE);
	TextBox->ScrollIndex = 0;
}

/**
 * @brief Add string to existing string inside TextBox
 *
 * @param TextBox - pointer to GUI_TEXTBOX_TYPE type
 *
 * @param string - points to char array that will be concatenated with existing TextBox string
 *
 * @result New string will be added at the end of existing string inside TextBox element
 */
void Gui_TextBoxAddToString(GUI_TEXTBOX_TYPE *TextBox, char *string)
{
	unsigned short i = 0, j = 0;
	unsigned short num_of_char_per_line = 0;
	unsigned short num_of_visible_lines = 0;
	unsigned char font_width = 0;
	unsigned char font_height = 0;

	if( (Gui_GetStringLength(TextBox->String) + Gui_GetStringLength(string)) >= GUI_TEXTBOX_MAX_SIZE)
	{
		Gui_TextBoxClearString(TextBox);
	}

	//Count index of the last element
	while(TextBox->String[i] != '\0')
	{
		i++;
	}

	//Copy new string at the end of existing
	while(string[j] != '\0')
	{
		TextBox->String[i] = string[j];
		i++;
		j++;
	}
	TextBox->String[i] = '\0';

	switch(TextBox->FontSize)
	{
	case FONT_8P:
		font_width = FONT_8P_WIDTH;
		font_height = FONT_8P_HEIGHT;
		break;
	case FONT_8P_BOLD:
		font_width = FONT_8P_WIDTH;
		font_height = FONT_8P_HEIGHT;
		break;
	case FONT_12P:
		font_width = FONT_12P_WIDTH;
		font_height = FONT_12P_HEIGHT;
		break;
	case FONT_16P:
		font_width = FONT_16P_WIDTH;
		font_height = FONT_16P_HEIGHT;
		break;
	}

	num_of_visible_lines = TextBox->Height / font_height;
	num_of_char_per_line = TextBox->Width / font_width;
	if( (Gui_GetStringLength(TextBox->String)/num_of_char_per_line) >= num_of_visible_lines)
	{
		TextBox->ScrollIndex++;
	}

	Gui_TextBoxSetString(TextBox, TextBox->String);
}

/**
 * @brief Get the pointer to a memory buffer that holds TextBox's string data
 *
 * @return pointer to char
 */
char* Gui_TextBoxGetStringPointer(void)
{
	return StringData;
}

/**
 * @brief Set the string to TextBox element
 *
 * @param TextBox - pointer to GUI_TEXTBOX_TYPE type
 *
 * @param string - pointer to char to be placed inside TextBox
 */
void Gui_TextBoxSetString(GUI_TEXTBOX_TYPE *TextBox, char *string)
{
	unsigned char font_width = 0;
	unsigned short dest_index = 0;
	unsigned short source_index = 0;
	unsigned short num_of_char_per_line = 0;

	switch(TextBox->FontSize)
	{
	case FONT_8P:
		font_width = FONT_8P_WIDTH;
		break;
	case FONT_8P_BOLD:
		font_width = FONT_8P_WIDTH;
		break;
	case FONT_12P:
		font_width = FONT_12P_WIDTH;
		break;
	case FONT_16P:
		font_width = FONT_16P_WIDTH;
		break;
	}

	//Copy string to buff
	strcpy(buff, string);

	num_of_char_per_line = TextBox->Width / font_width;

	for(dest_index = 0, source_index = 0; (buff[source_index] != '\0') || (dest_index < GUI_TEXTBOX_MAX_SIZE); source_index++)
	{
		//Copy buff to TextBox->string with respect to newline char \n
		if(buff[source_index] == '\n')
		{
			//Rest of text will be draw in another line. In order to do that we need to fill rest of the line with spaces
			while(dest_index < num_of_char_per_line)
			{
				TextBox->String[dest_index++] = ' ';
			}
			num_of_char_per_line += (TextBox->Width / font_width);
		}
		else
		{
			if(dest_index > num_of_char_per_line)
			{
				num_of_char_per_line += (TextBox->Width / font_width);
			}
			TextBox->String[dest_index++] = buff[source_index];
		}
	};
}

/**
 * @brief Adds new data to Graph element
 *
 * @param Graph - pointer to GUI_GRAPH_TYPE type
 *
 * @param data - unsigned char type
 *
 * @result data will be placed at the beginning of Graph element's queue (FIFO) array
 */
void Gui_AddDataToGraph(GUI_GRAPH_TYPE *Graph, unsigned char data)
{
	unsigned char i = 0;

	data = (unsigned char)(((unsigned short)(Graph->Scale * data) )/ 100);

	//limit data
	if(data > GUI_GRAPH_MAX_VALUE)
	{
		data = GUI_GRAPH_MAX_VALUE;
	}

	// All other data points need to be shifted
	for(i = 0; i < GUI_NUM_OF_GRAPH_DATA - 1; i++)
	{
		Graph->GraphData[i] = Graph->GraphData[i + 1];
	}

	// New data is added at the rear side of queue (FIFO) graph data table
	Graph->GraphData[GUI_NUM_OF_GRAPH_DATA - 1] = data;
}

/**
 * @brief Redraw Graph at define refresh rate
 *
 * @param Graph - pointer to GUI_GRAPH_TYPE type
 */
void Gui_RefreshGraph(GUI_GRAPH_TYPE *Graph)
{
	unsigned short i = 0;
	static unsigned int RefreshCnt = 0;
	static unsigned char PreviousData[GUI_NUM_OF_GRAPH_DATA];
	// Draw plot

	if(RefreshCnt++ >= GUI_GRAPH_REFRESH_RATE)
	{
		RefreshCnt = 0;
		for(i = 0; Graph != NULL, i < GUI_NUM_OF_GRAPH_DATA; i++)
		{
			GraphicDriver_DrawPoint(Graph->XPos + i,
											Graph->YPos + PreviousData[i],
											Gui_RGB888To565(0xCC, 0xCC, 0xCC));

			GraphicDriver_DrawPoint(Graph->XPos + i,
									Graph->YPos + Graph->GraphData[i],
									0xF800);

			PreviousData[i] = Graph->GraphData[i];
		}
	}
}

/**
 * @brief Add new Label element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Label list
 *
 * @return - pointer to newly created GUI_LABEL_TYPE type element
 */
GUI_LABEL_TYPE* Gui_NewLabel(GUI_VIEW_TYPE *View)
{
	GUI_LABEL_LIST_TYPE *NewNode = NULL;
	GUI_LABEL_TYPE LabelDefault = LABEL_DEFAULT;
	static unsigned char LabelId = 1;

	NewNode = malloc(sizeof(GUI_LABEL_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->LabelElement = LabelDefault;				//set a new value
		NewNode->LabelElement.Id = LabelId++;
		NewNode->Next = View->LabelList;					//next element will point at the end of actual list
	}

	View->LabelList = NewNode;								//assign to previous list (list), new update list (new_node)

	return (GUI_LABEL_TYPE*) &NewNode->LabelElement;
}

/**
 * @brief Delete Label list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Label list elements will be deallocated and free to reuse again
 */
void Gui_DeleteLabelList(GUI_VIEW_TYPE *View)
{
	//delete every label in the list
	for(; View->LabelList != NULL; View->LabelList = View->LabelList->Next)
	{
		free(&(View->LabelList->LabelElement));
	}
}

/**
 * @brief Add new Button element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Button list
 *
 * @return - pointer to newly created GUI_BUTTON_TYPE type element
 */
GUI_BUTTON_TYPE* Gui_NewButton(GUI_VIEW_TYPE *View)
{
	GUI_BUTTON_LIST_TYPE *NewNode = NULL;
	GUI_BUTTON_TYPE ButtonDefault = BUTTON_DEFAULT;
	static unsigned char ButtonId = 1;

	NewNode = malloc(sizeof(GUI_BUTTON_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->ButtonElement = ButtonDefault;			//set a new value
		NewNode->Next = View->ButtonList;				//next element will point at the end of actual list
		NewNode->ButtonElement.Id = ButtonId++;
	}

	View->ButtonList = NewNode;							//assign to previous list (list), new update list (new_node)

	return (GUI_BUTTON_TYPE*) &NewNode->ButtonElement;
}

/**
 * @brief Delete Button list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Button list elements will be deallocated and free to reuse again
 */
void Gui_DeleteButtonList(GUI_VIEW_TYPE *View)
{
	//delete every button in the list
	for(; View->ButtonList != NULL; View->ButtonList = View->ButtonList->Next)
	{
		free(&(View->ButtonList->ButtonElement));
	}
}

/**
 * @brief Add new Slider element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Slider list
 *
 * @return - pointer to newly created GUI_SLIDER_TYPE type element
 */
GUI_SLIDER_TYPE* Gui_NewSlider(GUI_VIEW_TYPE *View)
{
	GUI_SLIDER_LIST_TYPE *NewNode = NULL;
	GUI_SLIDER_TYPE SliderDefault = SLIDER_DEFAULT;
	static unsigned char SliderId = 1;

	NewNode = malloc(sizeof(GUI_SLIDER_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->SliderElement = SliderDefault;		//set a new value
		NewNode->SliderElement.Id = SliderId++;
		NewNode->Next = View->SliderList;		//next element will point at the end of actual list
	}

	View->SliderList = NewNode;				//assign to previous list (list), new update list (new_node)

	return (GUI_SLIDER_TYPE*) &NewNode->SliderElement;
}

/**
 * @brief Delete Slider list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Slider list elements will be deallocated and free to reuse again
 */
void Gui_DeleteSliderList(GUI_VIEW_TYPE *View)
{
	//delete every slider in the list
	for(; View->SliderList != NULL; View->SliderList = View->SliderList->Next)
	{
		free(&(View->SliderList->SliderElement));
	}
}

/**
 * @brief Add new Checkbox element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Checkbox list
 *
 * @return - pointer to newly created GUI_CHECKBOX_TYPE type element
 */
GUI_CHECKBOX_TYPE* Gui_NewCheckbox(GUI_VIEW_TYPE *View)
{
	GUI_CHECKBOX_LIST_TYPE *NewNode = NULL;
	GUI_CHECKBOX_TYPE CheckboxDefault = CHECKBOX_DEFAULT;
	static unsigned char CheckboxId = 1;

	NewNode = malloc(sizeof(GUI_CHECKBOX_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->CheckboxElement = CheckboxDefault;		//set a new value
		NewNode->CheckboxElement.Id = CheckboxId++;
		NewNode->Next = View->CheckboxList;		//next element will point at the end of actual list
	}

	View->CheckboxList = NewNode;				//assign to previous list (list), new update list (new_node)

	return (GUI_CHECKBOX_TYPE*) &NewNode->CheckboxElement;
}

/**
 * @brief Delete Checkbox list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Checkbox list elements will be deallocated and free to reuse again
 */
void Gui_DeleteCheckboxList(GUI_VIEW_TYPE *View)
{
	//delete every checkbox in the list
	for(; View->CheckboxList != NULL; View->CheckboxList = View->CheckboxList->Next)
	{
		free(&(View->CheckboxList->CheckboxElement));
	}
}

/**
 * @brief Add new Led element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Led list
 *
 * @return - pointer to newly created GUI_LED_TYPE type element
 */
GUI_LED_TYPE* Gui_NewLed(GUI_VIEW_TYPE *View)
{
	GUI_LED_LIST_TYPE *NewNode = NULL;
	GUI_LED_TYPE LedDefault = LED_DEFAULT;
	static unsigned char LedId = 1;

	NewNode = malloc(sizeof(GUI_LED_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->LedElement = LedDefault;		//set a new value
		NewNode->LedElement.Id = LedId++;
		NewNode->Next = View->LedList;		//next element will point at the end of actual list
	}

	View->LedList = NewNode;				//assign to previous list (list), new update list (new_node)

	return (GUI_LED_TYPE*) &NewNode->LedElement;
}

/**
 * @brief Delete Led list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Led list elements will be deallocated and free to reuse again
 */
void Gui_DeleteLedList(GUI_VIEW_TYPE *View)
{
	//delete every Led in the list
	for(; View->LedList != NULL; View->LedList = View->LedList->Next)
	{
		free(&(View->LedList->LedElement));
	}
}

/**
 * @brief Add new Panel element to the list in View
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Panel list
 *
 * @return - pointer to newly created GUI_PANEL_TYPE type element
 */
GUI_PANEL_TYPE* Gui_NewPanel(GUI_VIEW_TYPE *View)
{
	GUI_PANEL_LIST_TYPE *NewNode = NULL;
	GUI_PANEL_TYPE PanelDefault = PANEL_DEFAULT;
	static unsigned char PanelId = 1;

	NewNode = malloc(sizeof(GUI_PANEL_LIST_TYPE));
	if(NewNode == NULL)
	{
		//not enough memory to allocate or allocation error
		return NULL;
	}
	else
	{
		NewNode->PanelElement = PanelDefault;		//set a new value
		NewNode->PanelElement.Id = PanelId++;
		NewNode->Next = View->PanelList;		//next element will point at the end of actual list
	}

	View->PanelList = NewNode;				//assign to previous list (list), new update list (new_node)

	return (GUI_PANEL_TYPE*) &NewNode->PanelElement;
}

/**
 * @brief Delete Panel list in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Panel list elements will be deallocated and free to reuse again
 */
void Gui_DeletePanelList(GUI_VIEW_TYPE *View)
{
	//delete every Panel in the list
	for(; View->PanelList != NULL; View->PanelList = View->PanelList->Next)
	{
		free(&(View->PanelList->PanelElement));
	}
}

/**
 * @brief Create new Graph type element
 *
 * @param View - pointer to GUI_VIEW_TYPE type containing Graph element
 *
 * @return - pointer to newly created GUI_GRAPH_TYPE type element
 *
 * @note There is no Graph list since there will be no more memory to allocate Graph data buffer everytime
 */
GUI_GRAPH_TYPE*	Gui_NewGraph(GUI_VIEW_TYPE *View)
{
	GUI_GRAPH_TYPE *NewGraph;
	GUI_GRAPH_TYPE GraphDefault = GRAPH_DEFAULT;
	NewGraph = malloc(sizeof(GUI_GRAPH_TYPE));

	if(NewGraph ==  NULL)
	{
		return NULL;
	}
	else
	{
		*NewGraph = GraphDefault;
		memset(NewGraph->GraphData, 0, GUI_NUM_OF_GRAPH_DATA);
		View->Graph = NewGraph;

		return (GUI_GRAPH_TYPE*)NewGraph;
	}
}

/**
 * @brief Delete Graph element in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of Graph element will be deallocated and free to reuse again
 */
void Gui_DeleteGraph(GUI_VIEW_TYPE *View)
{
	free(View->Graph);
}

/**
 * @brief Create new TextBox element in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @return - pointer to newly created GUI_TEXTBOX_TYPE element
 *
 * @note There is no list of TexBoxes since there will be problems with allocating
 * enough memory to TextBox string array
 */
GUI_TEXTBOX_TYPE* Gui_NewTextBox(GUI_VIEW_TYPE *View)
{
	GUI_TEXTBOX_TYPE *NewTextBox;
	GUI_TEXTBOX_TYPE TextBoxDefault = TEXTBOX_DEFAULT;
	NewTextBox = malloc(sizeof(GUI_TEXTBOX_TYPE));

	if(NewTextBox ==  NULL)
	{
		return NULL;
	}
	else
	{
		*NewTextBox = TextBoxDefault;
		View->TextBox = NewTextBox;
		View->TextBox->String = StringData;

		return (GUI_TEXTBOX_TYPE*)NewTextBox;
	}
}

/**
 * @brief Delete TextBox element in View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory of TextBox element will be deallocated and free to reuse again
 */
void Gui_DeleteTextBox(GUI_VIEW_TYPE *View)
{
	free(View->TextBox);
}

/**
 * @brief Draw View containing lists of define GUI components
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 */
void Gui_DrawView(GUI_VIEW_TYPE *View)
{
	GUI_LABEL_LIST_TYPE *LabelListBuffer = NULL;
	GUI_BUTTON_LIST_TYPE *ButtonListBuffer = NULL;
	GUI_PANEL_LIST_TYPE *PanelListBuffer = NULL;
	GUI_SLIDER_LIST_TYPE *SliderListBuffer = NULL;
	GUI_CHECKBOX_LIST_TYPE *CheckboxListBuffer = NULL;
	GUI_LED_LIST_TYPE *LedListBuffer = NULL;

	//Draw every panel in the list first to be sure that other elements might be drawn inside panel
	for(PanelListBuffer = View->PanelList; PanelListBuffer != NULL; PanelListBuffer = PanelListBuffer->Next)
	{
		Gui_DrawPanel( &(PanelListBuffer->PanelElement) );
	}

	//Draw every label in the list
	for(LabelListBuffer = View->LabelList; LabelListBuffer != NULL; LabelListBuffer = LabelListBuffer->Next)
	{
		Gui_DrawLabel( &(LabelListBuffer->LabelElement) );
	}

	//Draw every button in the list
	for(ButtonListBuffer = View->ButtonList; ButtonListBuffer != NULL; ButtonListBuffer = ButtonListBuffer->Next)
	{
		Gui_DrawButton( &(ButtonListBuffer->ButtonElement) );
	}

	//Draw every slider in the list
	for(SliderListBuffer = View->SliderList; SliderListBuffer != NULL; SliderListBuffer = SliderListBuffer->Next)
	{
		Gui_DrawSlider( &(SliderListBuffer->SliderElement) );
	}

	//Draw every checkbox in the list
	for(CheckboxListBuffer = View->CheckboxList; CheckboxListBuffer != NULL; CheckboxListBuffer = CheckboxListBuffer->Next)
	{
		Gui_DrawCheckbox( &(CheckboxListBuffer->CheckboxElement) );
	}

	//Draw every led in the list
	for(LedListBuffer = View->LedList; LedListBuffer != NULL; LedListBuffer = LedListBuffer->Next)
	{
		Gui_DrawLed( &(LedListBuffer->LedElement) );
	}

	if(View->Graph != NULL)
	{
		Gui_DrawGraph(View->Graph);
	}

	if(View->TextBox != NULL)
	{
		Gui_DrawTextBox(View->TextBox);
	}

	View->IsCreated = TRUE;
}

/**
 * @brief Delete memory used by whole View element
 *
 * @param View - pointer to GUI_VIEW_TYPE type element
 *
 * @result All memory used by list of GUI components will be deallocated and free to reuse again
 */
void Gui_DeleteView(GUI_VIEW_TYPE *View)
{
	View->IsCreated = FALSE;
	Gui_DeleteGraph(View);
	Gui_DeleteTextBox(View);
	Gui_DeleteLedList(View);
	Gui_DeleteCheckboxList(View);
	Gui_DeleteSliderList(View);
	Gui_DeleteButtonList(View);
	Gui_DeleteLabelList(View);
	Gui_DeletePanelList(View);
}

/**
 *	@brief Periodic Gui task
 *
 *	@details Periodic task that scans touch sensing data about GUI components and refreshes the Graph
 *
 *	@param View - pointer to GUI_VIEW_TYPE type element
 *
 *	@note This task should be executed no longer than every 25 [ms] to maintain proper responsiveness
 */
void Gui_Task(GUI_VIEW_TYPE *View)
{
	Gui_ScanButtons(View->ButtonList);
	Gui_ScanSlider(View->SliderList);
	Gui_ScanCheckbox(View->CheckboxList);
	Gui_ScanTextBox(View->TextBox);

	if(View->Graph != NULL)
	{
		Gui_RefreshGraph(View->Graph);
	}
}

/**
 * @brief Scan all Button in the list
 *
 * @param ButtonList - pointer to GUI_BUTTON_LIST_TYPE
 *
 * @result When a button will be touched (click or release or both),
 * state machine will execute dedicated event function
 */
void Gui_ScanButtons(GUI_BUTTON_LIST_TYPE *ButtonList)
{
	static TOUCH_EVENT_TYPE GuiButtonTouchEvent = EVENT_TOUCH_IDLE;
	GUI_BUTTON_LIST_TYPE *ButtonListBuffer = NULL;
	static unsigned char SlectedButtonId = 0;
	ButtonListBuffer = ButtonList;

	switch(GuiButtonTouchEvent)
	{
		case EVENT_TOUCH_IDLE:
			if(TouchDriver_IsTouchDetected() == TRUE)
			{
				//Valid touch event has been detected, go to click state
				for(; ButtonListBuffer != NULL; ButtonListBuffer = ButtonListBuffer->Next)
				{
					if( (TouchDriver_GetX() >= ButtonListBuffer->ButtonElement.XPos) &&
						(TouchDriver_GetX() < (ButtonListBuffer->ButtonElement.XPos + ButtonListBuffer->ButtonElement.Width) ) &&
						(TouchDriver_GetY() >= ButtonListBuffer->ButtonElement.YPos) &&
						(TouchDriver_GetY() < (ButtonListBuffer->ButtonElement.YPos + ButtonListBuffer->ButtonElement.Height) ) )
					{
						SlectedButtonId = ButtonListBuffer->ButtonElement.Id;
						Gui_DrawSelectedButton( &(ButtonListBuffer->ButtonElement) );
						// TODO add on click event
						// ......
						//
						GuiButtonTouchEvent = EVENT_TOUCH_CLICK;
						break;
					}
					else
					{
						SlectedButtonId = 0;
					}
				}
			}
			else
			{
				SlectedButtonId = 0;
			}
			break;

		case EVENT_TOUCH_CLICK:
			if(TouchDriver_IsTouchDetected() == FALSE)
			{
				//Release event has been detected
				GuiButtonTouchEvent = EVENT_TOUCH_RELEASE;
			}
			break;

		case EVENT_TOUCH_RELEASE:
			for(; (ButtonListBuffer != NULL) && (ButtonListBuffer->ButtonElement.Id != SlectedButtonId); ButtonListBuffer = ButtonListBuffer->Next)
			{
				//empty loop, wait for condition (SliderListBuffer->SliderElement.Id == SlectedSliderId)
			}

			SlectedButtonId = 0;
			Gui_DrawButton( &(ButtonListBuffer->ButtonElement) );

			if(ButtonListBuffer->ButtonElement.OnReleaseEvent != NULL)
			{
				ButtonListBuffer->ButtonElement.OnReleaseEvent();
			}

			GuiButtonTouchEvent = EVENT_TOUCH_IDLE;
			break;

		default:
			break;
	}
}

/**
 * @brief Scan all Slider in the list
 *
 * @param SliderList - pointer to GUI_SLIDER_LIST_TYPE
 *
 * @result When a slider will be touched (click or release or both),
 * state machine will execute dedicated event function
 */
void Gui_ScanSlider(GUI_SLIDER_LIST_TYPE *SliderList)
{
	static TOUCH_EVENT_TYPE GuiSliderTouchEvent = EVENT_TOUCH_IDLE;
	GUI_SLIDER_LIST_TYPE *SliderListBuffer = NULL;
	SliderListBuffer = SliderList;
	static unsigned char SlectedSliderId = 0;
	signed char new_value = 0, value_diff = 0;

	switch(GuiSliderTouchEvent)
	{
		case EVENT_TOUCH_IDLE:
			if(TouchDriver_IsTouchDetected() == TRUE)
			{
				//Valid touch event has been detected, go to click state
				for(; SliderListBuffer != NULL; SliderListBuffer = SliderListBuffer->Next)
				{
					if( (TouchDriver_GetX() >= SliderListBuffer->SliderElement.SliderButton.XStart) &&
						(TouchDriver_GetX() < (SliderListBuffer->SliderElement.SliderButton.XEnd) ) &&
						(TouchDriver_GetY() >= SliderListBuffer->SliderElement.SliderButton.YStart) &&
						(TouchDriver_GetY() < (SliderListBuffer->SliderElement.SliderButton.YEnd) ) )
					{
						SlectedSliderId = SliderListBuffer->SliderElement.Id;

						//Draw selected slider button and call click event

						//Slider button has been touched, go to state where slider value is being calculated
						GuiSliderTouchEvent = EVENT_TOUCH_CLICK;
						break;
					}
					else
					{
						SlectedSliderId = 0;
					}
				}
			}
			else
			{
				SlectedSliderId = 0;
			}
			break;

		case EVENT_TOUCH_CLICK:
			if(TouchDriver_IsTouchDetected() == TRUE)
			{
				//Valid touch event has been detected, go to click state
				for(; (SliderListBuffer != NULL) && (SliderListBuffer->SliderElement.Id != SlectedSliderId); SliderListBuffer = SliderListBuffer->Next)
				{
					//empty loop, wait for condition (SliderListBuffer->SliderElement.Id == SlectedSliderId)
				}

				if( (TouchDriver_GetX() >= SliderListBuffer->SliderElement.XPos) &&
					(TouchDriver_GetX() < (SliderListBuffer->SliderElement.XPos + SliderListBuffer->SliderElement.Width) ) &&
					(TouchDriver_GetY() >= SliderListBuffer->SliderElement.YPos) &&
					(TouchDriver_GetY() < (SliderListBuffer->SliderElement.YPos + SliderListBuffer->SliderElement.Height) ) )
				{
					//Calculate slider value based on touch screen touch coordinates
					if(SliderListBuffer->SliderElement.Orientation == HORIZONTAL)
					{
						new_value = (100 * (TouchDriver_GetX() - SliderListBuffer->SliderElement.XPos) + 1) / (SliderListBuffer->SliderElement.Width - 1);
					}
					else
					{
						new_value = (100 * (TouchDriver_GetY() - SliderListBuffer->SliderElement.YPos) + 1) / (SliderListBuffer->SliderElement.Height - 1);
					}

					value_diff = new_value - SliderListBuffer->SliderElement.Value;

					// check if new slider position differs from previous no more than 30 %
					if( ( ABS(value_diff) >= 1 ) && ( ABS(value_diff) < 30) )
					{
						SliderListBuffer->SliderElement.Value = new_value;
						Gui_DrawSlider( &(SliderListBuffer->SliderElement) );

						if(SliderListBuffer->SliderElement.OnSliderChangeEvent != NULL)
						{
							SliderListBuffer->SliderElement.OnSliderChangeEvent();
						}
					}
				}
			}
			else
			{
				//Release event has been detected
				GuiSliderTouchEvent = EVENT_TOUCH_RELEASE;
			}
			break;

		case EVENT_TOUCH_RELEASE:
			for(; (SliderListBuffer != NULL) && (SliderListBuffer->SliderElement.Id != SlectedSliderId); SliderListBuffer = SliderListBuffer->Next)
			{
				//empty loop, wait for condition (SliderListBuffer->SliderElement.Id != SlectedSliderId)
			}
			SlectedSliderId = 0;
			//Draw slider and call on_release event
			GuiSliderTouchEvent = EVENT_TOUCH_IDLE;
			break;

		default:
			break;
	}
}

/**
 * @brief Scan all Checkbox in the list
 *
 * @param CheckboxList - pointer to GUI_CHECKBOX_LIST_TYPE
 *
 * @result When a checkbox will be touched (click or release or both),
 * state machine will execute dedicated event function
 */
void Gui_ScanCheckbox(GUI_CHECKBOX_LIST_TYPE *CheckboxList)
{
	static TOUCH_EVENT_TYPE GuiCheckboxTouchEvent = EVENT_TOUCH_IDLE;
	GUI_CHECKBOX_LIST_TYPE *CheckboxListBuffer = NULL;
	static unsigned char SlectedCheckboxId = 0;
	CheckboxListBuffer = CheckboxList;

	switch(GuiCheckboxTouchEvent)
	{
		case EVENT_TOUCH_IDLE:
			if(TouchDriver_IsTouchDetected() == TRUE)
			{
				//Valid touch event has been detected, go to click state
				for(; CheckboxListBuffer != NULL; CheckboxListBuffer = CheckboxListBuffer->Next)
				{
					if( (TouchDriver_GetX() >= CheckboxListBuffer->CheckboxElement.XPos) &&
						(TouchDriver_GetX() < (CheckboxListBuffer->CheckboxElement.XPos + CheckboxListBuffer->CheckboxElement.Size) ) &&
						(TouchDriver_GetY() >= CheckboxListBuffer->CheckboxElement.YPos) &&
						(TouchDriver_GetY() < (CheckboxListBuffer->CheckboxElement.YPos + CheckboxListBuffer->CheckboxElement.Size) ) )
					{
						SlectedCheckboxId = CheckboxListBuffer->CheckboxElement.Id;
						// TODO add on click event
						// ......
						//
						GuiCheckboxTouchEvent = EVENT_TOUCH_CLICK;
						break;
					}
					else
					{
						SlectedCheckboxId = 0;
					}
				}
			}
			else
			{
				SlectedCheckboxId = 0;
			}
			break;

		case EVENT_TOUCH_CLICK:
			if(TouchDriver_IsTouchDetected() == FALSE)
			{
				//Release event has been detected
				GuiCheckboxTouchEvent = EVENT_TOUCH_RELEASE;
			}
			break;

		case EVENT_TOUCH_RELEASE:
			for(; (CheckboxListBuffer != NULL) && (CheckboxListBuffer->CheckboxElement.Id != SlectedCheckboxId); CheckboxListBuffer = CheckboxListBuffer->Next)
			{
				//empty loop, wait for condition (SliderListBuffer->SliderElement.Id == SlectedSliderId)
			}

			SlectedCheckboxId = 0;

			if(CheckboxListBuffer->CheckboxElement.IsChecked == TRUE)
			{
				CheckboxListBuffer->CheckboxElement.IsChecked = FALSE;
			}
			else
			{
				CheckboxListBuffer->CheckboxElement.IsChecked = TRUE;
			}
			Gui_DrawCheckbox( &(CheckboxListBuffer->CheckboxElement) );

			if(CheckboxListBuffer->CheckboxElement.OnCheckboxChangeEvent != NULL)
			{
				CheckboxListBuffer->CheckboxElement.OnCheckboxChangeEvent();
			}

			GuiCheckboxTouchEvent = EVENT_TOUCH_IDLE;
			break;

		default:
			break;
	}
}

/**
 * @brief Scan all TextBox in the list
 *
 * @param TextBox - pointer to GUI_TEXTBOX_TYPE element
 *
 * @result When a texbox will be touched (only release event),
 * text will be scrolled down or up depending if the touch will be detected
 * on upper or lower half of TextBox element
 */
void Gui_ScanTextBox(GUI_TEXTBOX_TYPE *TextBox)
{
	static TOUCH_EVENT_TYPE GuiTextBoxTouchEvent = EVENT_TOUCH_IDLE;

	switch(GuiTextBoxTouchEvent)
	{
		case EVENT_TOUCH_IDLE:
			if(TouchDriver_IsTouchDetected() == TRUE)
			{
				if( (TouchDriver_GetX() >= TextBox->XPos) &&
					(TouchDriver_GetX() < (TextBox->XPos + TextBox->Width) ) &&
					(TouchDriver_GetY() >= TextBox->YPos) &&
					(TouchDriver_GetY() < (TextBox->YPos + TextBox->Height) ) )
				{
					GuiTextBoxTouchEvent = EVENT_TOUCH_CLICK;
					break;
				}
			}
			break;

		case EVENT_TOUCH_CLICK:
			if(TouchDriver_IsTouchDetected() == FALSE)
			{
				//Release event has been detected
				if( TouchDriver_GetY() > (TextBox->YPos + (55*TextBox->Height)/100 ) )
				{
					//Scroll up TextBox
					if(TextBox->ScrollIndex-- <= 0)
					{
						TextBox->ScrollIndex = 0;
					}
					Gui_DrawTextBox(TextBox);
				}
				else if( TouchDriver_GetY() < ( TextBox->YPos + (45*TextBox->Height)/100 ) )
				{
					//Scroll down TextBox
					if(TextBox->ScrollIndex++ > GUI_TEXTBOX_MAX_SIZE)
					{
						TextBox->ScrollIndex = GUI_TEXTBOX_MAX_SIZE;
					}
					Gui_DrawTextBox(TextBox);
				}
				GuiTextBoxTouchEvent = EVENT_TOUCH_RELEASE;
			}
			break;

		case EVENT_TOUCH_RELEASE:

			GuiTextBoxTouchEvent = EVENT_TOUCH_IDLE;
			break;

		default:
			break;
	}
}

/**
 * @brief Get length of string
 *
 * @param string - pointer to char type
 *
 * @note Equivalent to strlen() C library function
 */
unsigned short Gui_GetStringLength(char *string)
{
	unsigned short i = 0;

	while( string[i] != '\0' )
	{
		i++;
	}

	return i;
}

/**
 * @brief Convert Integer value to string data
 *
 * @param string - pointer to char type of string that will contain converted integer
 *
 * @param num - int type value to be converted
 *
 * @return - pointer to char type string containing converted integer number
 *
 * @note This function also copies resulting memory buffer to defined string in parameter
 */
char *Gui_IntToString(char *string, int num)
{
	string = DigitCaption;
	Gui_itoa(num, DigitCaption);
	strcpy(string, DigitCaption);

	return string;
}

/**
 * @brief Convert Integer value to string data
 *
 * @param string - pointer to char type of string that will contain converted integer
 *
 * @param num - int type value to be converted
 *
 * @return - pointer to char type string containing converted integer number
 */
char *Gui_itoa(int num, char *string)
{
	char *buff1 = string;
	char *buff2 = string;
	char c = 0;

	if(num >= 0)
	{
		do
		{
			*buff1++ = '0' + (num % 10);
		}
		while(num /= 10);
	}
	else
	{
		*buff1++ = '-';
		buff2++;

		do
		{
			int d = num % 10;
			num = num / 10;
			if (d != 0)
			{
				num++;
				d = 10 - d;
			}
			*buff1++ = '0' + d;
		}
		while (num != 0);
	}

	*buff1 = '\0';

	while(buff2 < buff1)
	{
		buff1--;

		c = *buff2;
		*buff2 = *buff1;
		*buff1 = c;

		buff2++;
	}

	return string;
}

/**
 * @brief Convert 24-bit RGB value to 16-bit R5 G6 B5 bit color value
 *
 * @param red,green,blue - unsigned char color data
 *
 * @result Converted R5 G6 B5 format unsigned int value
 */
unsigned int Gui_RGB888To565(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int retval;
	red >>= 3;
	green >>= 2;
	blue >>= 3;

	retval = (red << 11) | (green << 5) | blue;

	return retval;
}

#endif /* GUI_C_ */
