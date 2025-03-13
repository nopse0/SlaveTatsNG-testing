cmake_minimum_required(VERSION 3.21)

project(
	SlaveTatsNG-interfacetest
	VERSION 0.0.1
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# ########################################################################################################################
# ## Build options
# ########################################################################################################################

# #######################################################################################################################
# # Add CMake features
# #######################################################################################################################
include(XSEPlugin)

# #######################################################################################################################
# # Find dependencies
# #######################################################################################################################
#find_package(magic_enum CONFIG REQUIRED)
#find_package(xbyak CONFIG REQUIRED)
#find_package(nlohmann_json CONFIG REQUIRED)
#find_path(CLIB_UTIL_INCLUDE_DIRS "ClibUtil/utils.hpp")

#target_include_directories(
#	${PROJECT_NAME}
#	#PRIVATE
#	#${CLIB_UTIL_INCLUDE_DIRS}
#)

#target_link_libraries(
#	${PROJECT_NAME}
#	PRIVATE
#	magic_enum::magic_enum
#	xbyak::xbyak
#	nlohmann_json::nlohmann_json
#)
