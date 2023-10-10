#ifndef HAL_STREAM_H
#define HAL_STREAM_H

#include <stdint.h>
typedef enum
{
	E_STREAM_I_FRAME_TYPE = 1,
	E_STREAM_P_FRAME_TYPE,
	E_STREAM_B_FRAME_TYPE,
	E_STREAM_A_FRAME_TYPE, 
}E_STREAM_FRAME_TYPE;

typedef struct Hal_sdk_frame_s
{
	unsigned int frame_size;
	unsigned int frame_no;
	unsigned int sec;
	unsigned int usec;
	int64_t pts;		//millisecond
	unsigned short frame_type;
	union {
		unsigned short frame_rate;
		unsigned short audio_sample_rate;
	};

	union {
		unsigned short width;
		unsigned short bits_per_sample;
	};

	union {
		unsigned short height;
		unsigned short audio_format;
	};	
    unsigned char   data[0];
} __attribute__ ((packed))Hal_sdk_frame_t;
typedef Hal_sdk_frame_t Hal_frame_head_t;

#endif /* HAL_STREAM_H */
