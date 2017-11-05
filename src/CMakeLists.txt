cmake_minimum_required(VERSION 3.0.2)

add_library("net"
	"buffer.c"
	"crc.c"
	"crc32.c"
	"ethernet.c"
	"ipv6.c"
	"mac.c"
	"mutator.c"
	"pipe.c"
	"protocol.c"
	"stack.c"
	"tcp.c")

target_include_directories("net" PRIVATE "${PROJECT_SOURCE_DIR}/include")

set (LIBNET_GNU_CFLAGS -Wall -Wextra -Werror -Wfatal-errors -std=c99)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options("net" PRIVATE ${LIBNET_GNU_CFLAGS})
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")

enable_testing()

function(ADD_LIBNET_TEST TEST_NAME)
	add_executable(${TEST_NAME} ${ARGN})
	target_link_libraries(${TEST_NAME} "net")
	target_include_directories(${TEST_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
	add_test(${TEST_NAME} ${TEST_NAME})
endfunction(ADD_LIBNET_TEST TEST_NAME)

add_libnet_test("buffer-test" "buffer-test.c")
add_libnet_test("crc-test" "crc-test.c")
add_libnet_test("ethernet-test" "ethernet-test.c")
add_libnet_test("ipv6-test" "ipv6-test.c")
add_libnet_test("mac-test" "mac-test.c")
add_libnet_test("tcp-test" "tcp-test.c")
