
add_subdirectory(usart )

set(SRC_LIST main.cpp)

set(header_path "../src")

INCLUDE_DIRECTORIES(
    ${header_path}
    ${header_path}/usart
    )

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}
                                      communi_src
                                      usart_src)
