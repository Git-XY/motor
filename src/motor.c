#include "motor.h"

#define PWM_DEV_NAME        "pwm1"  /* PWM�豸���� */
#define PWM_DEV_CHANNEL      1      /* PWMͨ�� */

struct rt_device_pwm *pwm_dev;      /* PWM�豸��� */

static int pwm_motor(int argc, char *argv[])
{
    rt_uint32_t period;

    period = 500000;    /* ����Ϊ0.5ms����λΪ����ns */

    /* �����豸 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* ����PWM���ں�������Ĭ��ֵ */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 250000);
    /* ʹ���豸 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
	rt_thread_mdelay(100);
	rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
	rt_thread_mdelay(100);
	rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    rt_thread_mdelay(100);
	rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
	
	return  RT_EOK;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(pwm_motor, pwm motor sample);
