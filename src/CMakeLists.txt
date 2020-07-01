set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
	if ("${CMAKE_HOST_SYSTEM_PROCESSOR}" MATCHES "x86_64")
		set(ARCH_HINT "x86_64")
		set(OUT_LIB_SUFFIX "64")
		set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-windows-msvc")
	elseif ("${CMAKE_HOST_SYSTEM_PROCESSOR}" MATCHES "AMD64")
		set(ARCH_HINT "AMD64")
		set(OUT_LIB_SUFFIX "64")
		set(CMAKE_LIBRARY_ARCHITECTURE "amd64-windows-msvc")
	else ()
		set(ARCH_HINT "i386")
		set(OUT_LIB_SUFFIX "")
		set(CMAKE_LIBRARY_ARCHITECTURE "i386-windows-msvc")
	endif ()
endif()

# путь к доп. функциям
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Modules/CMake")

# подключаемые cmake модули
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckIncludeFiles)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)
include(CheckHeaderSTDC)
include(TestBigEndian)
include(CheckCXXSourceCompiles)
include(CMakeDependentOption)
include(CheckIncludeFile)
include(CheckTypeExists)
include(UserFunctions)
include(PrecompiledHeader)

add_subdirectory (Vendor)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()


# Northwind
set (NORTHWIND_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Northwind/src)

set (NORTHWIND_SRC_DIRS 
	Northwind/src
	Northwind/src/Core
	Northwind/src/Event
	Northwind/src/Platform
)

CollectFilesForLib("${NORTHWIND_SRC_DIRS}" NORTHWIND_SRC_FILES)

add_library(Northwind STATIC ${NORTHWIND_SRC_FILES})

target_include_directories(Northwind PUBLIC ${NORTHWIND_INCLUDE_DIRS})
set_target_properties(Northwind PROPERTIES LINKER_LANGUAGE CXX)
add_precompiled_header(Northwind nwpch.h FORCEINCLUDE SOURCE_CXX ${CMAKE_CURRENT_SOURCE_DIR}/Northwind/src/nwpch.cpp)

###############################################
## OPENGL
###############################################

find_package(OpenGL)
find_package(GLUT)

target_link_libraries(Northwind ${OPENGL_LIBRARIES} ${OPENGL_glu_LIBRARY})

# link glad
target_link_libraries(Northwind glad)

# link glfw
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GLFW/include)
target_link_libraries(Northwind glfw ${GLFW_LIBRARIES})
###############################################

# link spdlog 
spdlog_enable_warnings(Northwind)
target_link_libraries(Northwind spdlog::spdlog)

# link imgui
target_link_libraries(Northwind imgui)

# link glm
target_link_libraries(Northwind glm)






# Sandbox
set (SANDBOX_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src)

set (SANDBOX_INCLUDE_DIRS 
	Sandbox/src
)

CollectFilesForLib("${SANDBOX_INCLUDE_DIRS}" SANDBOX_SRC_FILES)

add_executable(Sandbox ${SANDBOX_SRC_FILES})
target_include_directories(Sandbox PUBLIC ${SANDBOX_INCLUDE_DIRS})
target_include_directories(Sandbox PUBLIC ${NORTHWIND_INCLUDE_DIRS})
target_include_directories(Sandbox PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include")
target_include_directories(Sandbox PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm")

target_link_libraries(Sandbox Northwind)
#

message (STATUS "=============== Configuration =================")
message (STATUS "		project			${PROJECT_NAME}			")
message (STATUS "		version			${NORTHWIND_VERSION}	")
message (STATUS "		spdlog-version	${SPDLOG_VERSION}		")
message (STATUS "		glm-version		${GLM_VERSION}			")
message (STATUS "===============================================")