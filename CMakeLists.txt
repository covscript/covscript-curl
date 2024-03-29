cmake_minimum_required(VERSION 3.10)

project(covscript-curl)

if (DEFINED ENV{CS_DEV_PATH})
    include_directories($ENV{CS_DEV_PATH}/include)
    link_directories($ENV{CS_DEV_PATH}/lib)
endif ()

if (DEFINED ENV{CS_DEV_OUTPUT})
    set(LIBRARY_OUTPUT_PATH $ENV{CS_DEV_OUTPUT})
    set(EXECUTABLE_OUTPUT_PATH $ENV{CS_DEV_OUTPUT})
endif ()

# Compiler Options
set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/O2 /EHsc /utf-8 /w")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    if (WIN32)
        set(CMAKE_C_FLAGS "--static -fPIC -s -O3")
        set(CMAKE_CXX_FLAGS "--static -fPIC -s -O3")
    else ()
        set(CMAKE_C_FLAGS "-fPIC -s -O3")
        set(CMAKE_CXX_FLAGS "-fPIC -s -O3")
    endif ()
else ()
    set(CMAKE_C_FLAGS "-fPIC -O3")
    set(CMAKE_CXX_FLAGS "-fPIC -O3")
endif ()

add_library(curl_ext SHARED curl.cpp)

target_link_libraries(curl_ext covscript curl)

if (WIN32)
    target_compile_definitions(curl_ext PRIVATE CURL_STATICLIB)
    target_link_libraries(curl_ext crypt32 wldap32 nghttp2 ssh2 z bcrypt ssl crypto brotlidec brotlicommon zstd nghttp3 ngtcp2 ngtcp2_crypto_quictls ws2_32)
endif ()

set_target_properties(curl_ext PROPERTIES OUTPUT_NAME curl)
set_target_properties(curl_ext PROPERTIES PREFIX "")
set_target_properties(curl_ext PROPERTIES SUFFIX ".cse")