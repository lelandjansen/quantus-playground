cmake_minimum_required(VERSION 3.6)
project(sd-card)


set(DEVICE_MODEL atmega328p)
set(F_CPU 16000000)

set(CMAKE_C_COMPILER /usr/local/Cellar/avr-gcc/4.9.3/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/local/Cellar/avr-gcc/4.9.3/bin/avr-g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -mmcu=${DEVICE_MODEL} -DF_CPU=${F_CPU}UL -fdata-sections -ffunction-sections -Wl,--gc-sections -std=c++11") #
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -mmcu=${DEVICE_MODEL} -DF_CPU=${F_CPU}UL -fdata-sections -ffunction-sections") #


# Disable -Wl,-search_paths_first for OSX
if(APPLE)
    string(REPLACE "-Wl,-search_paths_first" "" CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS})
endif()


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(lib/ff12b/src)

set(SOURCE_FILES
        src/main.cc
        src/led/led.cc
        src/button/button.cc

        src/main.c

#        lib/ff12b/src/diskio.c
#        lib/ff12b/src/ff.c
        lib/ff/ff.c
        lib/ff/mmc_avr.c
        )

set(HEADER_FILES
#        src/main.h
        src/led/led.h
        src/button/button.h

#        lib/ff12b/src/diskio.h
#        lib/ff12b/src/ff.h
#        lib/ff12b/src/ffconf.h
#        lib/ff12b/src/integer.h
        lib/ff/diskio.h
        lib/ff/ff.h
        lib/ff/ffconf.h
        lib/ff/integer.h
        lib/ff/mmc_avr.h
#        lib/ff/xitoa.h
        )


add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -j .text -j .data -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf --mcu=${DEVICE_MODEL} --format=avr)
#consider using avr-strip
