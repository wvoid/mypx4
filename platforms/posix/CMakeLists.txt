
include_directories(${CMAKE_CURRENT_BINARY_DIR})

get_property(module_libraries GLOBAL PROPERTY PX4_MODULE_LIBRARIES)

# When building with catkin, do not change CMAKE_RUNTIME_OUTPUT_DIR from
# CMAKE_CURRENT_BINARY_DIR ''./platforms/posix' to './bin'
if (NOT CATKIN_DEVEL_PREFIX)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
endif()

set(PX4_SHELL_COMMAND_PREFIX "px4-")

add_definitions("-DPX4_SHELL_COMMAND_PREFIX=\"${PX4_SHELL_COMMAND_PREFIX}\"")

px4_posix_generate_builtin_commands(
	OUT apps
	MODULE_LIST ${module_libraries})

px4_posix_generate_alias(
	OUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/px4-alias.sh
	MODULE_LIST ${module_libraries}
	PREFIX ${PX4_SHELL_COMMAND_PREFIX}
)

if (CMAKE_BUILD_TYPE STREQUAL FuzzTesting)
	add_executable(px4
		src/px4/common/main_fuzztesting.cpp
		apps.cpp
		)
else()
	add_definitions(-DPX4_SOURCE_DIR="${PX4_SOURCE_DIR}" -DPX4_BINARY_DIR="${PX4_BINARY_DIR}")

	add_executable(px4
		src/px4/common/main.cpp
		apps.cpp
		)
endif()

target_link_libraries(px4
	PRIVATE
		${module_libraries}
		m
		parameters
)

if((NOT APPLE) AND (NOT ANDROID))
	target_link_libraries(px4 PRIVATE rt)
endif()

if(NOT ANDROID)
	target_link_libraries(px4 PRIVATE pthread)
endif()

target_link_libraries(px4 PRIVATE uORB)

if (CMAKE_BUILD_TYPE STREQUAL FuzzTesting)
	target_include_directories(px4 PRIVATE SYSTEM "${CMAKE_BINARY_DIR}/mavlink}")
	target_compile_options(px4 PRIVATE "-Wno-cast-align")
endif()

#=============================================================================
# install
#

# TODO: extend to snapdragon

# px4 dirs
install(
	DIRECTORY
		${PROJECT_SOURCE_DIR}/posix-configs
		${PROJECT_SOURCE_DIR}/test
		${CMAKE_BINARY_DIR}/etc
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	DESTINATION
		${PROJECT_NAME}
	USE_SOURCE_PERMISSIONS
)

# Module Symlinks
px4_posix_generate_symlinks(
	MODULE_LIST ${module_libraries}
	PREFIX ${PX4_SHELL_COMMAND_PREFIX}
	TARGET px4
)

if(config_romfs_root)
	add_subdirectory(${PX4_SOURCE_DIR}/ROMFS ${PX4_BINARY_DIR}/ROMFS)
	add_dependencies(px4 romfs_gen_files_target)
endif()


# board defined upload helper
if(EXISTS "${PX4_BOARD_DIR}/cmake/upload.cmake")
	include(${PX4_BOARD_DIR}/cmake/upload.cmake)
endif()


if("${PX4_BOARD}" MATCHES "beaglebone_blue")
	target_link_libraries(px4 PRIVATE robotics_cape)

elseif("${PX4_BOARD}" MATCHES "emlid_navio2")
	target_link_libraries(px4 PRIVATE atomic)

	# vscode launch.json
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/launch_rpi.json.in ${PX4_SOURCE_DIR}/.vscode/launch.json COPYONLY)

elseif("${PX4_BOARD}" MATCHES "sitl")

	# vscode launch.json
	if(${PX4_BOARD_LABEL} MATCHES "replay")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/launch_replay.json.in ${PX4_SOURCE_DIR}/.vscode/launch.json COPYONLY)

	elseif(${PX4_CONFIG} MATCHES "px4_sitl_ign")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/launch_sitl_ignition.json.in ${PX4_SOURCE_DIR}/.vscode/launch.json COPYONLY)

	else()
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/launch_sitl_default.json.in ${PX4_SOURCE_DIR}/.vscode/launch.json COPYONLY)
	endif()

	set(SITL_WORKING_DIR ${PX4_BINARY_DIR}/rootfs)
	file(MAKE_DIRECTORY ${SITL_WORKING_DIR})
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/posix.lldbinit ${SITL_WORKING_DIR}/.lldbinit COPYONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/posix.gdbinit ${SITL_WORKING_DIR}/.gdbinit COPYONLY)

	if(BUILD_TESTING)
		include(sitl_tests)
	endif()

	# install

	# px4 dirs
	install(
		DIRECTORY
			${PROJECT_SOURCE_DIR}/integrationtests
			${PROJECT_SOURCE_DIR}/launch
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
		DESTINATION
			${PROJECT_NAME}
		USE_SOURCE_PERMISSIONS
		)

	# px4 files
	install(
		FILES
			${PROJECT_SOURCE_DIR}/CMakeLists.txt
			${PROJECT_SOURCE_DIR}/package.xml
		DESTINATION
			${PROJECT_NAME}
		)

	# px4 Tools dirs
	install(
		DIRECTORY
			${PROJECT_SOURCE_DIR}/Tools/ecl_ekf
		DESTINATION
			${PROJECT_NAME}/Tools
		USE_SOURCE_PERMISSIONS
		)

	# px4 Tools files
	install(
		PROGRAMS
			${PROJECT_SOURCE_DIR}/Tools/simulation/gazebo/setup_gazebo.bash
			${PROJECT_SOURCE_DIR}/Tools/upload_log.py
		DESTINATION
			${PROJECT_NAME}/Tools
		)

	# ROMFS files
	install(
		DIRECTORY
			${PX4_BINARY_DIR}/etc
		DESTINATION
			${PROJECT_NAME}/build/px4_sitl_default
		)

	# sitl_gazebo built plugins
	install(
		DIRECTORY
			${PX4_BINARY_DIR}/build_gazebo
		DESTINATION
			${PROJECT_NAME}/build/px4_sitl_default
		FILES_MATCHING
			PATTERN "CMakeFiles" EXCLUDE
			PATTERN "*.so"
		)

	# sitl_gazebo dirs
	install(
		DIRECTORY
			${PROJECT_SOURCE_DIR}/Tools/simulation/gazebo/sitl_gazebo/models
			${PROJECT_SOURCE_DIR}/Tools/simulation/gazebo/sitl_gazebo/worlds
		DESTINATION
			${PROJECT_NAME}/Tools/simulation/gazebo/sitl_gazebo
		)

	# sitl_gazebo files
	install(
		FILES
			${PROJECT_SOURCE_DIR}/Tools/simulation/gazebo/sitl_gazebo/CMakeLists.txt
			${PROJECT_SOURCE_DIR}/Tools/simulation/gazebo/sitl_gazebo/package.xml
		DESTINATION
			${PROJECT_NAME}/Tools/simulation/gazebo/sitl_gazebo
		)

endif()
