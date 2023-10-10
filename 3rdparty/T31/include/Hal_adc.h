#ifndef HAL_ADC_H
#define HAL_ADC_H

typedef struct ipc_lux_threshold_config_s
{
	unsigned int adc_print_enable;
	unsigned int minlux_adc;
	unsigned int maxlux_adc;
	unsigned int adc_threshold_ignore_md;
	unsigned int soft_flag;
}ipc_lux_threshold_config;

typedef enum
{
	E_ADC_LIGHT_SENSOR_NIGHT = 0,
	E_ADC_LIGHT_SENSOR_DAY = 1,
}E_ADC_LIGHT_SENSOR_MODE;

/*****************************************************************************
 Prototype    : Hal_ADC_get_current_light_sensor_value
 Description  : 获取当前光敏adc值
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_ADC_get_current_light_sensor_value();

/*****************************************************************************
 Prototype    : Hal_ADC_get_light_sensor_day_night_mode
 Description  : 获取ADC阈值判定后的白天黑夜状态
 Input        : None
 Output       : None
 Return Value : E_ADC_LIGHT_SENSOR_MODE
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/4
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_ADC_get_light_sensor_day_night_mode();

/*****************************************************************************
 Prototype    : Hal_ADC_get_light_sensor_config
 Description  :  
 Input        : ipc_lux_threshold_config **pLuxConfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern void Hal_ADC_get_light_sensor_config(ipc_lux_threshold_config **pLuxConfig);

/*****************************************************************************
 Prototype    : Hal_ADC_light_sensor_config_init
 Description  :  
 Input        : ipc_lux_threshold_config lux_config  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern void Hal_ADC_light_sensor_config_init(ipc_lux_threshold_config lux_config);

#endif
