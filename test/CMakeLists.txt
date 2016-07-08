cmake_minimum_required(VERSION 2.6.3)
SET(CMAKE_C_COMPILER arm-arago-linux-gnueabi-g++)
SET(CMAKE_CXX_COMPILER arm-arago-linux-gnueabi-g++)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(INIT_SRC msg_init.c)
set(CLIENT_SRC msg_client.c)
set(SERVER_SRC msg_server.c)

add_executable(msg_init ${INIT_SRC})
add_executable(msg_client ${CLIENT_SRC})
add_executable(msg_server ${SERVER_SRC})

target_link_libraries(msg_init libmsgm pthread)
target_link_libraries(msg_client libmsgm pthread)
target_link_libraries(msg_server libmsgm pthread)
