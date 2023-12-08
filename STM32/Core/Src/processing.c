/*
 * processing.c
 *
 *  Created on: Dec 1, 2023
 *      Author: vanbi
 */


#include <software_timer.h>
#include "main.h"
#include "reading.h"
#include "processing.h"

enum ButtonState_0 { BUTTON_RELEASED_0, BUTTON_PRESSED_0, BUTTON_PRESSED_MORE_THAN_1_SECOND_0 };
enum ButtonState_0 buttonState_0 = BUTTON_RELEASED_0;
enum ButtonState_1 { BUTTON_RELEASED_1, BUTTON_PRESSED_1, BUTTON_PRESSED_MORE_THAN_1_SECOND_1 };
enum ButtonState_1 buttonState_1 = BUTTON_RELEASED_1;
enum ButtonState_2 { BUTTON_RELEASED_2, BUTTON_PRESSED_2, BUTTON_PRESSED_MORE_THAN_1_SECOND_2 };
enum ButtonState_2 buttonState_2 = BUTTON_RELEASED_2;
enum ButtonState_3 { BUTTON_RELEASED_3, BUTTON_PRESSED_3, BUTTON_PRESSED_MORE_THAN_1_SECOND_3 };
enum ButtonState_3 buttonState_3 = BUTTON_RELEASED_3;

enum LightState light_state = Red_Green;
enum NO_OF_MODES mode = Normal_mode;

int is_press_flag[N0_OF_BUTTONS] = {0, 0, 0, 0};

void fsm_for_input_processing(void) {
	switch(buttonState_0){
		case BUTTON_RELEASED_0:
			if(is_button_pressed(0)){
				buttonState_0 = BUTTON_PRESSED_0;
				is_press_flag[0] = 1;
			}
				// INCREASE VALUE OF PORT A BY ONE UNIT
			break;
		case BUTTON_PRESSED_0:
			if (!is_button_pressed(0)){
				buttonState_0 = BUTTON_RELEASED_0;
				is_press_flag[0] = 0;
			}else{
				if(is_button_pressed_1s(0)){
					buttonState_0 = BUTTON_PRESSED_MORE_THAN_1_SECOND_0;
					is_press_flag[0] = 1;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND_0:
			if (!is_button_pressed(0)){
				buttonState_0 = BUTTON_RELEASED_0;
				is_press_flag[0] = 0;
			}
			// TODO
			break;
	}
	switch(buttonState_1){
		case BUTTON_RELEASED_1:
			if(is_button_pressed(1)){
				buttonState_1 = BUTTON_PRESSED_1;
				is_press_flag[1] = 1;
			}
				// INCREASE VALUE OF PORT A BY ONE UNIT
			break;
		case BUTTON_PRESSED_1:
			if (!is_button_pressed(1)){
				buttonState_1 = BUTTON_RELEASED_1;
				is_press_flag[1] = 0;
			}else{
				if(is_button_pressed_1s(1)){
					buttonState_1 = BUTTON_PRESSED_MORE_THAN_1_SECOND_1;
					is_press_flag[1] = 1;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND_1:
			if (!is_button_pressed(1)){
				buttonState_1 = BUTTON_RELEASED_1;
				is_press_flag[1] = 0;
			}
			// TODO
			break;
	}
	switch(buttonState_2){
		case BUTTON_RELEASED_2:
			if(is_button_pressed(2)){
				buttonState_2 = BUTTON_PRESSED_2;
				is_press_flag[2] = 1;
			}
				// INCREASE VALUE OF PORT A BY ONE UNIT
			break;
		case BUTTON_PRESSED_2:
			if (!is_button_pressed(2)){
				buttonState_2 = BUTTON_RELEASED_2;
				is_press_flag[2] = 0;
			}else{
				if(is_button_pressed_1s(2)){
					buttonState_2 = BUTTON_PRESSED_MORE_THAN_1_SECOND_2;
					is_press_flag[2] = 1;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND_2:
			if (!is_button_pressed(2)){
				buttonState_2 = BUTTON_RELEASED_2;
				is_press_flag[2] = 0;
			}
			// TODO
			break;
	}
	switch(buttonState_3){
		case BUTTON_RELEASED_2:
			if(is_button_pressed(3)){
				buttonState_3 = BUTTON_PRESSED_3;
				is_press_flag[3] = 1;
			}
				// INCREASE VALUE OF PORT A BY ONE UNIT
			break;
		case BUTTON_PRESSED_3:
			if (!is_button_pressed(3)){
				buttonState_3 = BUTTON_RELEASED_3;
				is_press_flag[3] = 0;
			}else{
				if(is_button_pressed_1s(3)){
					buttonState_3 = BUTTON_PRESSED_MORE_THAN_1_SECOND_3;
					is_press_flag[3] = 1;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND_3:
			if (!is_button_pressed(3)){
				buttonState_3 = BUTTON_RELEASED_3;
				is_press_flag[3] = 0;
			}
			// TODO
			break;
	}
}
