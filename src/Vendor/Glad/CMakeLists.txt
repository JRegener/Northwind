project (glad)

file (GLOB_RECURSE SOURCE_FILES "*.cpp" "*c")
file (GLOB_RECURSE HEADER_FILES "*.h")

add_library (glad STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE CXX)