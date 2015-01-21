#ifndef _H_FFMPEGUTILS
#define _H_FFMPEGUTILS

#ifndef INT64_C													//应对UINT64_C未定义
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
#include "utils.h"

#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
#endif

#ifndef INT64_C													//应对UINT64_C未定义
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#ifdef __cplusplus  
extern "C"   
{  
	#include <libavutil/file.h>
	#include <libavutil/dict.h>
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libavformat/avio.h>
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

int encoding_decoding(const char* filename, const char* output_type = NULL);

int read_packet(void *opaque, uint8_t *buf, int buf_size);