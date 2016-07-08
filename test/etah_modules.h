#ifndef _INC_ETAH_MODULES_H_
#define _INC_ETAH_MODULES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VARRUN 		"/var/run"				// 进程PID文件的位置

#define ETAH_MODULE_NAME_LENGTH	32			// 模块名的最大长度

#define MAKE_LONG(A,B,C,D)		(((A)<<24)|((B)<<16)|((C)<<8)|(D))

// 程序状态编号
typedef enum 
{         
	ETAH_MODULE_DEAD=0,		// 未运行状态
	
	ETAH_MODULE_RUN,    	// 正在运行状态
	
} ETAH_MODULES_STATUS;

// 程序以及模块的编号
typedef enum 
{         
	ETAH_MODULE_RES_INIT=0,		// 资源初始化程序(放在第一个，固定编号为0)
	
	ETAH_MODULE_CFG_MAN,    	// 配置管理程序

	ETAH_MODULE_CODEC_CORE,		// 解码以及视频输出程序
	
	ETAH_MODULE_CCODE_MAN,		// 解码协议处理程序
	
	ETAH_MODULE_HTTP_SVR,		// HTTP接口程序
	
	ETAH_MODULE_CODEC_MMI,		// 人机交互界面程序	
	
	ETAH_MODULE_SYS_SVR,		// 系统管理程序
	
	ETAH_MODULE_SYS_MON,		// 系统监控程序	(最后一个进程，前面的进程号连续)

#define ETAH_MODULE_MAX		8	// 最大进程数目，增加进程时需要同步修改改值	

	ETAH_MODULE_LIB_MSGM,		// 消息队列处理库

	ETAH_MODULE_LIB_LOG,		// 日志库

	ETAH_MODULE_LIB_SHM  		// 共享内存库	
	
} ETAH_MODULES_ID;


#ifdef __cplusplus
}
#endif

#endif
