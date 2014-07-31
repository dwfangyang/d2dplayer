#ifndef _H_FFMPEGUTILS
#define _H_FFMPEGUTILS

#ifndef INT64_C													//应对UINT64_C未定义
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
#ifdef __cplusplus  
extern "C"   
{  
#include <libavcodec/avcodec.h>
}  
#endif 

struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};
#endif