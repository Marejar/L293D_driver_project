/*
 * L293D_driver.h
 *
 *  Created on: Apr 1, 2023
 *      Author: PC
 */

#ifndef INC_L293D_DRIVER_H_
#define INC_L293D_DRIVER_H_

#include <stdint.h>
#include "main.h"

#define ENABLE 1
#define DISABLE 0

#define MOTOR_ROTATION_CLOCKWISE 1
#define MOTOR_ROTATION_COUNTERCLOCKWISE 0

#define MOTOR_START 1
#define MOTOR_STOP 0



struct L293D_motor_t{

	TIM_HandleTypeDef *htimer;
	uint32_t timer_channel;
	uint8_t clockwise_rotation_enable_pin;
	uint8_t counterclockwise_rotation_enable_pin;
	uint8_t direction_of_rotation_flag;

};


void L293D_motor_init(struct L293D_motor_t *pmotor, TIM_HandleTypeDef *htim, uint32_t tim_channel, uint8_t clockwise_rotation_enable_pin, uint8_t counterclockwise_rotation_enable_pin);
void EnorDi_pwm_signal(struct L293D_motor_t *pmotor, uint8_t EnorDi);
void increase_motor_speed(struct L293D_motor_t *pmotor);
void decrease_motor_speed(struct L293D_motor_t *pmotor);
void StoporStart_motor_f(struct L293D_motor_t *pmotor, uint8_t StoporStart);
void select_motor_rotation_direction_f(struct L293D_motor_t *pmotor, uint8_t direction);

#endif /* INC_L293D_DRIVER_H_ */
