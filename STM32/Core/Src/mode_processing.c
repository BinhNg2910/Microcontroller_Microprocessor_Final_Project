#include <software_timer.h>
#include "main.h"
#include "normal_mode.h"
#include "mode_processing.h"
#include "input_reading.h"
#include "input_processing.h"
#include <stdio.h>
#include <string.h>
UART_HandleTypeDef huart2;
int checkflag = 0;
int buzzer = 0;
int pedesFlag = 0;
int toggleLED = 0;
int tempFlag = 0;
void checkFlagPedes(){
	if(mode == Normal_mode ) checkflag = 1;
	else checkflag = 0;

	if((light_state == Red_Green || light_state == Red_Yellow) && horizontal_countdown <= 5) {
			tempFlag = 1;
	}
	else if (light_state == Yellow_Red){
		tempFlag = 2;
	}
	else {
		tempFlag = 0;
	}
}

void initBuzzerPedes(){
	buzzer = 0;
}

void buzzerPedes(){
	if(pedesFlag == 1){
		if(buzzer < 100){
			buzzer += 25;
		}
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, buzzer);
	}
	else if(pedesFlag == 0){
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	}
	pedesFlag = 1 - pedesFlag;
}
void clearTerminal(){
	char clr[] = "\033[2J";
	HAL_UART_Transmit(&huart2, (uint8_t *)clr, sizeof(clr) - 1, HAL_MAX_DELAY);
}
void printString(const char *str){
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}
void printValue(int val){
	char str[100];
	HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "%d\r\n", val), HAL_MAX_DELAY);
}
void displayTLValues(){
	clearTerminal();
	switch(light_state){
	case Red_Green:
		printString("RED: ");
		printValue(horizontal_countdown);
		printString("GREEN: ");
		printValue(vertical_countdown);
		break;
	case Red_Yellow:
		printString("RED: ");
		printValue(horizontal_countdown);
		printString("AMBER: ");
		printValue(vertical_countdown);
		break;
	case Green_Red:
		printString("GREEN: ");
		printValue(horizontal_countdown);
		printString("RED: ");
		printValue(vertical_countdown);
		break;
	case Yellow_Red:
		printString("AMBER: ");
		printValue(horizontal_countdown);
		printString("RED: ");
		printValue(vertical_countdown);
		break;
	default:
		break;
	}
}

void modify_red(){
	if(timer0_flag == 1){
		if(toggleLED == 1){
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, SET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, RESET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, SET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, RESET);
		}else{
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, RESET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, RESET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, RESET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, RESET);
		}
		toggleLED = 1 - toggleLED;
		setTimer0(500);
	}
}

void modify_yellow(){
	if(timer0_flag == 1){
		if(toggleLED == 1){
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, SET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, SET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, SET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, SET);
		}else{
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, RESET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, RESET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, RESET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, RESET);
		}
		toggleLED = 1 - toggleLED;
		setTimer0(500);
	}
}

void modify_green(){
	if(timer0_flag == 1){
		if(toggleLED == 1){
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, RESET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, SET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, RESET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, SET);
		}else{
			HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, RESET);
			HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, RESET);
			HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, RESET);
			HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, RESET);
		}
		toggleLED = 1 - toggleLED;
		setTimer0(500);
	}
}

void initLightPedes(){
	HAL_GPIO_WritePin(PDL_0_GPIO_Port, PDL_0_Pin, RESET); //0
	HAL_GPIO_WritePin(PDL_1_GPIO_Port, PDL_1_Pin, RESET); //0
}

void setRedPedes(){
	HAL_GPIO_WritePin(PDL_0_GPIO_Port, PDL_0_Pin, SET); //1
	HAL_GPIO_WritePin(PDL_1_GPIO_Port, PDL_1_Pin, RESET); //0
}

void setGreenPedes(){
	HAL_GPIO_WritePin(PDL_0_GPIO_Port, PDL_0_Pin, RESET); //0
	HAL_GPIO_WritePin(PDL_1_GPIO_Port, PDL_1_Pin, SET); //1
}

int reduce_time = 0;
void pes_processing(){
	switch(light_state){
		case Red_Green:
			if(tempFlag == 2) checkFlagPedes();
			if(timer1_flag == 1){
				if(tempFlag == 1) {
					 setRedPedes();
				}
				else if(tempFlag == 0) {
					if(horizontal_countdown <= 5) buzzerPedes();
					setTimer1(1000 - reduce_time * 50);
					if(1000 - (reduce_time + 1)* 50 > 50) reduce_time++;
					setGreenPedes();
				}
			}
			break;
		case Red_Yellow:
			if(tempFlag == 2) checkFlagPedes();
			if(timer1_flag == 1){
				if(tempFlag == 1) {
					setRedPedes();
				}
				else if(tempFlag == 0) {
					if(horizontal_countdown <= 5) buzzerPedes();
					setTimer1(1000 - reduce_time * 50);
					if(1000 - (reduce_time + 1)* 50 > 50) reduce_time++;
					setGreenPedes();
				}
			}
			break;
		case Green_Red:
			setRedPedes();
			initBuzzerPedes();
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
			break;
		case Yellow_Red:
			if(tempFlag == 2) {
				setRedPedes();
			}
			else {
				initLightPedes();
				checkflag = 0;
			}
			reduce_time = 0;
			break;
		default:
			break;
	}
}

void mode_processing(){
	fsm_for_input_processing();
	if(is_press_flag[0]){
		HAL_GPIO_WritePin(TFL_00_GPIO_Port, TFL_00_Pin, RESET);
		HAL_GPIO_WritePin(TFL_01_GPIO_Port, TFL_01_Pin, RESET);
		HAL_GPIO_WritePin(TFL_10_GPIO_Port, TFL_10_Pin, RESET);
		HAL_GPIO_WritePin(TFL_11_GPIO_Port, TFL_11_Pin, RESET);
		led_time_buffer[RED] =  led_time[RED];
		led_time_buffer[YELLOW] = led_time[YELLOW];
		led_time_buffer[GREEN] = led_time[GREEN];
		if(++mode > 3){
			mode = 0;
		}
		clearTerminal();
		printString("MODE ");
		printValue(mode);
		checkflag = 0;
		is_press_flag[0] = 0;
		initBuzzerPedes();
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
		reduce_time = 0;
	}else if(is_press_flag[1]){
		switch(mode){
			case Modify_red:
				printString("INCREASE RED TIMER : ");
				led_time_buffer[RED]++;
				printValue(led_time_buffer[RED]);
				break;
			case Modify_yellow:
				printString("INCREASE AMBER TIMER : ");
				led_time_buffer[YELLOW]++;
				printValue(led_time_buffer[YELLOW]);
				break;
			case Modify_green:
				printString("INCREASE GREEN TIMER : ");
				led_time_buffer[GREEN]++;
				printValue(led_time_buffer[GREEN]);
				break;
			default:
				break;
		}
		is_press_flag[1] = 0;
	}else if(is_press_flag[2]){
		switch(mode){
			case Modify_red:
				led_time[RED] = led_time_buffer[RED];
                if(led_time[RED] >= (led_time[GREEN] + led_time[YELLOW])){
                    led_time[GREEN] = led_time[RED] - led_time[YELLOW];
                }
                else{
                    int half = led_time[RED] / 2;
                    int mod = led_time[RED] % 2;
                    led_time[YELLOW] = half;
                    led_time[GREEN] = half + mod;
                }
                clearTerminal();
				printString("SET RED TIMER : ");
				printValue(led_time_buffer[RED]);
				break;
			case Modify_yellow:
				led_time[YELLOW] = led_time_buffer[YELLOW];
                if(led_time[RED] >= (led_time[YELLOW] + led_time[GREEN])){
                    led_time[GREEN] = led_time[RED] - led_time[YELLOW];
                }
                else{
                    if((led_time[GREEN] + led_time[YELLOW]) <= 99){
                        led_time[RED] = led_time[GREEN] + led_time[YELLOW];
                    }
                    else{
                        led_time[RED] = 99;
                        led_time[GREEN] = led_time[RED] - led_time[YELLOW];
                    }
                }
                clearTerminal();
				printString("SET YELLOW TIMER : ");
				printValue(led_time_buffer[YELLOW]);
				break;
			case Modify_green:
				led_time[GREEN] = led_time_buffer[GREEN];
                if(led_time[RED] >= (led_time[GREEN] + led_time[YELLOW])){
                    led_time[YELLOW] = led_time[RED] - led_time[GREEN];
                }
                else{
                    if((led_time[YELLOW] + led_time[GREEN]) <= 99){
                        led_time[RED] = led_time[YELLOW] + led_time[GREEN];
                    }
                    else{
                        led_time[RED] = 99;
                        led_time[YELLOW] = led_time[RED] - led_time[GREEN];
                    }
                }
                clearTerminal();
				printString("SET GREEN TIMER : ");
				printValue(led_time_buffer[GREEN]);
				break;
			default:
				break;
		}
		is_press_flag[2] = 0;
	}else if(is_press_flag[3]){
		checkFlagPedes();
		setTimer1(1000);
		printString("BUTTON_3 PRESS : ");
		is_press_flag[3] = 0;
	}
	switch(mode){
		case Normal_mode:
			if(timer0_flag == 1){
				traffic_light();
				displayTLValues();
				setTimer0(1000);
			}
			if(checkflag == 1){
				pes_processing();
			}else {
				HAL_GPIO_WritePin(PDL_0_GPIO_Port, PDL_0_Pin, RESET); //1
				HAL_GPIO_WritePin(PDL_1_GPIO_Port, PDL_1_Pin, RESET); //0
			}
			break;
		case Modify_red:
			modify_red();
			HAL_GPIO_WritePin(PDL_0_GPIO_Port, PDL_0_Pin, RESET); //1
			HAL_GPIO_WritePin(PDL_1_GPIO_Port, PDL_1_Pin, RESET); //0
			break;
		case Modify_yellow:
			modify_yellow();
			break;
		case Modify_green:
			modify_green();
			break;
		default:
			break;
	}
}
