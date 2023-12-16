/*
 * mode_processing.h
 *
 *  Created on: 2 Dec, 2023
 *      Author: asus
 */

#ifndef INC_MODE_PROCESSING_H_
#define INC_MODE_PROCESSING_H_

enum NO_OF_MODES {Normal_mode, Modify_red, Modify_yellow, Modify_green};
extern enum NO_OF_MODES mode;

void mode_processing(void);

void modify_red(void);
void modify_yellow(void);
void modify_green(void);

void printString(const char*);


#endif /* INC_MODE_PROCESSING_H_ */
