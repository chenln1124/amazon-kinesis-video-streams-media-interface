#ifndef HAL_MAIN_H
#define HAL_MAIN_H
#include <stdio.h>

typedef enum
{
	HAL_CPU_HI3518EV200 = 0,
	HAL_CPU_HI3518EV300,
	
	HAL_CPU_RTS3903N,
	HAL_CPU_RTS3906N,
	HAL_CPU_RTS3904N,
	HAL_CPU_RTS3916N,

	HAL_CPU_SSC333,
	HAL_CPU_SSC335,
	HAL_CPU_SSC337,
	HAL_CPU_SSC335DE,
	HAL_CPU_SSC337DE,

	HAL_CPU_T31,
	HAL_CPU_T40,
    HAL_CPU_T41,
}HAL_CPU_TYPE_E;

/*****************************************************************************
 Prototype    : Hal_get_stream_from_codec
 Description  : 指定编码通道，按帧获取音视频帧数据
 Input        : E_HAL_AV_CHNNEL vChn          
                Hal_frame_head_t *frame_head  
                unsigned char *frame_addr     
                int max_frame_size            
                int timeout_ms            
 Output       : None
 Return Value : 0:success otherwise:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/26
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_stream_from_codec(E_HAL_AV_CHNNEL vChn, Hal_frame_head_t *frame_head, unsigned char *frame_addr, int max_frame_size, int timeout_ms);

/*****************************************************************************
 Prototype    : Hal_get_av_channel_is_support
 Description  : 库内部使用，获取av通道全局变量，是否支持-
                此通道
 Input        : E_HAL_AV_CHNNEL chn  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_av_channel_is_support(E_HAL_AV_CHNNEL chn);

/*****************************************************************************
 Prototype    : Hal_get_av_channel_config
 Description  : 库内部使用，获取av通道全局变量参数
 Input        : E_HAL_AV_CHNNEL chn        
                ipc_av_config **pAVconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_av_channel_config(E_HAL_AV_CHNNEL chn, ipc_av_config **pAVconfig);

/*****************************************************************************
 Prototype    : Hal_set_av_channel_config
 Description  : 库内部使用，同步av通道全局变量参数
 Input        : E_HAL_AV_CHNNEL chn       
                ipc_av_config *pAVconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_set_av_channel_config(E_HAL_AV_CHNNEL chn, ipc_av_config *pAVconfig);

/*****************************************************************************
 Prototype    : Hal_get_cpu_type
 Description  : 通过方案预留寄存器，读取CPU主控名字
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/5/24
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_cpu_type();

/*****************************************************************************
 Prototype    : Hal_get_max_resolution_width_height
 Description  : 获取配置的最大分辨率
 Input        : int *maxResWidth   
                int *maxResHeight  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/4/25
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern void Hal_get_max_resolution_width_height(int *maxResWidth, int *maxResHeight);

/*****************************************************************************
 Prototype    : Hal_uninit
 Description  : 反初始化，释放所有资源
 Input        : None
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/22
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_uninit();

/*****************************************************************************
 Prototype    : Hal_init
 Description  : 初始化
 Input        : int maxResWidth                            
                int maxResHeight                           
                ipc_av_config av_config[E_HAL_AV_CHN_MAX]  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/4/25
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_init(int maxResWidth, int maxResHeight, ipc_av_config av_config[E_HAL_AV_CHN_MAX]);
#endif
