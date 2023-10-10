#ifndef HAL_AV_CHANNEL_PARAMS_H
#define HAL_AV_CHANNEL_PARAMS_H

#include "Hal_stream.h"

/* Video Resolution */
#define VIDEO_WIDTH_8M			(3264)
#define VIDEO_HEIGHT_8M			(2448)
#define VIDEO_WIDTH_4M			(2560)
#define VIDEO_HEIGHT_4M			(1440)
#define VIDEO_WIDTH_3M			(2304)
#define VIDEO_HEIGHT_3M			(1296)
#define VIDEO_WIDTH_1080P_2M	(1920)
#define VIDEO_HEIGHT_1080P_2M	(1080)
#define VIDEO_WIDTH_720P_1M		(1280)
#define VIDEO_HEIGHT_720P_1M	(720)

#define VIDEO_WIDTH_960X540		(960)
#define VIDEO_HEIGHT_960X540	(540)

#define VIDEO_WIDTH_720X480		(720)
#define VIDEO_HEIGHT_720X480	(480)
	
#define VIDEO_WIDTH_VGA			(640)
#define VIDEO_HEIGHT_VGA		(480)

#define VIDEO_WIDTH_640X360		(640)
#define VIDEO_HEIGHT_640X360	(360)

#define VIDEO_WIDTH_512X288		(512)
#define VIDEO_HEIGHT_512X288	(288)

#define VIDEO_WIDTH_352X288		(352)
#define VIDEO_HEIGHT_352X288	(288)

#define VIDEO_WIDTH_352X240		(352)
#define VIDEO_HEIGHT_352X240	(240)

#define VIDEO_WIDTH_352X144		(352)
#define VIDEO_HEIGHT_352X144	(144)

#define VIDEO_WIDTH_128X72		(128)
#define VIDEO_HEIGHT_128X72		(72)

/* Video framerate */
#define VIDEO_FRAMERATE_30FPS	(30)
#define VIDEO_FRAMERATE_25FPS	(25)
#define VIDEO_FRAMERATE_20FPS	(20)
#define VIDEO_FRAMERATE_15FPS	(15)
#define VIDEO_FRAMERATE_10FPS	(10)
#define VIDEO_FRAMERATE_8FPS	(8)
#define VIDEO_FRAMERATE_5FPS	(5)

/* Video gop */
#define VIDEO_GOP_30			(30)
#define VIDEO_GOP_25			(25)
#define VIDEO_GOP_20			(20)
#define VIDEO_GOP_15			(15)
#define VIDEO_GOP_10			(10)
#define VIDEO_GOP_5				(5)
#define VIDEO_GOP_1				(1)

/* Video Bitrate kbps */
#define VIDEO_BITRATE_3Mbps		(3000)
#define VIDEO_BITRATE_2_5Mbps	(2500)
#define VIDEO_BITRATE_2Mbps		(2000)
#define VIDEO_BITRATE_1_5Mbps	(1500)
#define VIDEO_BITRATE_1_3Mbps	(1300)
#define VIDEO_BITRATE_1_2Mbps	(1200)
#define VIDEO_BITRATE_1_8Mbps	(1800)
#define VIDEO_BITRATE_1Mbps		(1024)
#define VIDEO_BITRATE_896Kbps	(896)
#define VIDEO_BITRATE_800Kbps	(800)
#define VIDEO_BITRATE_768Kbps	(768)
#define VIDEO_BITRATE_600Kbps	(600)
#define VIDEO_BITRATE_550Kbps	(550)
#define VIDEO_BITRATE_512Kbps	(512)
#define VIDEO_BITRATE_384Kbps	(384)
#define VIDEO_BITRATE_256bps	(256)
#define VIDEO_BITRATE_128Kbps	(128)
#define VIDEO_BITRATE_64Kbps	(64)

/* Audio Sample rate */
#define AUDIO_SAMPLE_RATE_8K		(8000)		/* 8kHz sampling rate */
#define AUDIO_SAMPLE_RATE_11K		(11025)     /* 11.025kHz sampling rate */
#define AUDIO_SAMPLE_RATE_12K		(12000)		/* 12kHz sampling rate */
#define AUDIO_SAMPLE_RATE_16K		(16000)		/* 16kHz sampling rate */
#define AUDIO_SAMPLE_RATE_22K		(22050)		/* 22.05kHz sampling rate */
#define AUDIO_SAMPLE_RATE_24K		(24000)		/* 24kHz sampling rate */
#define AUDIO_SAMPLE_RATE_32K		(32000)		/* 32kHz sampling rate */
#define AUDIO_SAMPLE_RATE_44K		(44100)		/* 44.1kHz sampling rate */
#define AUDIO_SAMPLE_RATE_48K		(48000)		/* 48kHz sampling rate */
#define AUDIO_SAMPLE_RATE_96K		(96000)		/* 96kHz sampling rate */

/* Audio Bitwidth */
#define AUDIO_BITWIDTH_8		(8)
#define AUDIO_BITWIDTH_16		(16)

/* av channel params */
typedef enum ipc_video_enctype
{
	IPC_VIDEO_ENCTYPE_YUV	=	1,
	IPC_VIDEO_ENCTYPE_H264	=	2,
	IPC_VIDEO_ENCTYPE_H265	=	3,
	IPC_VIDEO_ENCTYPE_MJPEG	=	4
}IPC_VIDEO_ENCTYPE;

typedef enum ipc_video_rcmode
{
	E_IPC_RCMODE_CBR         = 1,
	E_IPC_RCMODE_VBR         = 2,
	E_IPC_RCMODE_AVBR        = 3,
	E_IPC_RCMODE_ABR         = 4,
	E_IPC_RCMODE_FIXQP       = 5,
	E_IPC_RCMODE_MJPEGFIXQP  = 6
}E_IPC_VIDEO_RCMODE;

typedef enum ipc_video_profile
{
	IPC_VIDEO_PROFILE_H264_MAIN	    = 0,
	IPC_VIDEO_PROFILE_H264_BASELINE = 1,  	
  	IPC_VIDEO_PROFILE_H264_HIGH     = 2,
  	IPC_VIDEO_PROFILE_H265_MAIN     = 3,
  	IPC_VIDEO_PROFILE_JPEG_MAIN     = 4,
}E_IPC_VIDEO_PROFILE;


typedef enum ipc_audio_enctype
{
	IPC_AUDIO_ENCTYPE_PCM	=	1,
	IPC_AUDIO_ENCTYPE_G711A	=	2,
	IPC_AUDIO_ENCTYPE_AACLC	=	3,
	IPC_AUDIO_ENCTYPE_G711U	=	4,
	IPC_AUDIO_ENCTYPE_G726  =   5,
	IPC_AUDIO_ENCTYPE_ADPCM =   6,
	IPC_AUDIO_ENCTYPE_OPUS	=	7,
}IPC_AUDIO_ENCTYPE;

typedef struct _ipc_video_config_s
{
	IPC_VIDEO_ENCTYPE	enc_type;
	E_IPC_VIDEO_RCMODE	rc_mode;
	int					bitrate;		//unit:kbps
	int					framerate;
	int					gop;
	int					width;
	int					height;
	E_IPC_VIDEO_PROFILE enc_profile;
}ipc_video_config;

typedef struct _ipc_audio_config_s
{
	IPC_AUDIO_ENCTYPE	enc_type;
	int					samplerate;
	int					bitwidth;
	int					pointNumPerFrame;		//-1: use SDK default setting; When SUB AI enabled, Sigmastar will use the bigger setting
}ipc_audio_config;

typedef enum
{
	E_HAL_VIDEO_ENC_CHN_MAIN = 0,
	E_HAL_VIDEO_ENC_CHN_SUB = 1,
	E_HAL_VIDEO_ENC_CHN_JPEG = 2,
	E_HAL_VIDEO_ENC_CHN_YUV = 3,	//for algorithm
	E_HAL_AUDIO_AI_CHN_MAIN = 4,
	E_HAL_AUDIO_AI_CHN_SUB = 5,
	E_HAL_AUDIO_AO_CHN = 6,
	E_HAL_VIDEO_ENC_CHN_TIMELAPSE = 7,
	E_HAL_AV_CHN_MAX,
}E_HAL_AV_CHNNEL;


typedef enum
{
	E_HAL_VIDEO_STREAM = 0,
	E_HAL_AUDIO_STREAM = 1,	
}E_HAL_STREAM_TYPE;

typedef enum
{
	E_HAL_STREAM_MAIN_CHANNEL = 0,
	E_HAL_STREAM_SUB_CHANNEL = 1,	
	E_HAL_STREAM_THIRD_CHANNEL = 2,
}E_HAL_STREAM_CHANNEL_TYPE;
typedef struct _ipc_av_config_s
{
	int bSupport;
	union
	{
		ipc_video_config video_conf;
		ipc_audio_config audio_conf;
		ipc_audio_config speak_conf;
	};

	/* 如果需要设置H264 自定义字段，在此回调函数    中填入buffer内容 */
	int (*Hal_Get_H264_SEI_Buffer_CallBack)(unsigned char *buffer, int buff_size);

	/* 从codec出来的音视频帧流，外部对接使用此回    调获取 */
	int (*Hal_Get_AV_Stream_From_Codec)(E_HAL_STREAM_TYPE stream_type, E_HAL_STREAM_CHANNEL_TYPE chn_type, Hal_frame_head_t *frame_head, unsigned char *frame_addr);

	int bIQServerStart;
}ipc_av_config;
#endif
