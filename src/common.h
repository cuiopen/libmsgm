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

#define FTOK_FILE_NAME    "/tmp/libmsgm"  // ftokָ�����ļ���

#define MESSAGE_TYPE_ASK 0x01
#define MESSAGE_TYPE_ANS 0x02

typedef struct _MSGM_BODY{
    int type;  // MESSAGE_TYPE_ASK ���� MESSAGE_TYPE_ANS
    int cmd;   // MESSAGE_TYPE_ASKʱ��Ч��MESSAGE_CMD_SETCONFIG��MESSAGE_CMD_GETCONFIG����MESSAGE_CMD_RPCCALL��һ
    int ret;   // MESSAGE_TYPE_ANSʱ��Ч����ʾ���õķ���ֵ
    int from;  // ��¼������Ϣ�ߵ���Ϣ���е�ģ��ID
    int to;    // ��¼������Ϣ�ߵ���Ϣ���е�ģ��ID
    int seq;   // ��Ϣ��ʶ������ANS��ASK��ƥ��
    int size;  // data����Ч����
    char data[BYTE_1024];  // MESSAGE_TYPE_ASKʱ��Ϊ���ò�����MESSAGE_TYPE_ANSʱ��Ϊ���ؽ��
    int  ext_size;  // ��չ����
    char* ext_data; // ��չ����
}MSGM_BODY;
    
#define MSGM_BODY_SIZE  (sizeof(MSGM_BODY))

#define COUNT_1024    1024

/*********************************************
    1. �˺���Ϊ������Ϣ���̣߳�����Ĳ���������ΪMSGM_HANDLE
    2. ����߳�ֻ����MESSAGE_TYPE_ASK���͵���Ϣ
*********************************************/
void *thread_msgm_ask_handle(void *void_msg_handle);

#ifdef __cplusplus
}
#endif

#endif
