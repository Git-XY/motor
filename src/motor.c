#include "motor.h"

#define PWM_DEV_NAME        "pwm1"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL      1      /* PWM通道 */

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */

static int pwm_motor(int argc, char *argv[])
{
    rt_uint32_t period;

    period = 500000;    /* 周期为0.5ms，单位为纳秒ns */

    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 250000);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
	rt_thread_mdelay(100);
	rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
	rt_thread_mdelay(100);
	rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    rt_thread_mdelay(100);
	rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
	
	return  RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_motor, pwm motor sample);
