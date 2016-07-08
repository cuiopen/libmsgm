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
	1. MSG_CMD_DECODER_AUTO_LOOP -> �Զ��ֲ�
**************************************************************************/
typedef struct _DECODER_AUTO_LOOP
{
	int enable;  // ʹ��
	int interval;  // �ֲ����
}DECODER_AUTO_LOOP;

/**************************************************************************
	2. MSG_CMD_DECODER_DEC_SRC -> ���ý�����Դ
**************************************************************************/
typedef enum _DECODER_PROTOCOL
{
	PROTOCOL_RTMP = 0x01,  // RTMPЭ��
	PROTOCOL_RTSP = 0x02,  // RTSPЭ��
	PROTOCOL_UNKNOWN = 0x99  // δ֪
}DECODER_PROTOCOL;

typedef struct _DECODER_DEC_SRC
{
	int channel;  // ͨ��ID
	int enable;  // ʹ��
	char alais[128];  // ����
	DECODER_PROTOCOL protocol;  // Э��
	int cache;  // ����
	char params[256];  // ����
}DECODER_DEC_SRC;

/**************************************************************************
	3. MSG_CMD_OUTPUT_DIAGNOSIS -> �������
**************************************************************************/
typedef struct _OUTPUT_DIAGNOSIS
{
	int channel;  // ͨ��ID
	int enable;  // ʹ��
	int font_size;  // �����С
	int pos_x;  // ����λ�ã�x����
	int pos_y;  // ����λ�ã�y����
}OUTPUT_DIAGNOSIS;

/**************************************************************************
	4. MSG_CMD_SYSTEM_DEBUG_LEVEL_CODEC_MAN -> ���Եȼ�
**************************************************************************/
typedef struct _SYSTEM_DEBUG_LEVEL_CODEC_MAN
{
	int debug_level;  // ���Եȼ�
}SYSTEM_DEBUG_LEVEL_CODEC_MAN;

#endif


