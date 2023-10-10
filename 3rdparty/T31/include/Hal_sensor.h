#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H

/* PIR Sensor */
typedef enum
{
	E_HAL_SENSOR_PIR_NO_ALARM = 0,
	E_HAL_SENSOR_PIR1_TRIGGERED = 0x01,
	E_HAL_SENSOR_PIR2_TRIGGERED = 0x02,
	E_HAL_SENSOR_PIR3_TRIGGERED = 0x04,
}E_HAL_SENSOR_PIR_ALARM_STATUS;

typedef enum
{
	E_HAL_SENSOR_PIR_LEVEL_LOWEST = 1,
	E_HAL_SENSOR_PIR_LEVEL_LOW,
	E_HAL_SENSOR_PIR_LEVEL_MIDDLE,
	E_HAL_SENSOR_PIR_LEVEL_HIGH,
	E_HAL_SENSOR_PIR_LEVEL_HIGHEST,
}E_HAL_SENSOR_PIR_LEVEL;

typedef enum
{
	E_HAL_SENSOR_PIR_DIGITAL = 0,
	E_HAL_SENSOR_PIR_ANALOG = 1,
}E_HAL_SENSOR_PIR_TYPE;

/*****************************************************************************
 Prototype    : Hal_sensor_PIR_get_alarm_status
 Description  : 获取PIR报警状态
 Input        : None
 Output       : None
 Return Value : E_HAL_SENSOR_PIR_ALARM_STATUS
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/4
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_sensor_PIR_get_alarm_status();

/*****************************************************************************
 Prototype    : Hal_sensor_PIR_set_detection_level
 Description  : 设置PIR侦测档位
 Input        : E_HAL_SENSOR_PIR_LEVEL level  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/5
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_sensor_PIR_set_detection_level(E_HAL_SENSOR_PIR_LEVEL level);

/*****************************************************************************
 Prototype    : Hal_sensor_PIR_init
 Description  : PIR Sensor init
 Input        : E_HAL_SENSOR_PIR_TYPE pir_type  
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/4
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_sensor_PIR_init(E_HAL_SENSOR_PIR_TYPE pir_type);

/* Temperature/Humidity Sensor */
typedef enum
{
	E_HAL_SENSOR_TEMP_HUM_TH06C = 0,
	E_HAL_SENSOR_TEMP_HUM_CT75 = 1,
	E_HAL_SENSOR_TEMP_HUM_CHT8305 = 2,
	E_HAL_SENSOR_TEMP_HUM_MAX,
}E_HAL_SENSOR_TEMP_HUM_TYPE;

/*****************************************************************************
 Prototype    : Hal_sensor_temperature_humidity_get_current_data
 Description  : 获取当前温湿度数值
 Input        : int *temp  
                int *hum   
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/5
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_sensor_temperature_humidity_get_current_data(int *temp, int *hum);

/*****************************************************************************
 Prototype	  : Hal_sensor_temperature_humidity_init
 Description  : 温湿度初始化
 Input		  :  
 Output 	  : None
 Return Value : 
 Calls		  : 
 Called By	  : 
 
  History		 :
  1.Date		 : 2021/3/5
	Author		 : Owen
	Modification : Created function

*****************************************************************************/
extern int Hal_sensor_temperature_humidity_init();


#endif
