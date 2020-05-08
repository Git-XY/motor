#include "motor.h"
#include <stdio.h>

#if (defined(PKG_USING_MOTOR)||defined(RT_DEBUG_MOTOR))&&defined(BSP_USING_PWM1)

#define PWM_DEV_NAME        "pwm1"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL      1      /* PWM通道 */

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */

static int rt_hw_pwm_motor_device()
{
    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm device run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }
	return  RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_motor_device);

void operating_motor(enum vibration_strength strength,rt_uint32_t duration)
{
	rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, PWM_PERIOD, strength);
	rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
	rt_thread_mdelay(duration);
	rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
}

void message_motor(enum vibration_strength strength)
{
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, PWM_PERIOD, strength);
    rt_uint8_t count = 2;
	while(count--)
	{
		rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
		rt_thread_mdelay(100);
		rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
		rt_thread_mdelay(100);
	}
}

#if defined(RT_DEBUG_MOTOR_CMD)&&defined(RT_DEBUG_MOTOR)
static void motor1(int argc, char**argv)
{
	if (argc < 2)
    {
        rt_kprintf("Please input'motor1 <Strength value> <range:125000-500000>'\n");
        return ;
    }
	
	rt_uint32_t num = 0;
	sscanf(argv[1],"%d",&num);
	if(num < Strength_25 || num > Strength_100)
		return ;
	
		message_motor(num);
}
MSH_CMD_EXPORT(motor1, motor1 sample: motor1 <Strength value> <range:125000-500000>);


static void motor2(int argc, char**argv)
{
	if (argc < 2)
    {
        rt_kprintf("Please input'motor2  <Strength value range:125000-500000><time value ms>'\n");
        return ;
    }
	
	rt_uint32_t num = 0,num2= 0;
	sscanf(argv[1],"%d",&num);
	sscanf(argv[2],"%d",&num2);
	if(num < Strength_25 || num > Strength_100)
		return ;
	
		operating_motor(num,num2);
}
MSH_CMD_EXPORT(motor2,  motor2 sample: motor2 <Strength value range:125000-500000><time value ms>);
#endif

#endif

