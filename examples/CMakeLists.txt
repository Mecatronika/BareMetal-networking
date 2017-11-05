cmake_minimum_required(VERSION 3.0.2)

function(ADD_LIBNET_EXAMPLE EXAMPLE_NAME)
	add_executable(${EXAMPLE_NAME} ${ARGN})
	target_link_libraries(${EXAMPLE_NAME} "net")
	target_include_directories(${EXAMPLE_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
endfunction(ADD_LIBNET_EXAMPLE EXAMPLE_NAME)

add_libnet_example("example1" "example1.c")

add_libnet_example("tcp-pack" "tcp-pack.c")
