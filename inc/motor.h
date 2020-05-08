#ifndef __MOTOR_H__
#define __MOTOR_H__
#include <rtthread.h>
#include <rtdevice.h>

#if (defined(PKG_USING_MOTOR)||defined(RT_DEBUG_MOTOR))&&defined(BSP_USING_PWM1)

#define PWM_PERIOD           500000 /* 周期为0.5ms，单位为纳秒ns */

enum vibration_strength
{
	Strength_25  = PWM_PERIOD/4,
	Strength_50  = PWM_PERIOD/2,
	Strength_75  = PWM_PERIOD*3/4,
	Strength_100 = PWM_PERIOD
};

void operating_motor(enum vibration_strength strength,rt_uint32_t duration);

void message_motor(enum vibration_strength strength);

#endif

#endif

