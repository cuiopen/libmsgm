#ifndef _K_MSGM_H_
#define _K_MSGM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OUT  // �������
#define IN   // �������
#define BYTE_1024 				1024		// ���֧��32��ģ��

#define MESSAGE_CMD_SETCONFIG 1  // setConfig
#define MESSAGE_CMD_GETCONFIG 2  // getConfig
#define MESSAGE_CMD_RPCCALL   3  // rpcCall

// ���ӳ������������ϢID
#define MESSAGE_CMD_KEEP_ALIVE		0x10000
#define MESSAGE_CMD_KEEP_ALIVE_ACK	0x10001

// ���ӳ����˳���Ϣ
#define MESSAGE_CMD_APP_EXIT		0x20000
#define MESSAGE_CMD_APP_RESTART		0x20001

#define MESSAGE_TYPE_ASK 0x01
#define MESSAGE_TYPE_ANS 0x02

#define MESSAGE_PRM_CUT_MARK  '='  // ��Ϣ���е�params�ָ������ַ�
#define MESSAGE_PRM_CUT_MASK_STR "="  // ��Ϣ���е�params�ָ���,�ַ���

#define MODULE_KEY_MAX    32  // ģ���KEYֵС��1024

// ASK���ͻص�
typedef int (*MSGM_ASK_HANDLE)(void* handle, IN int cmd, IN int params_len, IN char* params, OUT int* result_len, OUT char* result);

// ANS���ͻص�
typedef int (*MSGM_ANS_HANDLE)(void* handle, IN int cmd, IN int result_len, IN char* result);

// ģ��ı��ͳһ��etah_modules.h�ṩ
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
    int cmd;  // ��Ӧmsgm_body�е�cmd
	int ret;  // ���صĽ��ֵ
    int len;  // data����Ч����
    char params[BYTE_1024];  // ��Ӧmsgm_body�е�data
}MSGM_CMD;

typedef struct _MSGM_HANDLE{
	int key;  // ģ��ID
	int msgmid;  // ��Ϣ����ID
	MSGM_ASK_HANDLE m_ask_handle;  // ASK��Ϣ�ص� 
	void *m_ask_first_params;  // ASK�ص����׸�����
	MSGM_ANS_HANDLE m_ans_handle;  // ��ʱ����
	int key_to_msgmid[MODULE_KEY_MAX];  // key <-> msgmid ӳ���(�޸�Ϊ���֧��32��ģ��)
	int seq;  // ASK��Ϣ�ı��
}MSGM_HANDLE;

/*********************************************
    1. ����keyΪ��ʶ����Ϣ����
*********************************************/
int msgm_create(int key);

/*********************************************
    1. ��keyΪ��ʶ����Ϣ����
*********************************************/
MSGM_HANDLE* msgm_open(int key);

/*********************************************
    1. ע��ASK���͵Ļص�����
    2. ����������Ϣ���߳�
*********************************************/
int msgm_ask_handle_register(MSGM_HANDLE* msg_handle, MSGM_ASK_HANDLE ask_handle, void* handle);

/*********************************************
    1. ͬ����ʱ��ģʽ����ASK����
    2. timeout -> ms  key -> ASKĿ�ĵص���Ϣ���б�ʶ
*********************************************/
int msgm_send_ask_timeout(MSGM_HANDLE* msg_handle, MSGM_CMD *msg, MSGM_CMD *msgm_result, int timeout, int key);

/*********************************************
    1. �첽����ASK���󣬼�����ASK��Ϣ�󷵻�
    2. key -> ASKĿ�ĵص���Ϣ���б�ʶ
*********************************************/
int msgm_send_ask_async(MSGM_HANDLE* msg_handle, MSGM_CMD *msg,int key);

/*********************************************
    1. �ر���Ϣ����
*********************************************/
void msgm_close(MSGM_HANDLE* msg_handle);

/*********************************************
    1. ɾ����Ϣ����
*********************************************/
void msgm_delete(MSGM_HANDLE* msg_handle);

/*********************************************
	1. ͨ��key����ȡmsgmid
*********************************************/
int get_msgmid_from_key(MSGM_HANDLE* msg_handle, int key);

void dump_MSGM_CMD(MSGM_CMD *cmd, int size);

#ifdef __cplusplus
}
#endif

#endif
