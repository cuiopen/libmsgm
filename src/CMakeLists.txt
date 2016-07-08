cmake_minimum_required(VERSION 2.8)

SET(CMAKE_C_COMPILER  arm-arago-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER arm-arago-linux-gnueabi-g++)
SET(CMAKE_ASM_COMPILER arm-arago-linux-gnueabi-gcc)

set(LIB_SRC common.h debug.h msgm.c etah_msgq.h)
add_library(libmsgm ${LIB_SRC})
set_target_properties(libmsgm PROPERTIES OUTPUT_NAME "etah_msgq")

INSTALL(FILES etah_msgq.h
			DESTINATION include)
			
INSTALL(TARGETS libmsgm
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)