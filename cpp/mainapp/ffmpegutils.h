#ifndef _H_FFMPEGUTILS
#define _H_FFMPEGUTILS

#ifndef INT64_C													//应对UINT64_C未定义
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
#include "Windows.h"
#ifdef __cplusplus  
extern "C"   
{  
	#include <libavcodec/avcodec.h>
	#include <libavutil/opt.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/channel_layout.h>
	#include <libavutil/common.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/samplefmt.h>
}  
#endif 

struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};
#endif