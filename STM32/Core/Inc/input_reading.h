/*
 * reading.h
 *
 *  Created on: Dec 1, 2023
 *      Author: vanbi
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

// we aim to work with more than one buttons
#define N0_OF_BUTTONS 	4

void button_reading (void) ;
unsigned char is_button_pressed (unsigned char index);
unsigned char is_button_pressed_1s (unsigned char index);

#endif /* INC_INPUT_READING_H_ */
