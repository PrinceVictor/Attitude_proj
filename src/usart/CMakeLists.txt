set(libcommuni_src communi.cpp)
set(libusart_src usart.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(communi_src SHARED ${libcommuni_src})
add_library(usart_src SHARED ${libusart_src})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(communi ${libcommuni_src})
target_link_libraries(communi ${Boost_LIBRARIES} usart_src )
