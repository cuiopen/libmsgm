#ifndef _K_DEBUG_H_
#define _K_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define __FILE_NAME__(x) strrchr(x,'/')?(strrchr(x,'/')+1):x

#define __DEBUG__

#ifdef __DEBUG__
#define DEBUG_ERROR(format,...) printf("[libmsgm: ERROR] File: %s, Line: %05d: "format"\n", __FILE_NAME__(__FILE__), __LINE__, ##__VA_ARGS__)
#define DEBUG_WARN(format,...)  printf("[libmsgm: WARN ] File: %s, Line: %05d: "format"\n", __FILE_NAME__(__FILE__), __LINE__, ##__VA_ARGS__)
#define DEBUG_INFO(format,...)  printf("[libmsgm: INFO ] File: %s, Line: %05d: "format"\n", __FILE_NAME__(__FILE__), __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_ERROR(format,...) 
#define DEBUG_WARN(format,...) 
#define DEBUG_INFO(format,...) 
#endif


#define dprintfbin(buf, size) 					\
	do {											\
		int i; 										\
		for (i = 0; i < size - 1; i++){ 				\
			if (0 == i % 16){ 						\
				if (0 != i)							\
					printf("\n");					\
				printf("0x%04x: ", i); 			\
			}										\
			printf("%02x ", ((char*)buf)[i]);		\
		}											\
		printf("%02x\n", ((char*)buf)[i]); 			\
	} while(0)


#ifdef __cplusplus
}
#endif

#endif
