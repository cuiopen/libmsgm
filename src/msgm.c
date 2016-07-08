#include <pthread.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "etah_msgq.h"
#include "debug.h"
#include "common.h"

/*********************************************
    1. 创建key为标识的消息队列
*********************************************/
int msgm_create(int key)
{
    int ret = -1;
    key_t msgm_key_t;
    // 文件不存在
    if ( access(FTOK_FILE_NAME, F_OK) == -1 )
    {
        int fd;
        fd = open(FTOK_FILE_NAME, O_RDWR|O_CREAT|0666);
        if ( fd == -1 )
        {
            DEBUG_ERROR("failed to create %s", FTOK_FILE_NAME);
            return -1;
        }
        else
        {
            close(fd);
        }
    }

    // 生成key_t
    msgm_key_t = ftok(FTOK_FILE_NAME, key);
    if ( msgm_key_t == -1 )
    {
        DEBUG_ERROR("failed to ftok %s.%d", FTOK_FILE_NAME, key);
        return -1;
    }

	// ??????,??????
    DEBUG_INFO("msgm_key_t -> %x", msgm_key_t);

	ret = msgget(msgm_key_t, IPC_EXCL);

    if ( ret < 0 )
    {
        // ??????
    	ret = msgget(msgm_key_t, IPC_CREAT);
    }

    if ( ret < 0 )
    {
        DEBUG_ERROR("msgget -> %x failed", msgm_key_t);
        return -1;
    }
    
    return ret;
}

/*********************************************
    1. 打开key为标识的消息队列
*********************************************/
MSGM_HANDLE* msgm_open(int key)
{
	int ret = 0;
	key_t msgm_key_t;
	MSGM_HANDLE* msg_handle = NULL;
	
    msgm_key_t = ftok(FTOK_FILE_NAME, key);
    if ( msgm_key_t == -1 )
    {
        DEBUG_ERROR("failed to ftok %s.%d", FTOK_FILE_NAME, key);
        return NULL;
    }

    DEBUG_INFO("msgm_key_t -> %x", msgm_key_t);
    // 打开消息队列
    ret = msgget(msgm_key_t, IPC_EXCL);

    if ( ret < 0 )
    {
        DEBUG_ERROR("msgget -> %x failed", msgm_key_t);
        return NULL;
    }
	
	msg_handle = (MSGM_HANDLE*)malloc(sizeof(MSGM_HANDLE));
	memset(msg_handle, 0, sizeof(MSGM_HANDLE));
	memset(msg_handle->key_to_msgmid, 0xff, MODULE_KEY_MAX*sizeof(int));
	msg_handle->key = key;
	msg_handle->msgmid = ret;
	msg_handle->m_ans_handle = NULL;
	msg_handle->m_ask_first_params = NULL;
	msg_handle->m_ask_handle = NULL;
	msg_handle->seq = 0;
    
    return msg_handle;
}

/*********************************************
    1. 此函数为接收消息的线程，传入的参数的类型为MSGM_HANDLE
    2. 这个线程只接受MESSAGE_TYPE_ASK类型的消息
*********************************************/
#define ASK_HANDLE_IS_NULL    "ASK_HANDLE IS NULL"
#define SIZE_OF_ASK_HANDLE_IS_NULL  (sizeof(ASK_HANDLE_IS_NULL))
void *thread_msgm_ask_handle(void *void_msg_handle)
{
	MSGM_HANDLE *msg_handle = NULL;
	if (void_msg_handle == NULL)
	{
		DEBUG_ERROR("void_msg_handle is NULL");
		return (void*)-1;
	}
	
	msg_handle = (MSGM_HANDLE*)void_msg_handle;

	pthread_detach(pthread_self());
	
	while(1)
	{
		MSGM_BODY msg;
		// 阻塞等待 接收MESSAGE_TYPE_ASK类型消息
		if ( msgrcv(msg_handle->msgmid, (void*)(&msg), MSGM_BODY_SIZE, MESSAGE_TYPE_ASK, 0) == MSGM_BODY_SIZE )
		{
			char result[BYTE_1024] = "";
			int result_len = BYTE_1024;
			int ret = -1;
			MSGM_BODY msg_ans;
			
			// 回调已经注册
			if(msg_handle->m_ask_handle != NULL)
			{
				ret = msg_handle->m_ask_handle(msg_handle->m_ask_first_params, msg.cmd, msg.size, msg.data, &result_len, result);
			}
			// 回调还未注册
			else
			{
				memcpy(result, ASK_HANDLE_IS_NULL, SIZE_OF_ASK_HANDLE_IS_NULL);
				result_len = SIZE_OF_ASK_HANDLE_IS_NULL;
				ret = -1;
			}
			
			// 回复ANS包
			int msgmid_to = 0;
			memset(&msg_ans, 0, sizeof(MSGM_BODY));
			msg_ans.type = MESSAGE_TYPE_ANS;
			msg_ans.cmd = msg.cmd;
			msg_ans.ret = ret;
			msg_ans.from = msg_handle->key;
			msg_ans.to = msg.from;
			msg_ans.seq = msg.seq;
			msg_ans.size = result_len;
			memcpy(msg_ans.data, result, result_len);
			
			// 在key <-> msgmid 映射表里面通过key找msgmid
			msgmid_to = get_msgmid_from_key(msg_handle, msg.from);
			if (msgmid_to < 0)
			{
				DEBUG_ERROR("get_msgmid_from_key failed");
				continue;
			}
			
			ret = msgsnd(msgmid_to, &msg_ans, MSGM_BODY_SIZE, IPC_NOWAIT);
			if(ret == -1)
			{
				DEBUG_ERROR("msgsnd failed!");
				continue;
			}
		}
			
	}
}

/*********************************************
    1. 注册ASK类型的回调函数
    2. 创建接收消息的线程
*********************************************/
int msgm_ask_handle_register(MSGM_HANDLE* msg_handle, MSGM_ASK_HANDLE ask_handle, void* handle)
{
	pthread_t server_tid;
	
	if (msg_handle == NULL)
	{
		DEBUG_ERROR("msg_handle is NULL");
		return -1;
	}
	
	msg_handle->m_ask_handle = ask_handle;
	msg_handle->m_ask_first_params = handle;
	
	// TODO 创建线程接受ASK类型线程
	if ( pthread_create(&server_tid, NULL, thread_msgm_ask_handle, (void*)(msg_handle)) != 0 )
	{
		DEBUG_ERROR("pthread_create failed");
		return -1;
	}
	
	return 0;
}

/*********************************************
    1. 同步超时的模式发送ASK请求
    2. timeout -> ms  key -> ASK目的地的消息队列标识
*********************************************/
#define SLEEP_50MS  usleep(50000)
int msgm_send_ask_timeout(MSGM_HANDLE* msg_handle, MSGM_CMD *msg, MSGM_CMD *msgm_result, int timeout, int key)
{
	int ret = 0;
	MSGM_BODY msg_ans;
	
	if (msg_handle == NULL || msgm_result == NULL || msg == NULL)
	{
		DEBUG_ERROR("inputs are illegal");
		return -1;
	}
	
	if ( msgm_send_ask_async(msg_handle, msg, key) < 0 )
	{
		DEBUG_ERROR("msgm_send_ask_async failed, key = %d", key);
		return -1;
	}
	
	// sleep超时等待消息，每次sleep 50ms
	struct	timeval start;
	struct	timeval end;
	gettimeofday(&start,NULL);
	
	while(1)
	{
		if( msgrcv(msg_handle->msgmid, (void*)(&msg_ans), MSGM_BODY_SIZE, MESSAGE_TYPE_ANS, IPC_NOWAIT) == MSGM_BODY_SIZE)
		{
			// ANS不匹配
			if (msg_ans.cmd != msg->cmd ||
				msg_ans.seq != msg_handle->seq)
			{
				continue;
			}
			
			if (msg_ans.size > BYTE_1024 || msg_ans.size < 0)
			{
				msgm_result->ret = -1;
			}
			else
			{
				msgm_result->ret = msg_ans.ret;
			}
			msgm_result->cmd = msg_ans.cmd;
			msgm_result->len = msg_ans.size;
			memcpy(msgm_result->params, msg_ans.data, msg_ans.size);
			break;
		}
		else
		{
			SLEEP_50MS;
		}
		
		gettimeofday(&end,NULL);
		
		unsigned  long diff = 1000 * (end.tv_sec-start.tv_sec)+ (end.tv_usec-start.tv_usec) / 1000;
		
		if( diff > timeout )
		{		
			DEBUG_ERROR("TIMEOUT diff -> %ul", diff);
			return -1;
		}
	}
	
	return 0;
}

int msgm_send_ask_async(MSGM_HANDLE* msg_handle, MSGM_CMD *msg,int key)
{
	int ret = -1;
	MSGM_BODY msg_ask;
	int msgmid_to = -1;
	
	if (msg_handle == NULL || msg == NULL)
	{
		DEBUG_ERROR("inputs are illegal");
		return -1;
	}
	
	if ( msg->len >= BYTE_1024 )
	{
		DEBUG_ERROR("msg->len: %d", msg->len);
		return -1;
	}
	
	msgmid_to = get_msgmid_from_key(msg_handle, key);
	
	if (msgmid_to < 0)
	{
		DEBUG_ERROR("get_msgmid_from_key failed, key = %d", key);
		return -1;
	}
	
	memset(&msg_ask, 0, MSGM_BODY_SIZE);
	msg_ask.type = MESSAGE_TYPE_ASK;
	msg_ask.cmd = msg->cmd;
	msg_ask.from = msg_handle->key;
	msg_ask.to = key;
	msg_ask.seq = ++(msg_handle->seq);
	msg_ask.size = msg->len;
	memcpy(msg_ask.data, msg->params, msg->len);
	
	ret = msgsnd(msgmid_to, &msg_ask, MSGM_BODY_SIZE, IPC_NOWAIT);
	if (ret < 0)
	{
		DEBUG_ERROR("msgsnd failed");
		return -1;
	}
	
	return 0;
}

/*********************************************
    1. 关闭消息队列
    2. 删除环形队列
*********************************************/
void msgm_close(MSGM_HANDLE* msg_handle)
{
	if (msg_handle == NULL)
	{
		DEBUG_ERROR("msg_handle is NULL");
		return ;
	}
	
	free(msg_handle);
}

/*********************************************
    1. 删除消息队列
*********************************************/
void msgm_delete(MSGM_HANDLE* msg_handle)
{
	if (msg_handle == NULL)
	{
		DEBUG_ERROR("msg_handle is NULL");
		return ;
	}
	
	msgctl(msg_handle->msgmid, IPC_RMID, NULL);
}

int get_msgmid_from_key(MSGM_HANDLE* msg_handle, int key)
{
	int msgmid = -1;
	if (msg_handle == NULL || key >= MODULE_KEY_MAX)
	{
		DEBUG_ERROR("input are illegal");
		return -1;
	}
	
	if( msg_handle->key_to_msgmid[key] <= 0)
	{
		key_t msgm_key_t = ftok(FTOK_FILE_NAME, key);
		if ( msgm_key_t == -1 )
		{
			DEBUG_ERROR("failed to ftok %s.%d", FTOK_FILE_NAME, key);
			return -1;
		}

		// 打开消息队列
		msgmid = msgget(msgm_key_t, IPC_EXCL);
		if ( msgmid < 0 )
		{
			DEBUG_ERROR("msgget -> %x failed", msgm_key_t);
			return -1;
		}
		
		DEBUG_INFO("1. msgm_key_t -> %x", msgmid);
		
		msg_handle->key_to_msgmid[key] = msgmid;
	}
	else
	{
		msgmid = msg_handle->key_to_msgmid[key];
	}
	
	return msgmid;
}

void dump_MSGM_CMD(MSGM_CMD *cmd, int size)
{
	if (cmd == NULL || size > BYTE_1024)
	{
		return;
	}
	
	DEBUG_INFO("---->START<----");
	DEBUG_INFO("cmd -> %d", cmd->cmd);
	DEBUG_INFO("cmd -> %d", cmd->ret);
	DEBUG_INFO("cmd -> %d", cmd->len);
	DEBUG_INFO("params -> ");
	dprintfbin(cmd->params, size);
	DEBUG_INFO("----->END<-----");
}