/*
 * L293D.c
 *
 *  Created on: Apr 1, 2023
 *      Author: PC
 */
#include "L293D_driver.h"

void EnorDi_pwm_signal(struct L293D_motor_t *pmotor, uint8_t EnorDi){

	if(EnorDi == ENABLE){
		HAL_TIM_PWM_Start(pmotor->htimer, pmotor->timer_channel);
	}else if(EnorDi == DISABLE){
		HAL_TIM_PWM_Stop(pmotor->htimer, pmotor->timer_channel);
	}else{
		//wrong parameter passed
	}

}

void increase_motor_speed(struct L293D_motor_t *pmotor){

	uint32_t current_timer_pulse;
	uint32_t demanded_timer_pulse;
	uint32_t current_timer_period;

	current_timer_pulse = pmotor->htimer->Instance->ARR;

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		current_timer_period = pmotor->htimer->Instance->CCR1;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		current_timer_period = pmotor->htimer->Instance->CCR2;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		current_timer_period = pmotor->htimer->Instance->CCR3;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		current_timer_period = pmotor->htimer->Instance->CCR4;
	}

	demanded_timer_pulse = (current_timer_pulse + (current_timer_period * 0,1));

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		pmotor->htimer->Instance->CCR1 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		pmotor->htimer->Instance->CCR2 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		pmotor->htimer->Instance->CCR3 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		pmotor->htimer->Instance->CCR4 = demanded_timer_pulse;
	}

}


void decrease_motor_speed(struct L293D_motor_t *pmotor){

	uint32_t current_timer_pulse;
	uint32_t demanded_timer_pulse;
	uint32_t current_timer_period;

	current_timer_pulse = pmotor->htimer->Instance->ARR;

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		current_timer_period = pmotor->htimer->Instance->CCR1;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		current_timer_period = pmotor->htimer->Instance->CCR2;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		current_timer_period = pmotor->htimer->Instance->CCR3;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		current_timer_period = pmotor->htimer->Instance->CCR4;
	}

	demanded_timer_pulse = (current_timer_pulse - (current_timer_period * 0,1));

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		pmotor->htimer->Instance->CCR1 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		pmotor->htimer->Instance->CCR2 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		pmotor->htimer->Instance->CCR3 = demanded_timer_pulse;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		pmotor->htimer->Instance->CCR4 = demanded_timer_pulse;
	}

}


void StopOrStart_motor(struct L293D_motor_t *pmotor, uint8_t StoporStart){

	if(StoporStart == MOTOR_START){

		if(pmotor->direction_of_rotation_flag == MOTOR_ROTATION_CLOCKWISE){
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_SET);

		}else if(pmotor->direction_of_rotation_flag == MOTOR_ROTATION_COUNTERCLOCKWISE){
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_SET);
		}

	}else if(StoporStart == MOTOR_STOP){
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_RESET);

	}

}


void select_motor_rotation_direction(struct L293D_motor_t *pmotor, uint8_t direction){

	if(direction = MOTOR_ROTATION_CLOCKWISE){
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_SET);

	}else if(direction = MOTOR_ROTATION_COUNTERCLOCKWISE){
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_SET);

	}

}
