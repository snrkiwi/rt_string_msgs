cmake_minimum_required(VERSION 2.8.3)
project(rt_string_msgs)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
)

## Find Orocos RTT and plugins
find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-scripting rtt-marshalling rtt-transport-mqueue rtt-transport-corba)
if (NOT OROCOS-RTT_FOUND)
  message(FATAL_ERROR "\n   RTT not found. Is the version correct? Use the CMAKE_PREFIX_PATH cmake or environment variable to point to the installation directory of RTT.")
else()
  include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
  #add_definitions( -DRTT_COMPONENT )
endif()

## find catkin and catkin dependencies
find_package(catkin REQUIRED COMPONENTS rtt_roscomm)
catkin_destinations()

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  rt_string.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS std_msgs message_runtime
)

###########
## Build ##
###########

## Language: cpp
if(TARGET ${PROJECT_NAME}_generate_messages_cpp)
  ## Overwrite generated header files in devel-space
  file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h"
  )

## Build options
# mqueue transport
OPTION(ENABLE_MQ "Build posix message queue transport plugin for ${_package}" OFF)
if(ENABLE_MQ)
  if (OROCOS-RTT_MQUEUE_FOUND)
    message(STATUS "Building MQueue transport plugin for ROS messages in package ${_package} with ${OROCOS-RTT_MQUEUE_LIBRARIES}")
  else()
    message(WARNING "Disabled built of posix message queue transport plugin for ${_package} because the RTT mqueue plugin could not be found.")
    set(ENABLE_MQ OFF CACHE BOOL "Build posix message queue transport plugin for ${_package} (forced to OFF)" FORCE)
  endif()
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

## Build typekit and transport plugins
include_directories(
  include
  include/orocos
  ${catkin_INCLUDE_DIRS}
)

# Build typekit plugin
orocos_typekit(rtt-rt_string_msgs-ros-transport
  src/ros_rt_string_msgs_transport.cpp
)
target_link_libraries(rtt-rt_string_msgs-ros-transport ${catkin_LIBRARIES})

  configure_file(cmake/rename_generated_header_files.cmake.in cmake/rename_generated_header_files.cmake @ONLY)
  add_custom_target(${PROJECT_NAME}_rename_generated_header_files
    DEPENDS ${HEADERS}
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/rename_generated_header_files.cmake
    COMMENT "Moving generated C++ header files to include/${PROJECT_NAME}/generated/."
  )
  add_dependencies(${PROJECT_NAME}_rename_generated_header_files ${PROJECT_NAME}_generate_messages_cpp)
  add_dependencies(${PROJECT_NAME}_generate_messages ${PROJECT_NAME}_rename_generated_header_files)
endif()

# Build mqueue transport plugin
if(ENABLE_MQ)
  orocos_typekit(rtt-rt_string_msgs-ros-transport-mqueue
    ${rtt-kdl_msgs-ros-transport-mqueue_SOURCES}
  )
  target_link_libraries(rtt-rt_string_msgs-ros-transport-mqueue ${catkin_LIBRARIES} ${OROCOS-RTT_MQUEUE_LIBRARIES})
endif()

# Add an explicit dependency between the typekits and message files
# TODO: Add deps for all msg dependencies
if(boost_date_time_msgs_EXPORTED_TARGETS)
  if(NOT boost_date_time_msgs STREQUAL ${PROJECT_NAME})
    add_dependencies(rtt-rt_string_msgs-ros-transport ${boost_date_time_msgs_EXPORTED_TARGETS})
    if(TARGET rtt-rt_string_msgs-ros-transport-mqueue)
      add_dependencies(rtt-rt_string_msgs-ros-transport-mqueue ${boost_date_time_msgs_EXPORTED_TARGETS})
    endif()
  endif()
endif()

## Language: Python
# TODO

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark cpp header files for installation
install(FILES
  include/${PROJECT_NAME}/rt_string.h
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(DIRECTORY include/${PROJECT_NAME}/boost
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

## Install headers
install(
  DIRECTORY include/orocos
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
)

## Generate Orocos package
orocos_generate_package(
  DEPENDS rt_string_msgs
  DEPENDS_TARGETS rtt_roscomm rtt_std_msgs
)
