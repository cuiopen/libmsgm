#pragma once
#ifndef __MSG_CODEC_MAN_H__
#define __MSG_CODEC_MAN_H__


typedef enum _MSG_CMD_CODEC_MAN_TYPE
{
	MSG_CMD_DECODER_AUTO_LOOP = 0x101,
	MSG_CMD_DECODER_DEC_SRC = 0x102,
	MSG_CMD_OUTPUT_DIAGNOSIS = 0x103,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_CODEC_MAN = 0x104
}MSG_CMD_CODEC_MAN_TYPE;

/**************************************************************************
	1. MSG_CMD_DECODER_AUTO_LOOP -> 自动轮播
**************************************************************************/
typedef struct _DECODER_AUTO_LOOP
{
	int enable;  // 使能
	int interval;  // 轮播间隔
}DECODER_AUTO_LOOP;

/**************************************************************************
	2. MSG_CMD_DECODER_DEC_SRC -> 设置解码来源
**************************************************************************/
typedef enum _DECODER_PROTOCOL
{
	PROTOCOL_RTMP = 0x01,  // RTMP协议
	PROTOCOL_RTSP = 0x02,  // RTSP协议
	PROTOCOL_UNKNOWN = 0x99  // 未知
}DECODER_PROTOCOL;

typedef struct _DECODER_DEC_SRC
{
	int channel;  // 通道ID
	int enable;  // 使能
	char alais[128];  // 别名
	DECODER_PROTOCOL protocol;  // 协议
	int cache;  // 缓存
	char params[256];  // 参数
}DECODER_DEC_SRC;

/**************************************************************************
	3. MSG_CMD_OUTPUT_DIAGNOSIS -> 网络诊断
**************************************************************************/
typedef struct _OUTPUT_DIAGNOSIS
{
	int channel;  // 通道ID
	int enable;  // 使能
	int font_size;  // 字体大小
	int pos_x;  // 字体位置，x坐标
	int pos_y;  // 字体位置，y坐标
}OUTPUT_DIAGNOSIS;

/**************************************************************************
	4. MSG_CMD_SYSTEM_DEBUG_LEVEL_CODEC_MAN -> 调试等级
**************************************************************************/
typedef struct _SYSTEM_DEBUG_LEVEL_CODEC_MAN
{
	int debug_level;  // 调试等级
}SYSTEM_DEBUG_LEVEL_CODEC_MAN;

#endif


