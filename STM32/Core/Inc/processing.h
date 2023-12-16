/*
 * processing.h
 *
 *  Created on: Dec 1, 2023
 *      Author: vanbi
 */

#ifndef INC_PROCESSING_H_
#define INC_PROCESSING_H_

#include "reading.h"

extern int is_press_flag[N0_OF_BUTTONS];

void fsm_for_input_processing(void);

#endif /* INC_PROCESSING_H_ */
