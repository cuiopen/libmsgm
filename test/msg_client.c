#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define COMMON_KEY_0    0x03
#define COMMON_KEY_1    0x04
#define COMMON_KEY_2    0x05
#define COMMON_KEY_3    0x06

#define TIMEOUT_FOR_5S  5000  // ����Ϊ��λ

#include "etah_msgq.h"
#include "etah_modules.h"
#include "msg_type_all.h"

int deal_to_ask(void* handle, int cmd, int params_len, char* params, int *result_len, char* result)
{
	printf("cmd -> %d params_len -> %d \n", cmd, params_len);
	*result_len = 4;
	memcpy(result, "456", *result_len);

	return 0;
}

int main(int argc, char *argv[])
{
	MSGM_HANDLE *msg_handle = NULL;
	int index = 0;
	int channel = 0; // 1,2,3,4

	msg_handle = msgm_open(ETAH_MODULE_SYS_MON);
	msgm_ask_handle_register(msg_handle, deal_to_ask, NULL);

	MSGM_CMD msg_in;
	MSGM_CMD msg_out;
	memset(&msg_in, 0, sizeof(MSGM_CMD));
	memset(&msg_out, 0, sizeof(MSGM_CMD));

/*******************************************************************
* SYS_SVR ----------------------------------> START
*******************************************************************/
#if 0
	msg_in.cmd = MSG_CMD_NETWORK_INTERFACE_SET;
	msg_in.ret = 0;
    
    NETWORK_INTERFACE interf;
    interf.id = 0;
    interf.enable = 1;
    strcpy(interf.mac, "20:20:20:20:20:20");
    interf.dhcp = 0;
    interf.addr[0].enable = 1;
    strcpy(interf.addr[0].ip_addr, "172.16.135.111");
    strcpy(interf.addr[0].net_mask, "255.255.255.0");
    interf.addr[1].enable = 0;
    strcpy(interf.addr[1].ip_addr, "172.16.135.114");
    strcpy(interf.addr[1].net_mask, "255.0.0.0");

    msg_in.len = sizeof(NETWORK_INTERFACE);
    memcpy(msg_in.params, &interf, msg_in.len);
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	NETWORK_INTERFACE *tmp = (NETWORK_INTERFACE*)msg_out.params;
    printf("id -> %d\n", tmp->id);
    printf("enable -> %d\n", tmp->enable);
    printf("mac -> %s\n", tmp->mac);
    printf("dhcp -> %d\n", tmp->dhcp);
    printf("add0.enable -> %d\n", tmp->addr[0].enable);
    printf("add0.ip_addr -> %s\n", tmp->addr[0].ip_addr);
    printf("add0.net_mask -> %s\n", tmp->addr[0].net_mask);
#endif

#if 0
    msg_in.cmd = MSG_CMD_NETWORK_DNS_SET;
    NETWORK_DNS dns;
    strcpy(dns.preferred, "1.2.3.4");
    strcpy(dns.alternate, "4.5.6.7");

    msg_in.len = sizeof(NETWORK_DNS);
    memcpy(msg_in.params, &dns, msg_in.len);

    msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

    NETWORK_DNS *tmp = (NETWORK_DNS *)msg_out.params;

    printf("1 -> %s\n", tmp->preferred);
    printf("2 -> %s\n", tmp->alternate);

#endif

#if 0
    msg_in.cmd = MSG_CMD_NETWORK_GATEWAY_SET;
    NETWORK_GATEWAY gateway;

    gateway.id = 0;
    strcpy(gateway.gateway, "172.16.1.4");

    msg_in.len = sizeof(NETWORK_GATEWAY );
    memcpy(msg_in.params, &gateway, msg_in.len);

    msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

    NETWORK_GATEWAY *tmp = (NETWORK_GATEWAY*)msg_out.params;
    printf("id -> %d gateway -> %s\n", tmp->id, tmp->gateway);

#endif

#if 0
    msg_in.cmd = MSG_CMD_SYSTEM_NTP_SET;
    SYSTEM_NTP ntp;

    ntp.enable = 1;
    strcpy(ntp.address, "172.16.3.35");
    //strcpy(ntp.time, "2015 01 01 01 00 00");

    msg_in.len = sizeof(SYSTEM_NTP );
    memcpy(msg_in.params, &ntp, msg_in.len);

    msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

    SYSTEM_NTP *tmp = (SYSTEM_NTP*)msg_out.params;
    printf("1 -> %d\n", tmp->enable);
    printf("2 -> %s\n", tmp->address);
    printf("3 -> %s\n", tmp->time);

#endif

#if 0
    msg_in.cmd = MSG_CMD_SYSTEM_DEBUG_LEVEL_SYS_SVR_SET;
    SYSTEM_DEBUG_LEVEL_SYS_SVR debug_level;
	
	debug_level.debug_level = 0x1000001f;

    msg_in.len = sizeof(SYSTEM_DEBUG_LEVEL_SYS_SVR );
    memcpy(msg_in.params, &debug_level, msg_in.len);

    msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	SYSTEM_DEBUG_LEVEL_SYS_SVR *tmp = (SYSTEM_DEBUG_LEVEL_SYS_SVR*)msg_out.params;
	
	printf("debug -> 0x%x\n", tmp->debug_level);

#endif

/*******************************************************************
* SYS_SVR ----------------------------------> END
*******************************************************************/

/*******************************************************************
* CODEC_MAN ----------------------------------> START
*******************************************************************/
#if 0
	msg_in.cmd = MSG_CMD_DECODER_AUTO_LOOP_SET;
	DECODER_AUTO_LOOP auto_loop;
	
	auto_loop.enable = 1;
	auto_loop.interval = 10;
	
	msg_in.len = sizeof(DECODER_AUTO_LOOP);
	memcpy(msg_in.params, &auto_loop, msg_in.len);
	
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);
	
	DECODER_AUTO_LOOP *tmp = (DECODER_AUTO_LOOP*)msg_out.params;
	
	printf("enable -> %d interval -> %d\n", tmp->enable, tmp->interval);
	
#endif

#if 1
	msg_in.cmd = MSG_CMD_DECODER_DEC_SRC_SET;
	DECODER_DEC_SRC dec_src;
	
	dec_src.channel = 0;
	dec_src.enable = 1;
	strcpy(dec_src.alais, "ktfun");
	dec_src.protocol = PROTOCOL_RTMP;
	dec_src.cache = 200;
	//strcpy(dec_src.params, "ip=172.16.65.87,port=1935,app=teach_app,stream=172166587_chd_h,login=admin,passwd=123");
	strcpy(dec_src.params, "ip=172.16.3.35,port=1935,app=teach_app,stream=201601221109_chd_h,login=admin,passwd=123");
	
	msg_in.len = sizeof(DECODER_DEC_SRC);
	memcpy(msg_in.params, &dec_src, msg_in.len);
	
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);
	
	DECODER_DEC_SRC *tmp = (DECODER_DEC_SRC*)msg_out.params;
	
	printf("ch -> %d\n", tmp->channel);
	printf("enable -> %d\n", tmp->enable);
	printf("alais -> %s\n", tmp->alais);
	printf("protocol -> %d\n", tmp->protocol);
	printf("cache -> %d\n", tmp->cache);
	printf("params -> %s\n", tmp->params);
	
#endif
/*******************************************************************
* CODEC_MAN ----------------------------------> END
*******************************************************************/

#if 0
	msg_in.cmd = MSG_CMD_DECODER_LIST_NUMBER_SET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);
#endif

#if 0
	msg_in.cmd = MSG_CMD_DEVICE_SYSTEM_INFO_SET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	DEVICE_SYSTEM_INFO tmp = *(DEVICE_SYSTEM_INFO*)(&msg_out.params);
	printf("%s %s %s %s\n", tmp.version, tmp.sn, tmp.product_id, tmp.alais);
#endif

#if 0
	msg_in.cmd = MSG_CMD_MOSAIC_STYLE_NUMBER_SET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	MOSAIC_STYLE_NUMBER tmp = *(MOSAIC_STYLE_NUMBER*)(&msg_out.params);
	printf("%d\n", tmp.number);
#endif

#if 0
	msg_in.cmd = MSG_CMD_MOSAIC_STYLE_SET;
	msg_in.ret = 0;

	MOSAIC_STYLE tmp_in;
	tmp_in.no = 3;
	msg_in.len = sizeof(MOSAIC_STYLE);

	memcpy(msg_in.params, &tmp_in, sizeof(MOSAIC_STYLE));

	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	MOSAIC_STYLE tmp_out = *(MOSAIC_STYLE*)(&msg_out.params);
	printf("%d %d %d \n", tmp_out.no, tmp_out.enable, tmp_out.pic_number);

	for (index = 0; index < tmp_out.pic_number; index++)
	{
		printf("%d %d %d %d %d\n", tmp_out.pics[index].width,
			tmp_out.pics[index].height,
			tmp_out.pics[index].x_pos,
			tmp_out.pics[index].y_pos,
			tmp_out.pics[index].layer);
	}
#endif

#if 0
	msg_in.cmd = MSG_CMD_SYSTEM_PKG_VERSION_SET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	SYSTEM_PKG_VERSION tmp = *(SYSTEM_PKG_VERSION*)(&msg_out.params);
	printf("%s\n", tmp.pkg_version);
#endif

#if 0
	msg_in.cmd = MSG_CMD_SYSTEM_DEBUG_LEVEL_CFG_MAN_GET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	SYSTEM_DEBUG_LEVEL_CFG_MAN tmp = *(SYSTEM_DEBUG_LEVEL_CFG_MAN*)(&msg_out.params);
	printf("%x\n", tmp.debug_level);
#endif

#if 0
    SYSTEM_DEC_MODE tmp_in;
    strcpy(tmp_in.dec_mode, "1080P");
    msg_in.len = sizeof(SYSTEM_DEC_MODE);
    memcpy(msg_in.params, &tmp_in, msg_in.len);
	msg_in.cmd = MSG_CMD_SYSTEM_DEC_MODE_SET;
	msg_in.ret = 0;
	msgm_send_ask_timeout(msg_handle, &msg_in, &msg_out, TIMEOUT_FOR_5S, ETAH_MODULE_CFG_MAN);
	dump_MSGM_CMD(&msg_out, 16);

	printf("%s\n", msg_out.params);
#endif


}
