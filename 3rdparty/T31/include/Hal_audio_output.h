#ifndef HAL_AUDIO_OUTPUT_H
#define HAL_AUDIO_OUTPUT_H
#include "Hal_av_channel_params.h"

typedef enum
{
	E_HAL_AO_STATUS_IDLE = 0,
	E_HAL_AO_STATUS_IN_USE = 1,
}E_HAL_AO_STATUS;

/*****************************************************************************
 Prototype    : Hal_speaker_play_packet
 Description  : 播放音频数据包
 Input        : IPC_AUDIO_ENCTYPE audio_type             
                unsigned char *audio_data  
                int packet_len             
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_speaker_play_packet(IPC_AUDIO_ENCTYPE audio_type, unsigned char *audio_data, int packet_len);

/*****************************************************************************
 Prototype    : Hal_speaker_get_is_inUse
 Description  : 获取当前喇叭是否正在使用
 Input        : None
 Output       : None
 Return Value : E_HAL_AO_STATUS
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_speaker_get_is_inUse();

/*****************************************************************************
 Prototype    : Hal_speaker_clear_buff
 Description  : 清空AO通道缓存buffer
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
extern int Hal_speaker_clear_buff();

/*****************************************************************************
 Prototype    : Hal_audio_output_set_anr_enable
 Description  : 设置AO ANR功能开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/2
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_audio_output_set_anr_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_audio_output_set_full_duplex_start
 Description  : 当APP开启双向对讲(全双工)时，调用此接口，-
                底层库会自动降低喇叭音量保障AEC效果
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/5/21
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_audio_output_set_full_duplex_start(int enable);

/*****************************************************************************
 Prototype    : Hal_Speaker_set_vol
 Description  : 设置Speaker音量档位
 Input        : int vol  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_Speaker_set_vol(int vol);

/*****************************************************************************
Prototype    : Hal_Mic_init_divided_levels
Description  : 将Speaker音量设置档位分为多少档位
Input 	   : int levels  
Output	   : None
Return Value : 
Calls 	   : 
Called By    : 

History		  :
1.Date		  : 2021/3/8
Author 	  : Owen
Modification : Created function

*****************************************************************************/
extern int Hal_Speaker_init_divided_levels(int levels);
#endif

