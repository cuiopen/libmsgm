#ifndef _K_MSGM_H_
#define _K_MSGM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OUT  // 输出参数
#define IN   // 输入参数
#define BYTE_1024 				1024		// 最大支持32个模块

#define MESSAGE_CMD_SETCONFIG 1  // setConfig
#define MESSAGE_CMD_GETCONFIG 2  // getConfig
#define MESSAGE_CMD_RPCCALL   3  // rpcCall

// 增加程序间心跳的消息ID
#define MESSAGE_CMD_KEEP_ALIVE		0x10000
#define MESSAGE_CMD_KEEP_ALIVE_ACK	0x10001

// 增加程序退出消息
#define MESSAGE_CMD_APP_EXIT		0x20000
#define MESSAGE_CMD_APP_RESTART		0x20001

#define MESSAGE_TYPE_ASK 0x01
#define MESSAGE_TYPE_ANS 0x02

#define MESSAGE_PRM_CUT_MARK  '='  // 消息体中的params分隔符，字符
#define MESSAGE_PRM_CUT_MASK_STR "="  // 消息体中的params分隔符,字符串

#define MODULE_KEY_MAX    32  // 模块的KEY值小于1024

// ASK类型回调
typedef int (*MSGM_ASK_HANDLE)(void* handle, IN int cmd, IN int params_len, IN char* params, OUT int* result_len, OUT char* result);

// ANS类型回调
typedef int (*MSGM_ANS_HANDLE)(void* handle, IN int cmd, IN int result_len, IN char* result);

// 模块的编号统一由etah_modules.h提供
#if 0
enum MSGM_MODULE_ID {
	MSGM_SYS_MON_ID = 0x01,
	MSGM_HTTP_SVR_ID = 0x02,
	MSGM_CFG_MAN_ID = 0x03,
	MSGM_CODEC_CORE_ID = 0x04,
	MSGM_SYS_SVR_ID = 0x05,
	MSGM_CODEC_MAN_ID = 0x06
};
#endif

#define MSGM_BODY_SIZE  (sizeof(MSGM_BODY))

typedef struct _MSGM_CMD
{
    int cmd;  // 对应msgm_body中的cmd
	int ret;  // 返回的结果值
    int len;  // data的有效长度
    char params[BYTE_1024];  // 对应msgm_body中的data
}MSGM_CMD;

typedef struct _MSGM_HANDLE{
	int key;  // 模块ID
	int msgmid;  // 消息队列ID
	MSGM_ASK_HANDLE m_ask_handle;  // ASK消息回调 
	void *m_ask_first_params;  // ASK回调的首个参数
	MSGM_ANS_HANDLE m_ans_handle;  // 暂时无用
	int key_to_msgmid[MODULE_KEY_MAX];  // key <-> msgmid 映射表(修改为最大支持32个模块)
	int seq;  // ASK消息的标号
}MSGM_HANDLE;

/*********************************************
    1. 创建key为标识的消息队列
*********************************************/
int msgm_create(int key);

/*********************************************
    1. 打开key为标识的消息队列
*********************************************/
MSGM_HANDLE* msgm_open(int key);

/*********************************************
    1. 注册ASK类型的回调函数
    2. 创建接收消息的线程
*********************************************/
int msgm_ask_handle_register(MSGM_HANDLE* msg_handle, MSGM_ASK_HANDLE ask_handle, void* handle);

/*********************************************
    1. 同步超时的模式发送ASK请求
    2. timeout -> ms  key -> ASK目的地的消息队列标识
*********************************************/
int msgm_send_ask_timeout(MSGM_HANDLE* msg_handle, MSGM_CMD *msg, MSGM_CMD *msgm_result, int timeout, int key);

/*********************************************
    1. 异步发送ASK请求，即发送ASK消息后返回
    2. key -> ASK目的地的消息队列标识
*********************************************/
int msgm_send_ask_async(MSGM_HANDLE* msg_handle, MSGM_CMD *msg,int key);

/*********************************************
    1. 关闭消息队列
*********************************************/
void msgm_close(MSGM_HANDLE* msg_handle);

/*********************************************
    1. 删除消息队列
*********************************************/
void msgm_delete(MSGM_HANDLE* msg_handle);

/*********************************************
	1. 通过key来获取msgmid
*********************************************/
int get_msgmid_from_key(MSGM_HANDLE* msg_handle, int key);

void dump_MSGM_CMD(MSGM_CMD *cmd, int size);

#ifdef __cplusplus
}
#endif

#endif
