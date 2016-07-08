/******************************************************************************
 * �ļ���  �� msg_avserver.h
 * ������  �� heyang
 * �������ڣ� 20151201 
 * �汾��  �� v1.1
 * �ļ�������avserver�ṩ�����ƽӿ�ͷ�ļ�
 * ��Ȩ˵���� Copyright (c) 2008-2020   �人����ͬ����Ϣ�������޹�˾
 * ��    ���� ��
 * �޸���־�� ��
******************************************************************************/
#ifndef __MSG_AVSERVER_H__
#define __MSG_AVSERVER_H__

/*
* 0. ��Ϣ��������
*/
typedef enum{
    MSG_CMD_AVSERVER_OUTPUT_RES,
    /** <������ʾ�ֱ���*/
    MSG_CMD_AVSERVER_OUTPUT_MS_INFO,
    /** <������ʾƴ����Ϣ*/
    
    MSG_CMD_AVSERVER_MAX
}MSG_CMD_AVSERVER_TYPE;


//1.1 MSG_CMD_AVSERVER_OUTPUT_MS_INFO
typedef struct _OUTPUT_MOSIAC_INFO
{
    int dev_no;
    /** <��ʾ�豸��*/
    int  style;
    /** <��ʾƴ����ʽID*/
    int src2chId[9];
    /** <��ʾƴ��ͨ����Ӧ��ϵ*/
}OUTPUT_MOSIAC_INFO;

//1.2 MSG_CMD_AVSERVER_OUTPUT_RES
typedef struct _OUTPUT_DEV_RES
{
    int dev_no;
    /** <��ʾ�豸��*/
    char output_res[128];
    /** <��ʾ�豸��ʾ�ֱ���*/
}OUTPUT_DEV_RES;



#endif


