cmake_minimum_required(VERSION 4.0)

project(Mandarine LANGUAGES CXX)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

include(FetchContent)

FetchContent_Declare(cereal GIT_REPOSITORY https://github.com/uscilab/cereal GIT_TAG master)
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cereal)

FetchContent_Declare(EventBus GIT_REPOSITORY https://github.com/gelldur/eventbus GIT_TAG master)
set(ENABLE_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(EventBus)

FetchContent_Declare(FLAC GIT_REPOSITORY https://github.com/xiph/flac GIT_TAG master)
set(INSTALL_MANPAGES OFF CACHE BOOL "" FORCE)
set(WITH_OGG OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(FLAC)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG main)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(magic_enum GIT_REPOSITORY https://github.com/neargye/magic_enum GIT_TAG master)
FetchContent_MakeAvailable(magic_enum)

FetchContent_Declare(miniz GIT_REPOSITORY https://github.com/richgel999/miniz GIT_TAG master)
FetchContent_MakeAvailable(miniz)

FetchContent_Declare(zlib GIT_REPOSITORY https://github.com/madler/zlib GIT_TAG develop)
FetchContent_MakeAvailable(zlib)

add_library(lzma STATIC
    externals/lzma-sdk/C/Alloc.c
    externals/lzma-sdk/C/Bra86.c
    externals/lzma-sdk/C/Bra.c
    externals/lzma-sdk/C/BraIA64.c
    externals/lzma-sdk/C/CpuArch.c
    externals/lzma-sdk/C/Delta.c
    externals/lzma-sdk/C/LzFind.c
    externals/lzma-sdk/C/Lzma86Dec.c
    externals/lzma-sdk/C/Lzma86Enc.c
    externals/lzma-sdk/C/LzmaDec.c
    externals/lzma-sdk/C/LzmaEnc.c
    externals/lzma-sdk/C/LzmaLib.c
    externals/lzma-sdk/C/Sort.c
)
target_include_directories(lzma PUBLIC externals/lzma-sdk/C)
target_compile_definitions(lzma PRIVATE _7ZIP_ST)

add_library(chdr STATIC
    externals/libchdr/src/bitstream.c
    externals/libchdr/src/cdrom.c
    externals/libchdr/src/chd.c
    externals/libchdr/src/huffman.c
    externals/libchdr/src/flac.c
)
target_include_directories(chdr PUBLIC externals/libchdr/src)
target_link_libraries(chdr FLAC lzma miniz zlib)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

if (MSVC)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    ${CMAKE_CURRENT_SOURCE_DIR}/externals/stb
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE cereal chdr Dexode::EventBus fmt-header-only magic_enum miniz)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # BIOS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/bios/functions.cpp

    # CPU
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/cop0.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/instructions.cpp

    # CPU/GTE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/gte/gte.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/gte/math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/cpu/gte/opcodes.cpp

    # DEBUGGER
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/debugger/debugger.cpp

    # DEVICE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/cache_control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/expansion2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/interrupt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/memory_control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/ram_control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/serial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/timer.cpp

    # DEVICE/CDROM
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/cdrom/cdrom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/cdrom/commands.cpp

    # DEVICE/CONTROLLER
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/controller.cpp

    # DEVICE/CONTROLLER/PERIPHERALS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/abstract_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/analog_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/digital_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/memory_card.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/mouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/controller/peripherals/none.cpp

    # DEVICE/DMA
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma0_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma1_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma2_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma3_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma4_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma5_channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/dma/dma6_channel.cpp

    # DEVICE/GPU
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/color_depth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/gpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/psx_color.cpp

    # DEVICE/GPU/RENDER
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/render/dither.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/render/render_line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/render/render_rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/gpu/render/render_triangle.cpp

    # DEVICE/MDEC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/mdec/algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/mdec/mdec.cpp

    # DEVICE/SPU
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/adsr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/interpolation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/noise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/reverb.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/spu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/device/spu/voice.cpp

    # DISC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/disc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/load.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/position.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/subchannel_q.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/track.cpp

    # DISC/FORMAT
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/format/chd_format.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/format/cue_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/format/cue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/format/ecm_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/disc/format/ecm.cpp

    # INPUT
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/input/input_manager.cpp

    # MEMORY_CARD
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/memory_card/card_formats.cpp

    # SOUND
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/sound/adpcm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/sound/tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/sound/wave.cpp

    # STATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/state/state.cpp

    # UTILS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/bcd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/file.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/gpu_draw_list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/psf.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/stb_image_write.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/string.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/utils/vector.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/sources/config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/stdafx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/system_tools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/system.cpp
)