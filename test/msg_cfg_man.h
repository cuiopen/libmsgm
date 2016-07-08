#pragma once
#ifndef __MSG_CFG_MAN_H__
#define __MSG_CFG_MAN_H__


typedef enum _MSG_CMD_CFG_MAN_TYPE
{
	//sys_svr GET -> 0x00
	MSG_CMD_NETWORK_INTERFACE_GET = 0x01,
	MSG_CMD_NETWORK_DNS_GET = 0x02,
	MSG_CMD_NETWORK_GATEWAY_GET = 0x03,
	MSG_CMD_SYSTEM_NTP_GET = 0x04,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_SYS_SVR_GET = 0x05,
	// sys_svr SET -> 0x80
	MSG_CMD_NETWORK_INTERFACE_SET = 0x81,
	MSG_CMD_NETWORK_DNS_SET = 0x82,
	MSG_CMD_NETWORK_GATEWAY_SET = 0x83,
	MSG_CMD_SYSTEM_NTP_SET = 0x84, 
	MSG_CMD_SYSTEM_DEBUG_LEVEL_SYS_SVR_SET = 0x85,
	// codec_man GET -> 0x100
	MSG_CMD_DECODER_AUTO_LOOP_GET = 0x101,
	MSG_CMD_DECODER_DEC_SRC_GET = 0x102,
	MSG_CMD_OUTPUT_DIAGNOSIS_GET = 0x103,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_CODEC_MAN_GET = 0x104,
	// codec_man SET -> 0x180
	MSG_CMD_DECODER_AUTO_LOOP_SET = 0x181,
	MSG_CMD_DECODER_DEC_SRC_SET = 0x182,
	MSG_CMD_OUTPUT_DIAGNOSIS_SET = 0x183,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_CODEC_MAN_SET = 0x184,
	// codec_core GET -> 0x200
	MSG_CMD_AVSERVER_OUTPUT_RES_GET = 0x201,
	MSG_CMD_AVSERVER_OUTPUT_MS_INFO_GET = 0x202,
	// codec_core SET -> 0x280
	MSG_CMD_AVSERVER_OUTPUT_RES_SET = 0x281,
	MSG_CMD_AVSERVER_OUTPUT_MS_INFO_SET = 0x282,
	// sys_mon -> 0x300
	// cfg_man GET -> 0x400
	MSG_CMD_DECODER_LIST_NUMBER_GET = 0x401,
	MSG_CMD_DEVICE_SYSTEM_INFO_GET = 0x402,
	MSG_CMD_MOSAIC_STYLE_NUMBER_GET = 0x403,
	MSG_CMD_MOSAIC_STYLE_GET = 0x404,
	MSG_CMD_SYSTEM_PKG_VERSION_GET = 0x405,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_CFG_MAN_GET = 0x406,
	MSG_CMD_SYSTEM_DEC_MODE_GET = 0x407,
	MSG_CMD_SYSTEM_COMP_MODE_GET = 0x408,
	// cfg_man SET -> 0x480
	MSG_CMD_DECODER_LIST_NUMBER_SET = 0x481,
	MSG_CMD_DEVICE_SYSTEM_INFO_SET = 0x482,
	MSG_CMD_MOSAIC_STYLE_NUMBER_SET = 0x483,
	MSG_CMD_MOSAIC_STYLE_SET = 0x484,
	MSG_CMD_SYSTEM_PKG_VERSION_SET = 0x485,
	MSG_CMD_SYSTEM_DEBUG_LEVEL_CFG_MAN_SET = 0x486,
	MSG_CMD_SYSTEM_DEC_MODE_SET = 0x487,
	MSG_CMD_SYSTEM_COMP_MODE_SET = 0x488,
	// MAX -> 0x1000
	MSG_CMD_MAX = 0x1001
}MSG_CMD_CFG_MAN_TYPE;

/**************************************************************************
	1. MSG_CMD_DECODER_LIST_NUMBER_GET -> 获取轮播列表数量 decoder.list_number
**************************************************************************/
typedef struct _DECODER_LIST_NUMBER
{
	int list_number; // 列表数量
}DECODER_LIST_NUMBER;

/**************************************************************************
	2. MSG_CMD_DEVICE_SYSTEM_INFO_GET -> 获取系统信息 device.[version^sn^product_id^alais]
**************************************************************************/
typedef struct _DEVICE_SYSTEM_INFO
{
	char version[56];  // 版本信息
	char sn[56];  // 序列号
	char product_id[56];  // 产品型号
	char alais[56];  // 产品别名
}DEVICE_SYSTEM_INFO;

/**************************************************************************
	3. MSG_CMD_MOSAIC_STYLE_NUMBER_GET -> 获取样式个数 mosaic.number
**************************************************************************/
typedef struct _MOSAIC_STYLE_NUMBER
{
	int number;
}MOSAIC_STYLE_NUMBER;

/**************************************************************************
	4. MSG_CMD_MOSAIC_STYLE_GET -> 获取样式 mosaic.styleN.[enable^pic_number^picN.[width^height^x_pos^y_pos^layer]]
**************************************************************************/
#define MOSAIC_PICTURE_MAX  9 
// 窗口描述
typedef struct _MOSAIC_PICTURE
{
	int width;  // 宽
	int height;  // 高
	int x_pos;  // 起始坐标 - x
	int y_pos;  // 起始坐标 - y
	int layer;  // 显示层
}MOSAIC_PICTURE;

// 样式描述
typedef struct _MOSAIC_STYLE
{
	int no;  // 样式的编号
	int enable;  // 使能
	int pic_number;  // 窗口个数 <= 9
	MOSAIC_PICTURE pics[MOSAIC_PICTURE_MAX];  // 窗口的描述
}MOSAIC_STYLE;

/**************************************************************************
	5. MSG_CMD_SYSTEM_PKG_VERSION_GET -> 版本号 system.pkg_version
**************************************************************************/
typedef struct _SYSTEM_PKG_VERSION
{
	char pkg_version[128];
}SYSTEM_PKG_VERSION;

/**************************************************************************
	6. MSG_CMD_SYSTEM_DEBUG_LEVEL_CFG_MAN_GET -> 调试等级 system.debug_level.cfg_man
**************************************************************************/
typedef struct _SYSTEM_DEBUG_LEVEL_CFG_MAN
{
	int debug_level;
}SYSTEM_DEBUG_LEVEL_CFG_MAN;

/**************************************************************************
	7. MSG_CMD_SYSTEM_DEC_MODE_GET -> 工作模式 system.dec_mode
**************************************************************************/
typedef struct _SYSTEM_DEC_MODE
{
	char dec_mode[16];
}SYSTEM_DEC_MODE;

/**************************************************************************
	8. MSG_CMD_SYSTEM_COMP_MODE_GET -> 分量输出的格式 system.comp_mode
**************************************************************************/
typedef struct _SYSTEM_COMP_MODE
{
	char comp_mode[16];
}SYSTEM_COMP_MODE;
#endif