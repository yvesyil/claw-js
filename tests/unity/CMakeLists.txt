add_library(unity "")

target_sources(unity
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/unity.c
        ${CMAKE_CURRENT_LIST_DIR}/unity_internals.h
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/unity.h
        )

target_include_directories(unity PUBLIC ${CMAKE_CURRENT_LIST_DIR})