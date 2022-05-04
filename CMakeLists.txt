cmake_minimum_required(VERSION 3.5.1)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

project(Avtoplanovik-300 LANGUAGES CXX)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
	${PROJECT_NAME}
		${_BASE_DIR}/defines/Defines.h
		${_BASE_DIR}/utils/ReadWriteFile.h
		${_BASE_DIR}/utils/PlanGeneratorUtils.h
		${_BASE_DIR}/entities/Conche.h
		${_BASE_DIR}/entities/Mass.h
		${_BASE_DIR}/PlanGenerator.h

		${_BASE_DIR}/utils/ReadWriteFile.cpp
		${_BASE_DIR}/utils/PlanGeneratorUtils.cpp
		${_BASE_DIR}/entities/Conche.cpp
		${_BASE_DIR}/entities/Mass.cpp
		${_BASE_DIR}/PlanGenerator.cpp
		${_BASE_DIR}/Main.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${_BASE_DIR}
)