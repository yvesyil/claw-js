add_library(clblast SHARED IMPORTED GLOBAL)

set_target_properties(clblast PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libclblast.dylib)