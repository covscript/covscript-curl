cmake_minimum_required(VERSION 3.16)

project(covscript-curl)

if (DEFINED ENV{CS_DEV_PATH})
    message("-- CovScript SDK detected at $ENV{CS_DEV_PATH}")
    include("$ENV{CS_DEV_PATH}/csbuild.cmake")
    include_directories($ENV{CS_DEV_PATH}/include)
    link_directories($ENV{CS_DEV_PATH}/lib)
else ()
    message(FATAL_ERROR "-- CovScript SDK not detected. Please set environment variable CS_DEV_PATH")
endif ()

add_library(curl_ext SHARED curl.cpp)

target_link_libraries(curl_ext covscript curl)

if (WIN32)
    target_compile_definitions(curl_ext PRIVATE CURL_STATICLIB)
    set(WIN32_OS_LINK_LIBS crypt32 bcrypt wldap32 secur32 iphlpapi ws2_32)
    set(WIN32_CURL_LINK_LIBS nghttp2 ssh2 z ssl crypto brotlidec brotlicommon zstd nghttp3 ngtcp2 ngtcp2_crypto_quictls psl)
    target_link_libraries(curl_ext ${WIN32_CURL_LINK_LIBS} ${WIN32_OS_LINK_LIBS})
endif ()

set_target_properties(curl_ext PROPERTIES OUTPUT_NAME curl)
set_target_properties(curl_ext PROPERTIES PREFIX "")
set_target_properties(curl_ext PROPERTIES SUFFIX ".cse")