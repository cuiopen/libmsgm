#include <stdio.h>
#include "etah_msgq.h"

#define COMMON_KEY_0    0x03
#define COMMON_KEY_1    0x04
#define COMMON_KEY_2    0x05
#define COMMON_KEY_3    0x06

#include "etah_modules.h"

int main()
{
	int ret;
	
	ret = msgm_create(ETAH_MODULE_SYS_MON);
	printf("1. ret -> %d\n", ret);
	
	ret = msgm_create(ETAH_MODULE_HTTP_SVR);
	printf("2. ret -> %d\n", ret);
	
	ret = msgm_create(ETAH_MODULE_CFG_MAN);
	printf("3. ret -> %d\n", ret);
	
	ret = msgm_create(ETAH_MODULE_CODEC_CORE);
	printf("4. ret -> %d\n", ret);

    ret = msgm_create(ETAH_MODULE_SYS_SVR);
	printf("5. ret -> %d\n", ret);

    ret = msgm_create(ETAH_MODULE_CCODE_MAN);
	printf("5. ret -> %d\n", ret);
}