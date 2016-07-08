#ifndef _K_COMMON_H_
#define _K_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

#include "debug.h"

#define FTOK_FILE_NAME    "/tmp/libmsgm"  // ftok指定的文件名

#define MESSAGE_TYPE_ASK 0x01
#define MESSAGE_TYPE_ANS 0x02

typedef struct _MSGM_BODY{
    int type;  // MESSAGE_TYPE_ASK 或者 MESSAGE_TYPE_ANS
    int cmd;   // MESSAGE_TYPE_ASK时有效，MESSAGE_CMD_SETCONFIG、MESSAGE_CMD_GETCONFIG或者MESSAGE_CMD_RPCCALL任一
    int ret;   // MESSAGE_TYPE_ANS时有效，表示调用的返回值
    int from;  // 记录发送消息者的消息队列的模块ID
    int to;    // 记录接收消息者的消息队列的模块ID
    int seq;   // 消息标识，用于ANS和ASK的匹配
    int size;  // data的有效长度
    char data[BYTE_1024];  // MESSAGE_TYPE_ASK时作为调用参数、MESSAGE_TYPE_ANS时作为返回结果
    int  ext_size;  // 扩展长度
    char* ext_data; // 扩展数据
}MSGM_BODY;
    
#define MSGM_BODY_SIZE  (sizeof(MSGM_BODY))

#define COUNT_1024    1024

/*********************************************
    1. 此函数为接收消息的线程，传入的参数的类型为MSGM_HANDLE
    2. 这个线程只接受MESSAGE_TYPE_ASK类型的消息
*********************************************/
void *thread_msgm_ask_handle(void *void_msg_handle);

#ifdef __cplusplus
}
#endif

#endif
