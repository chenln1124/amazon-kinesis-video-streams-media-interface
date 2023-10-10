#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#ifdef CONFIG_CPU_T31
#include "gpio_description_t31.h"
#endif

#ifdef CONFIG_CPU_T40
#include "gpio_description_t40.h"
#endif

#ifdef CONFIG_CPU_T41
#include "gpio_description_t41.h"
#endif

#ifdef CONFIG_CPU_SSC335
#include "gpio_description_ssc335.h"
#endif

#ifdef CONFIG_CPU_HI3518EV200
#include "gpio_description_hi3518ev200.h"
#endif

#ifdef CONFIG_CPU_RTS3903N
#include "gpio_description_rts3903n.h"
#endif

typedef enum
{
	E_HAL_IRCUT_OFF = 0,	//白天
	E_HAL_IRCUT_ON = 1,		//晚上
}E_HAL_IRCUT_STAT;

typedef enum
{
	E_HAL_IRLED_OFF = 0,
	E_HAL_IRLED_ON = 1,
}E_HAL_IRLED_STAT;

typedef enum
{
	E_HAL_LED_OFF = 0,
	E_HAL_LED_ON = 1,
}E_HAL_LED_STAT;

typedef enum
{
	E_HAL_LED_RED = 0,
	E_HAL_LED_BLUE = 1,	
	E_HAL_LED_GREEN = 2,	
	E_HAL_LED_WHITE = 3,
	E_HAL_LED_MAX,
}E_HAL_LED_INDEX;

typedef enum
{
	E_HAL_RESET_BUTTON_PRESSED = 0,
	E_HAL_RESET_BUTTON_RELEASED = 1,
}E_HAL_RESET_BUTTON_STAT;

typedef enum
{
	E_HAL_USB_DETECT_ON = 0,
	E_HAL_USB_DETECT_OFF = 1,
}E_HAL_USB_DETECT_STAT;

typedef enum
{
	E_HAL_WIFI_POWER_OFF = 0,
	E_HAL_WIFI_POWER_ON = 1,
}E_HAL_WIFI_POWER_STAT;

typedef enum
{
	E_HAL_SPEAKER_POWER_OFF = 0,
	E_HAL_SPEAKER_POWER_ON = 1,
}E_HAL_SPEAKER_POWER_STAT;

typedef enum
{
	E_HAL_MOTOR_POWER_OFF = 0,
	E_HAL_MOTOR_POWER_ON = 1,
}E_HAL_MOTOR_POWER_STAT;

typedef enum
{
	E_HAL_GPIO_DIR_INPUT = 0,
	E_HAL_GPIO_DIR_OUTPUT,	
}E_HAL_GPIO_DIRECTION;

typedef enum
{
	E_HAL_GPIO_LEVEL_LOW = 0,
	E_HAL_GPIO_LEVEL_HIGH,
}E_HAL_GPIO_LEVEL;

typedef enum
{
	E_HAL_IRCUT_DOUBLE_PIN_CTRL = 0,
	E_HAL_IRCUT_SINGEL_PIN_CTRL,	
}E_HAL_IRCUT_PIN_CTRL_MODE;

typedef enum
{
	E_HAL_PIR_DIGITAL_DOUBLE_PIN_CTRL = 0,
	E_HAL_PIR_DIGITAL_SINGEL_PIN_CTRL,	
	E_HAL_PIR_ANALOG_SINGEL_SENSOR,	
	E_HAL_PIR_ANALOG_THREE_SENSOR,
}E_HAL_PIR_SENSOR_SELECT;
	
typedef struct Hal_gpio_extra_config_s
{
	E_HAL_IRCUT_PIN_CTRL_MODE eIrcutPinMode;
	E_HAL_PIR_SENSOR_SELECT ePirSensor;
}Hal_gpio_extra_config_s;

/* GPIO功能涉及多个引脚时的index索引号 */
#define HAL_MAX_GPIO_CTRL_PIN_NUMBERS	5
typedef enum
{
	E_HAL_GPIO_IRCUT_AIN = 0,
	E_HAL_GPIO_IRCUT_BIN,
}E_HAL_GPIO_IRCUT_INDEX;

typedef enum
{
	E_HAL_GPIO_PIR_LEVEL_SET0 = 0,
	E_HAL_GPIO_PIR_LEVEL_SET1,	
	E_HAL_GPIO_PIR_ALARM_INPUT1,
	E_HAL_GPIO_PIR_ALARM_INPUT2,
	E_HAL_GPIO_PIR_ALARM_INPUT3,
}E_HAL_GPIO_PIR_INDEX;

typedef enum
{
	E_HAL_GPIO_LED_RED = 0,
	E_HAL_GPIO_LED_BLUE,
	E_HAL_GPIO_LED_GREEN,
	E_HAL_GPIO_LED_WHITE,
	E_HAL_GPIO_IRLED,
	E_HAL_GPIO_IRCUT,
	E_HAL_GPIO_RESET,
	E_HAL_GPIO_WIFI_POWER,
	E_HAL_GPIO_MOTOR_POWER,
	E_HAL_GPIO_SPEAK_POWER,
	E_HAL_GPIO_PIR,
	E_HAL_GPIO_USB_DETECT,
	E_HAL_GPIO_TCH_STOUT,
	E_HAL_GPIO_RF_PTT,
	E_HAL_GPIO_MAX,
}E_HAL_GPIO_INDEX;

/* GPIO配置参数结构体 */
typedef struct Hal_gpio_config_s
{
	int bSupport;
	int gpioCtrlPinNumber;		
		//功能涉及几个引脚，通常一个。 
		//模拟PIR，PIR引脚数为4时，则为三个PIR搭配的广角检测，一个PIR报警灵敏度设置脚, 三个报警状态输入脚
		//模拟PIR，PIR引脚数为2时，则为单个PIR检测，一个PIR报警灵敏度设置脚；
		//数字PIR，PIR引脚数为3时，两个gpio设置脚搭配控制灵敏度，一个报警状态输入脚
		//数字PIR，PIR引脚数为2时，一个gpio设置脚高低电平控制灵敏度，一个报警状态输入脚
		//IRCUT，正常用两个脚位搭配高低电平控制
		//单引脚控制IRCUT
	int muxCtrlRegOffset[HAL_MAX_GPIO_CTRL_PIN_NUMBERS];	//复用寄存器地址偏移量
	int pinNumber[HAL_MAX_GPIO_CTRL_PIN_NUMBERS];
	E_HAL_GPIO_DIRECTION eDirControl[HAL_MAX_GPIO_CTRL_PIN_NUMBERS];
	E_HAL_GPIO_LEVEL eValidLevel[HAL_MAX_GPIO_CTRL_PIN_NUMBERS];
	int bDefaultOn[HAL_MAX_GPIO_CTRL_PIN_NUMBERS];
	Hal_gpio_extra_config_s extraCfg;
}Hal_gpio_config_t;

/*****************************************************************************
 Prototype    : Hal_GPIO_motor_power_control
 Description  : 控制电机电源
 Input        : E_HAL_MOTOR_POWER_STAT eValue  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_motor_power_control(E_HAL_MOTOR_POWER_STAT eValue);

/*****************************************************************************
 Prototype    : Hal_GPIO_speaker_power_control
 Description  :  
 Input        : E_HAL_SPEAKER_POWER_STAT eValue  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_speaker_power_control(E_HAL_SPEAKER_POWER_STAT eValue);

/*****************************************************************************
 Prototype    : Hal_GPIO_wifi_power_control
 Description  :  
 Input        : E_HAL_WIFI_POWER_STAT eValue  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_wifi_power_control(E_HAL_WIFI_POWER_STAT eValue);


/*****************************************************************************
 Prototype    : Hal_GPIO_get_reset_button_status
 Description  : 获取复位键的状态
 Input        : None
 Output       : None
 Return Value : E_HAL_RESET_BUTTON_STAT
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_get_reset_button_status();

/*****************************************************************************
 Prototype    : Hal_GPIO_get_usb_detect_status
 Description  : USB电源插入状态
 Input        : None
 Output       : None
 Return Value : 0:input; 1:break;
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/8/30
    Author       : gz
    Modification : Created function

*****************************************************************************/
int Hal_GPIO_get_usb_detect_status();

/*****************************************************************************
 Prototype    : Hal_GPIO_LED_control
 Description  : 控制各LED的亮灭
 Input        : E_HAL_LED_INDEX eLedIndex  
                E_HAL_LED_STAT eValue      
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_LED_control(E_HAL_LED_INDEX eLedIndex, E_HAL_LED_STAT eValue);

/*****************************************************************************
 Prototype    : Hal_GPIO_IRLED_control
 Description  : 控制红外灯开关
 Input        : E_HAL_IRLED_STAT eValue  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_IRLED_control(E_HAL_IRLED_STAT eValue);

/*****************************************************************************
 Prototype    : Hal_GPIO_IRCUT_control
 Description  : 控制IRCUT开关
 Input        : E_HAL_IRCUT_STAT eValue  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_IRCUT_control(E_HAL_IRCUT_STAT eValue);

/*****************************************************************************
 Prototype    : Hal_GPIO_get_all_config
 Description  : 库内部使用，获取所有功能GPIO的参数
 Input        : Hal_gpio_config_t *pGpioCfg  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/13
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_get_all_config(Hal_gpio_config_t **pGpioCfg);

/*****************************************************************************
 Prototype    : Hal_GPIO_get_config
 Description  : 库内部使用，获取指定功能gpio的参数
 Input        : E_HAL_GPIO_INDEX eGpioIndex   
                Hal_gpio_config_t **pGpioCfg  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/13
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_get_config(E_HAL_GPIO_INDEX eGpioIndex, Hal_gpio_config_t **pGpioCfg);

/*****************************************************************************
 Prototype    : Hal_GPIO_get_ptz_is_running
 Description  : 云台电机是否正在运转
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/26
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_get_ptz_is_running();

/*****************************************************************************
 Prototype    : Hal_GPIO_get_power_capacity
 Description  : 获取当前电量值
 Input        : int *capacity_val  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/8/30
    Author       : gz
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_get_power_capacity(int *capacity_val, int *capacity_exist);

/*****************************************************************************
 Prototype    : Hal_GPIO_uninit
 Description  :  
 Input        : None
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_uninit();

typedef int (*Hal_GPIO_get_ptz_running_status)(void);
/*****************************************************************************
 Prototype    : Hal_GPIO_init
 Description  :  
 Input        : None
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_GPIO_init(Hal_gpio_config_t gpio_cfg[E_HAL_GPIO_MAX], Hal_GPIO_get_ptz_running_status handle);

#endif
