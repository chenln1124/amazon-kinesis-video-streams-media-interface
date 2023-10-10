#ifndef HAL_VIDEO_INPUT_H
#define HAL_VIDEO_INPUT_H

#include "Hal_av_channel_params.h"

/*****************************************************************************
 Prototype    : Hal_JPEG_chn_snapshot
 Description  : 抓拍jpeg至buffer
 Input        : unsigned char *snap_buffer  
                int *snap_buff_len           
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_JPEG_chn_snapshot(unsigned char *snap_buffer, int *snap_buff_len);

/*****************************************************************************
 Prototype    : Hal_video_channel_set_framerate
 Description  : framerate
 Input        : E_HAL_AV_CHNNEL vencChn  
                int fps                  
                int gop                  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/16
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_channel_set_framerate(E_HAL_AV_CHNNEL vencChn, int fps, int gop);

/*****************************************************************************
 Prototype    : Hal_video_channel_set_bitrate
 Description  : 码流，单位kbps
 Input        : E_HAL_AV_CHNNEL vencChn  
                int kbps                 
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/16
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_channel_set_bitrate(E_HAL_AV_CHNNEL vencChn, int kbps);

/*****************************************************************************
 Prototype    : Hal_video_channel_set_rc_mode
 Description  : 编码模式
 Input        : E_HAL_AV_CHNNEL vencChn  
                E_IPC_VIDEO_RCMODE mode  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/16
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_channel_set_rc_mode(E_HAL_AV_CHNNEL vencChn, E_IPC_VIDEO_RCMODE mode);

/*****************************************************************************
 Prototype    : Hal_video_channel_request_I_frame
 Description  : 强制I帧接口
 Input        : E_HAL_AV_CHNNEL vencChn  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/28
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_channel_request_I_frame(E_HAL_AV_CHNNEL vencChn);

/*****************************************************************************
 Prototype    : Hal_video_channel_params_reconfig
 Description  : 重置指定视频通道所有的视频参数
 Input        : int vencChn // only support for main and sub channel
                             
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_channel_params_reconfig(E_HAL_AV_CHNNEL vencChn, ipc_video_config video_params);


#endif
