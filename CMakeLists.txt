cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project("NorthwindEngine" CXX C)

set (NORTHWIND_MAJOR 0)
set (NORTHWIND_MINOR 0)
set (NORTHWIND_PATCH 1)
set (NORTHWIND_VERSION "${NORTHWIND_MAJOR}.${NORTHWIND_MINOR}.${NORTHWIND_PATCH}")

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory (src)
