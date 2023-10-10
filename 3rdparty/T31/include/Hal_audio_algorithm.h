#ifndef HAL_AUDIO_ALGO_H
#define HAL_AUDIO_ALGO_H
#include "Hal_av_channel_params.h"

typedef enum
{
	//音频分贝侦测开关。开启时,
	//若音频只有一路使能，默认将PCM数据通过回调函数Hal_Get_PCM_Stream_From_Codec(E_HAL_AUDIO_STREAM, E_HAL_STREAM_SUB_CHANNEL),输出PCM码流
	//若两路音频均使能，默认将PCM数据通过回调函数Hal_Get_PCM_Stream_From_Codec(E_HAL_AUDIO_STREAM, E_HAL_STREAM_THIRD_CHANNEL),输出PCM码流
	E_HAL_AUDIO_ALGORITHM_DB_SOUND_DETECTION = 0,
	E_HAL_AUDIO_ALGORITHM_MAX,
}E_HAL_AUDIO_ALGORITHM_TYPE;
	
typedef struct Hal_audio_algorithm_chn_config
{
	int bSupport;
	union
	{
		int reserve;
	};
	/* 从codec出来的音视频帧流，外部对接使用此回调获取 */
	int (*Hal_Get_PCM_Stream_From_Codec)(E_HAL_STREAM_TYPE stream_type, E_HAL_STREAM_CHANNEL_TYPE chn_type, Hal_frame_head_t *frame_head, unsigned char *frame_addr);
}Hal_audio_algorithm_chn_config;

/*****************************************************************************
 Prototype    : Hal_get_current_pcm_audio_stream_channel
 Description  : 当AI音频格式不是PCM，但需要另外一路PCM时，-
                其实不用再创建一路PCM AI通道。可从AI主码流的原-
                始数据获取，送出去

                可通过调用Hal_audio_algorithm_init使能，
                此处返回Hal_Get_PCM_Stream_From_Codec回调往外抛数据时的E_HAL_STREAM_CHANNEL_TYPE chn_type
 Input        : None
 Output       : None
 Return Value : 返回E_HAL_STREAM_CHANNEL_TYPE chn_type
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/12/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_current_pcm_audio_stream_channel();

/*****************************************************************************
 Prototype    : Hal_get_audio_whether_need_extra_pcm_stream
 Description  : 内部库使用
 Input        : None
 Output       : None
 Return Value : 0: 表示不用另行塞流；1: 需要另行塞流，aEncChn指定塞入流库通道；-1：表示无需额外支持PCM流
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/27
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_audio_whether_need_extra_pcm_stream(E_HAL_AV_CHNNEL *aEncChn);

/*****************************************************************************
 Prototype    : Hal_get_audio_algo_channel_config
 Description  : 内部库使用，获取算法通道全局变量参数
 Input        : E_HAL_AUDIO_ALGORITHM_TYPE algo_type             
                Hal_audio_algorithm_chn_config **pAlgoChnconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/27
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_audio_algo_channel_config(E_HAL_AUDIO_ALGORITHM_TYPE algo_type, Hal_audio_algorithm_chn_config **pAlgoChnconfig);

/*****************************************************************************
 Prototype    : Hal_set_audio_algo_channel_config
 Description  : 内部库使用，同步算法通道全局变量参数
 Input        : E_HAL_AUDIO_ALGORITHM_TYPE algo_type            
                Hal_audio_algorithm_chn_config *pAlgoChnconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/27
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_set_audio_algo_channel_config(E_HAL_AUDIO_ALGORITHM_TYPE algo_type, Hal_audio_algorithm_chn_config *pAlgoChnconfig);

/*****************************************************************************
 Prototype    : Hal_audio_algorithm_init
 Description  : 音频算法初始化
 Input        : Hal_audio_algorithm_chn_config algo_chn_cfg[E_HAL_AUDIO_ALGORITHM_MAX]  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/27
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_audio_algorithm_init(Hal_audio_algorithm_chn_config algo_chn_cfg[E_HAL_AUDIO_ALGORITHM_MAX]);
#endif