################################################################################
### define help functions and makros
################################################################################

################################################################################
# this function collect the source and header files for one directory
# arg1 = input dir name
# arg2 = output file list

function(CollectFilesInDir dir_name file_list)
    # collect the source and header files
    file(GLOB_RECURSE FILES_IN_DIR ${dir_name}/*.cpp ${dir_name}/*.c ${dir_name}/*.h)
    # set output variable to parent scope
    set(${file_list} ${FILES_IN_DIR} PARENT_SCOPE)
    # set filter for visual studio
    # source_group(${dir_name} FILES ${FILES_IN_DIR})
	
	foreach(FILE ${FILES_IN_DIR}) 
		# Get the directory of the source file
		get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
	
		# Remove common directory prefix to make the group
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	
		# Make sure we are using windows slashes
		string(REPLACE "/" "\\" GROUP "${GROUP}")
	
		# Group into "Source Files" and "Header Files"
		if ("${FILE}" MATCHES ".*\\.cpp")
		set(GROUP "Source Files${GROUP}")
		elseif("${FILE}" MATCHES ".*\\.h")
		set(GROUP "Header Files${GROUP}")
		endif()
	
		source_group("${GROUP}" FILES "${FILE}")
	endforeach()
	
	if (NOT WIN32)
		message(STATUS "collect files for directory ${dir_name}")
	endif ()
endfunction()

################################################################################
# this function collect the source and header files for list of directories
# arg1 = input list of dirs (use "${VAR}")
# arg2 = output file list

function(CollectFilesForLib dir_list file_list)
	if (NOT WIN32)
		message(STATUS "================ directory: ${file_list} ===============")
	endif ()
	
    foreach(dir_name ${dir_list})
        CollectFilesInDir(${dir_name} dir_file_list)
        set(FILES_IN_DIR ${FILES_IN_DIR} ${dir_file_list})
    endforeach(dir_name)
    # set output variable to parent scope
    set(${file_list} ${FILES_IN_DIR} PARENT_SCOPE)
endfunction()

################################################################################
# this function collect the source and header files for current directory
# arg2 = output file list

function(CollectFiles file_list)
    # collect the source and header files
    file(GLOB_RECURSE FILES_IN_DIR *.cpp *.c *.h)
    # set output variable to parent scope
    set(${file_list} ${FILES_IN_DIR} PARENT_SCOPE)
    source_group(src FILES ${FILES_IN_DIR})
endfunction()

################################################################################
# this function collect the cuda source files for one directory
# arg1 = input dir name
# arg2 = output file list

function(CollectCudaFilesInDir dir_name file_list)
    # collect the cuda source files
    file(GLOB_RECURSE FILES_IN_DIR ${dir_name}/*.cu)
    # set output variable to parent scope
    set(${file_list} ${FILES_IN_DIR} PARENT_SCOPE)
    source_group(GpuKernels FILES ${FILES_IN_DIR})
    message(STATUS "collect *.cu files for directory ${dir_name}")
endfunction()