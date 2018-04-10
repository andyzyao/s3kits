enable_testing() 
add_subdirectory("${CMAKE_SOURCE_DIR}/src/googletest")

include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src/googletest/googletest/include")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/aws-sdk-cpp")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src/aws-sdk-cpp/aws-cpp-sdk-core/include")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src/aws-sdk-cpp/aws-cpp-sdk-s3/include")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src")

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

find_package(CURL)
if(CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIR})
else(CURL_FOUND)
  message(FATAL_ERROR "curl not found!")
endif(CURL_FOUND)

add_library(s3_client s3_client.cpp)	
target_link_libraries(s3_client auth base64 ${CURL_LIBRARY})

add_executable(s3_client_test s3_client_test.cpp)	
target_link_libraries(s3_client_test s3_client gtest gtest_main)
add_test(s3_client_test s3_client_test)	

#file(GLOB google-url-srcs ${CMAKE_SOURCE_DIR}/src/google-url/src/*.cc)
#file(GLOB google-url-srcs ${CMAKE_SOURCE_DIR}/src/google-url/base/*.cc)
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/src/google-url")
add_library(google-url "${CMAKE_SOURCE_DIR}/src/google-url/src/url_parse.cc")

add_executable(s3sh s3sh.cpp)
target_link_libraries(s3sh aws-cpp-sdk-core aws-cpp-sdk-s3 google-url)

