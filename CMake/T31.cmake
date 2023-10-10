if(BOARD STREQUAL "T31")
    set(BOARD_SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${BOARD})
    set(BOARD_SRCS
        ${BOARD_SDK_DIR}/samples/libimp-samples/sample-common.c
    )
    set(BOARD_INCS_DIR
        ${BOARD_SDK_DIR}/include/
        ${BOARD_SDK_DIR}/samples/libimp-samples/
    )
    set(BOARD_LIBS_DIR
        ${BOARD_SDK_DIR}/lib
        ${BOARD_SDK_DIR}/lib/dynamic
        ${BOARD_SDK_DIR}/lib/dynamic/ivs
        ${BOARD_SDK_DIR}/lib/dynamic/mxu
        ${BOARD_SDK_DIR}/lib/dynamic/imp
        ${BOARD_SDK_DIR}/lib/static
        ${BOARD_SDK_DIR}/lib/static/ivs
        ${BOARD_SDK_DIR}/lib/static/mxu
        ${BOARD_SDK_DIR}/lib/static/imp
    )

    if(USE_MUCLIBC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -muclibc")
        set(BOARD_DESTINATION_PLATFORM mips-linux-uclibc-gnu)
    else()
        set(BOARD_DESTINATION_PLATFORM mips-linux-gnu)
    endif()
    set(BOARD_LIBS_SHARED
        Aoni_CPU_SDK_MD_HD_PET_VEH_MT fdk-aac mxu_merge mxu_objdetect mxu_contrib mxu_video mxu_imgproc mxu_core move_inf petbodyDet_inf motion_tracker_inf personDet_inf vehicleDet_inf jzdl imp alog sysutils rt m pthread dl
        # rt m pthread dl
    )
    set(BOARD_LIBS_STATIC
        libAoni_CPU_SDK_MD_HD_PET_VEH_MT.a fdk-aac mxu_merge mxu_objdetect mxu_contrib mxu_video mxu_imgproc mxu_core move_inf petbodyDet_inf motion_tracker_inf personDet_inf vehicleDet_inf jzdl imp alog sysutils librt.a libm.a pthread dl
        # librt.a libm.a pthread dl
    )
endif()
