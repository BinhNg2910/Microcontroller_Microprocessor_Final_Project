/*
 * scheduler.h
 *
 *  Created on: Dec 2, 2023
 *      Author: vanbi
 */

#ifndef INC_NORMAL_MODE_H_
#define INC_NORMAL_MODE_H_

#include "input_processing.h"

#define RED 	0
#define YELLOW	1
#define GREEN	2

#define HORI 	0
#define VERTI 	1

extern int led_time[3];
extern int led_time_buffer[3];
extern int horizontal_countdown;
extern int vertical_countdown;
extern int mode_and_time;

enum LightState {Red_Green, Red_Yellow, Green_Red, Yellow_Red, Init};
extern enum LightState light_state;

void seven_segment_state(void);
void traffic_light(void);

#endif /* INC_NORMAL_MODE_H_ */