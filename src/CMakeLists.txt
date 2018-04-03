enable_testing() 
add_subdirectory("${CMAKE_SOURCE_DIR}/src/googletest")

include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src/googletest/googletest/include")

add_executable(hello hello.cpp)

add_library(base64 base64.cpp)

find_package(OpenSSL)
add_library(auth auth.cpp)
target_link_libraries(auth ${OPENSSL_LIBRARIES})	

add_executable(auth_test auth_test.cpp)	
target_link_libraries(auth_test auth base64 gtest gtest_main)
add_test(auth_test auth_test)	

add_executable(base64_test base64_test.cpp)	
target_link_libraries(base64_test base64 gtest gtest_main)
add_test(base64_test base64_test)	
