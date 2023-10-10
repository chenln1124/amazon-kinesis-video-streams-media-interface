if(BOARD STREQUAL "FILE")
    set(BOARD_SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${BOARD})
 
    set(BOARD_SRCS
        ${BOARD_SDK_DIR}/FILEPort.c
    )
    set(BOARD_INCS_DIR
        ${BOARD_SDK_DIR}
    )
    set(BOARD_LIBS_DIR
    )
    if(USE_MUCLIBC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -muclibc")
    endif()
    set(BOARD_LIBS_SHARED
       rt
    )
    set(BOARD_LIBS_STATIC
       librt.a
    )
endif()
