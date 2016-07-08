#pragma once
#ifndef __MSG_SYS_SVR_H__
#define __MSG_SYS_SVR_H__


typedef enum _MSG_CMD_SYS_SVR_TYPE
{
	MSG_CMD_NETWORK_INTERFACE = 0x01,
	MSG_CMD_NETWORK_DNS = 0x02,
	MSG_CMD_NETWORK_GATEWAY = 0x03,
	MSG_CMD_SYSTEM_NTP = 0x04,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_SYS_SVR = 0x05
}MSG_CMD_SYS_SVR_TYPE;

/**************************************************************************
	1. MSG_CMD_NETWORK_INTERFACE -> 设置网卡参数
**************************************************************************/
// IP地址
typedef struct _NETWORK_ADDRESS
{
	int enable;
	char ip_addr[20];
	char net_mask[20];
}NETWORK_ADDRESS;

// 网卡接口
typedef struct _NETWORK_INTERFACE
{
	int id;  // 网卡ID
	int enable;  // 使能
	char mac[18];  // MAC地址 20:15:12:31:11:03
	int dhcp;  // dhcp使能
	NETWORK_ADDRESS addr[2]; // IP地址
}NETWORK_INTERFACE;

/**************************************************************************
	2. MSG_CMD_NETWORK_DNS -> 设置DNS
**************************************************************************/
typedef struct _NETWORK_DNS
{
	char preferred[20];  // 首选DNS
	char alternate[20];  // 备用DNS
}NETWORK_DNS;

/**************************************************************************
	3. MSG_CMD_NETWORK_GATEWAY -> 设置网关
**************************************************************************/
typedef struct _NETWORK_GATEWAY
{
	int id;  // ������
	char gateway[20];  // ����
}NETWORK_GATEWAY;

/**************************************************************************
	4. MSG_CMD_SYSTEM_NTP -> 设置NTP服务
**************************************************************************/
typedef struct _SYSTEM_NTP
{
	int enable;  // 使能
	char address[128];  // NTP服务器地址
	char time[128];  // enable为0时有效，2016 01 01 10 30 00 
}SYSTEM_NTP;

/**************************************************************************
	5. MSG_CMD_SYSTEM_DEBUG_LEVEL_SYS_SVR -> 设置调试等级
**************************************************************************/
typedef struct _SYSTEM_DEBUG_LEVEL_SYS_SVR
{
	int debug_level;  // 调试等级
}SYSTEM_DEBUG_LEVEL_SYS_SVR;

#endif
