/*
 * L293D.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Marek Jaromin
 */
#include "L293D_driver.h"

/**
  * @brief  Initializing function for single motor connected to L293D.
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @param  Pointer to the TIM_HandleTypeDef which contains timer set for PWM to control speed
  * @param  Number of pin in port. This pin is responsible for changing motor rotation direction
  * @param  Number of pin in port. This pin is responsible for changing motor rotation direction
  * @param  Pointer to the GPIO_TypeDef structure of clockwise_rotation_enable_pin port
  * @param  Pointer to the GPIO_TypeDef structure of counterclockwise_rotation_enable_pin port
  * @retval None
  */
void L293D_motor_init(struct L293D_motor_t *pmotor, TIM_HandleTypeDef *htim,
		uint32_t tim_channel, uint8_t clockwise_rotation_enable_pin,
		uint8_t counterclockwise_rotation_enable_pin,
		GPIO_TypeDef *clockwise_rotation_enable_port,
		GPIO_TypeDef *counterclockwise_rotation_enable_port){

	pmotor->htimer = htim;
	pmotor->timer_channel = tim_channel;
	pmotor->clockwise_rotation_enable_pin = clockwise_rotation_enable_pin;
	pmotor->counterclockwise_rotation_enable_pin = counterclockwise_rotation_enable_pin;
	pmotor->clockwise_rotation_enable_port = clockwise_rotation_enable_port;
	pmotor->counterclockwise_rotation_enable_port = counterclockwise_rotation_enable_port;
	pmotor->direction_of_rotation_flag = MOTOR_ROTATION_CLOCKWISE;

}

/**
  * @brief  Enabling or disabling PWM signal on EN pin of L293D
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @param  ENABLE or DISABLE macro should be passed
  * @retval None
  */
void EnorDi_pwm_signal(struct L293D_motor_t *pmotor, uint8_t EnorDi){

	if(EnorDi == ENABLE){
		HAL_TIM_PWM_Start(pmotor->htimer, pmotor->timer_channel);
	}else if(EnorDi == DISABLE){
		HAL_TIM_PWM_Stop(pmotor->htimer, pmotor->timer_channel);
	}else{
		//wrong parameter passed
	}

}

/**
  * @brief  Increasing motor speed. Amount of increased speed can be set
  * through SPEED_CHANGE_STEP macro's value
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @retval None
  */
void increase_motor_speed(struct L293D_motor_t *pmotor){

	uint32_t current_timer_pulse;
	uint32_t demanded_timer_pulse;
	uint32_t current_timer_period;

	current_timer_period = pmotor->htimer->Instance->ARR;

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		current_timer_pulse = pmotor->htimer->Instance->CCR1;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		current_timer_pulse = pmotor->htimer->Instance->CCR2;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		current_timer_pulse = pmotor->htimer->Instance->CCR3;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		current_timer_pulse = pmotor->htimer->Instance->CCR4;
	}

	if((current_timer_pulse + (current_timer_period / SPEED_CHANGE_STEP)) <= current_timer_period){
		demanded_timer_pulse = (uint32_t)(current_timer_pulse + (current_timer_period / SPEED_CHANGE_STEP));
	}else{
		demanded_timer_pulse = current_timer_period;
	}

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

/**
  * @brief  Decreasing motor speed. Amount of decreased speed can be set
  * through SPEED_CHANGE_STEP macro's value
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @retval None
  */
void decrease_motor_speed(struct L293D_motor_t *pmotor){

	uint32_t current_timer_pulse;
	uint32_t demanded_timer_pulse;
	uint32_t current_timer_period;

	current_timer_period = pmotor->htimer->Instance->ARR;

	if(pmotor->timer_channel == TIM_CHANNEL_1){
		current_timer_pulse = pmotor->htimer->Instance->CCR1;
	}else if(pmotor->timer_channel == TIM_CHANNEL_2){
		current_timer_pulse = pmotor->htimer->Instance->CCR2;
	}else if(pmotor->timer_channel == TIM_CHANNEL_3){
		current_timer_pulse = pmotor->htimer->Instance->CCR3;
	}else if(pmotor->timer_channel == TIM_CHANNEL_4){
		current_timer_pulse = pmotor->htimer->Instance->CCR4;
	}

	if((current_timer_pulse - (current_timer_period / SPEED_CHANGE_STEP)) >= 0){
		demanded_timer_pulse = (uint32_t)(current_timer_pulse - (current_timer_period / SPEED_CHANGE_STEP));
	}else{
		demanded_timer_pulse = 0;
	}

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

/**
  * @brief  Starting and stopping motor.
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @param  MOTOR_START or MOTOR_STOP should be passed
  * @retval None
  */
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

/**
  * @brief  Selecting rotation direction for particular motor
  * @param  Pointer to the L293D_motor_t structure which needs to be
  * created in main before using this function
  * @param  Setting desired direction. MOTOR_ROTATION_CLOCKWISE or MOTOR_ROTATION_COUNTERCLOCKWISE
  * should be passed
  * @retval None
  */
void select_motor_rotation_direction(struct L293D_motor_t *pmotor, uint8_t direction){

	if(direction == MOTOR_ROTATION_CLOCKWISE){
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_SET);
			pmotor->direction_of_rotation_flag = MOTOR_ROTATION_CLOCKWISE;

	}else if(direction == MOTOR_ROTATION_COUNTERCLOCKWISE){
			HAL_GPIO_WritePin(pmotor->clockwise_rotation_enable_port,
					pmotor->clockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(pmotor->counterclockwise_rotation_enable_port,
					pmotor->counterclockwise_rotation_enable_pin, GPIO_PIN_SET);
			pmotor->direction_of_rotation_flag = MOTOR_ROTATION_COUNTERCLOCKWISE;
	}

}
