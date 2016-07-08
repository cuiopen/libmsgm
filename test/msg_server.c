#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COMMON_KEY_0    0x03
#define COMMON_KEY_1    0x04
#define COMMON_KEY_2    0x05
#define COMMON_KEY_3    0x06

#include "etah_msgq.h"

int deal_to_ask(void* handle, int cmd, int params_len, char* params, int *result_len, char* result)
{
	if ( cmd == MESSAGE_CMD_SETCONFIG)
	{
		printf("cmd -> %d params_len -> %d \n", cmd, params_len);
		*result_len = 9;
		memcpy(result, "123456789", *result_len);
	}
	else if ( cmd == MESSAGE_CMD_GETCONFIG )
	{
		printf("cmd -> %d params_len -> %d \n", cmd, params_len);
		*result_len = 9;
		memcpy(result, "abcdefghi", *result_len);
	}
	else if ( cmd == MESSAGE_CMD_RPCCALL )
	{
		printf("cmd -> %d params_len -> %d \n", cmd, params_len);
		*result_len = 9;
		memcpy(result, "ABCDEFGHI", *result_len);
	}
	
	return 0;
}

int main()
{
	MSGM_HANDLE *msg_handle = NULL;
	
	msg_handle = msgm_open(COMMON_KEY_0);
	if (msg_handle == NULL)
	{
		printf("msg_handle is null!\n");
		return 1;
	}
	
	msgm_ask_handle_register(msg_handle, deal_to_ask, NULL);
	
	while(1)
	{
		usleep(1000000);
	}
}