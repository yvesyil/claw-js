function(kernel2str KERNELS)
    foreach(kernel ${KERNELS})
        get_filename_component(kernel_path "${kernel}" PATH)
        get_filename_component(kernel_name "${kernel}" NAME)
        get_filename_component(kernel_name_we "${kernel}" NAME_WE)

        # read source
        file(STRINGS ${kernel} kernel_src)

        # convert to list
        set(kernel_str "const char *_opencl_kernel_${kernel_name_we} = ")
        foreach(line ${kernel_src})
            set(kernel_str "${kernel_str}\n\"${line}\\n\"")
        endforeach()
        set(kernel_str "${kernel_str};")

        # write header
        file(WRITE "${kernel_path}/${kernel_name_we}.str.c" "// auto generated file.\n${kernel_str}")
    endforeach()
endfunction(kernel2str)
