#ifndef HAL_AUDIO_INPUT_H
#define HAL_AUDIO_INPUT_H

/*****************************************************************************
 Prototype    : Hal_audio_input_set_anr_enable
 Description  : 设置ANR功能开关
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
extern int Hal_audio_input_set_anr_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_audio_input_set_aec_enable
 Description  : 设置AEC功能开关
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
extern int Hal_audio_input_set_aec_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_audio_input_channel_get_sample_points_perFrame
 Description  : 获取每帧音频的采样点个数，如1024，
 				则samplerate为8000Hz，音频帧率则为8000/1024=8fps
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
extern int Hal_audio_input_channel_get_sample_points_perFrame();

/*****************************************************************************
 Prototype    : Hal_Mic_set_vol
 Description  : 设置Mic音量档位
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
extern int Hal_Mic_set_vol(int vol);

/*****************************************************************************
 Prototype    : Hal_Mic_init_divided_levels
 Description  : 将Mic音量设置档位分为多少档位
 Input        : int levels  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_Mic_init_divided_levels(int levels);

#endif
