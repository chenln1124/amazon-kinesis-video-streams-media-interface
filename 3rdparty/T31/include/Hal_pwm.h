#ifndef HAL_PWM_H
#define HAL_PWM_H

typedef struct _IPC_PWM_LIGHT_CFG_S_
{
    int enable;     /* 0:off  1:on*/
    int lightness;  /* 0 - 100*/
	int lightness_threshold;  //开始亮有效百分比
	int pwm_frequency;
	int duty_reverse;
}ipc_pwm_light_cfg;

typedef enum
{
	E_HAL_PWM_CHN0 = 0,
	E_HAL_PWM_CHN1 = 1,	
	E_HAL_PWM_CHN2 = 2,
	E_HAL_PWM_CHN3 = 3,
	E_HAL_PWM_CHN_MAX,
}E_HAL_PWM_CHN;

typedef enum
{
	E_HAL_PWM_TYPE_IRLED = 0,
	E_HAL_PWM_TYPE_FLOODLIGHT = 1,
	E_HAL_PWM_TYPE_MAX,
}E_HAL_PWM_TYPE;

typedef enum
{
	E_HAL_PWM_LIGHT_OFF = 0,
	E_HAL_PWM_LIGHT_ON = 1,
}E_HAL_PWM_LIGHT_STATUS;
	
/*****************************************************************************
 Prototype    : Hal_PWM_control_light_brightness
 Description  : 控制pwm灯亮度
 Input        : E_HAL_PWM_TYPE pwm_chn  
                int pwm_duty           
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_PWM_control_light_brightness(E_HAL_PWM_TYPE pwm_chn, int pwm_duty);

/*****************************************************************************
 Prototype    : Hal_PWM_control_light_onoff
 Description  : 控制pwm灯亮灭
 Input        : E_HAL_PWM_TYPE pwm_chn         
                E_HAL_PWM_LIGHT_STATUS onoff  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_PWM_control_light_onoff(E_HAL_PWM_TYPE pwm_chn, E_HAL_PWM_LIGHT_STATUS onoff);

/*****************************************************************************
 Prototype    : Hal_PWM_light_init
 Description  : 初始化启动PWM灯控
 Input        : E_HAL_PWM_CHN floodlight_pwmChn                 
                int floodlight_muxCtrlCfg             
                ipc_pwm_light_cfg floodlight_pwm_cfg  
                E_HAL_PWM_CHN irled_pwmChn                      
                int irled_muxCtrlCfg                  
                ipc_pwm_light_cfg irled_pwm_cfg       
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/12
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_PWM_light_init(int floodlight_pwmChn, int floodlight_muxCtrlCfg, ipc_pwm_light_cfg floodlight_pwm_cfg, int irled_pwmChn, int irled_muxCtrlCfg, ipc_pwm_light_cfg irled_pwm_cfg);

#endif
