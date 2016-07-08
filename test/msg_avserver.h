/******************************************************************************
 * 文件名  ： msg_avserver.h
 * 负责人  ： heyang
 * 创建日期： 20151201 
 * 版本号  ： v1.1
 * 文件描述：avserver提供给控制接口头文件
 * 版权说明： Copyright (c) 2008-2020   武汉东信同邦信息技术有限公司
 * 其    他： 无
 * 修改日志： 无
******************************************************************************/
#ifndef __MSG_AVSERVER_H__
#define __MSG_AVSERVER_H__

/*
* 0. 消息队列命令
*/
typedef enum{
    MSG_CMD_AVSERVER_OUTPUT_RES,
    /** <设置显示分辨率*/
    MSG_CMD_AVSERVER_OUTPUT_MS_INFO,
    /** <设置显示拼接信息*/
    
    MSG_CMD_AVSERVER_MAX
}MSG_CMD_AVSERVER_TYPE;


//1.1 MSG_CMD_AVSERVER_OUTPUT_MS_INFO
typedef struct _OUTPUT_MOSIAC_INFO
{
    int dev_no;
    /** <显示设备号*/
    int  style;
    /** <显示拼接样式ID*/
    int src2chId[9];
    /** <显示拼接通道对应关系*/
}OUTPUT_MOSIAC_INFO;

//1.2 MSG_CMD_AVSERVER_OUTPUT_RES
typedef struct _OUTPUT_DEV_RES
{
    int dev_no;
    /** <显示设备号*/
    char output_res[128];
    /** <显示设备显示分辨率*/
}OUTPUT_DEV_RES;



#endif


