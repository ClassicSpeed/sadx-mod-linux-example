cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(MySADXMod LANGUAGES CXX)

add_library(MySADXMod SHARED src/mod.cpp)

target_compile_features(MySADXMod PRIVATE cxx_std_17)


target_include_directories(MySADXMod SYSTEM PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader/SADXModLoader/include)


target_compile_options(MySADXMod PRIVATE
        # Downgrades the function-pointer → void* error inside UsercallFunctionHandler.h
        # to a warning; the SYSTEM include above then suppresses that warning.
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fpermissive>)


target_compile_definitions(MySADXMod PRIVATE
        WIN32
        _WINDOWS
        _USRDLL
        # Non-MSVC workaround: SADXVariables.h still references legacy names.
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:AnimData=AnimData_t>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:PhysicsData=PhysicsData_t>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:AdventureData=AdventureData_t>
        # Skip GCC-incompatible MSVC inline-asm declarations in function headers.
        SADXMODLOADER_SADXFUNCTIONS_H
        SADXMODLOADER_SADXFUNCTIONSNEW_H
)

target_link_options(MySADXMod PRIVATE -static-libgcc -static-libstdc++)

set_target_properties(MySADXMod PROPERTIES PREFIX "" OUTPUT_NAME "my-sadx-mod")
