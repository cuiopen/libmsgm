#ifndef _INC_ETAH_MODULES_H_
#define _INC_ETAH_MODULES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VARRUN 		"/var/run"				// ����PID�ļ���λ��

#define ETAH_MODULE_NAME_LENGTH	32			// ģ��������󳤶�

#define MAKE_LONG(A,B,C,D)		(((A)<<24)|((B)<<16)|((C)<<8)|(D))

// ����״̬���
typedef enum 
{         
	ETAH_MODULE_DEAD=0,		// δ����״̬
	
	ETAH_MODULE_RUN,    	// ��������״̬
	
} ETAH_MODULES_STATUS;

// �����Լ�ģ��ı��
typedef enum 
{         
	ETAH_MODULE_RES_INIT=0,		// ��Դ��ʼ������(���ڵ�һ�����̶����Ϊ0)
	
	ETAH_MODULE_CFG_MAN,    	// ���ù������

	ETAH_MODULE_CODEC_CORE,		// �����Լ���Ƶ�������
	
	ETAH_MODULE_CCODE_MAN,		// ����Э�鴦�����
	
	ETAH_MODULE_HTTP_SVR,		// HTTP�ӿڳ���
	
	ETAH_MODULE_CODEC_MMI,		// �˻������������	
	
	ETAH_MODULE_SYS_SVR,		// ϵͳ�������
	
	ETAH_MODULE_SYS_MON,		// ϵͳ��س���	(���һ�����̣�ǰ��Ľ��̺�����)

#define ETAH_MODULE_MAX		8	// ��������Ŀ�����ӽ���ʱ��Ҫͬ���޸ĸ�ֵ	

	ETAH_MODULE_LIB_MSGM,		// ��Ϣ���д����

	ETAH_MODULE_LIB_LOG,		// ��־��

	ETAH_MODULE_LIB_SHM  		// �����ڴ��	
	
} ETAH_MODULES_ID;


#ifdef __cplusplus
}
#endif

#endif
