cmake_minimum_required(VERSION 2.8.3)
project(usb_cam)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS image_transport roscpp std_msgs std_srvs sensor_msgs camera_info_manager)

## pkg-config libraries
##find_package(PkgConfig REQUIRED)
##pkg_check_modules(avcodec libavcodec REQUIRED)
##pkg_check_modules(swscale libswscale REQUIRED)
set(avutil_INCLUDE_DIRS  ffmpeg_build/include/libavutil)
set(avcodec_INCLUDE_DIRS ffmpeg_build/include/libavcodec)
set(swscale_INCLUDE_DIRS ffmpeg_build/include/libswscale)
set(ffmpeg_INCLUDE_DIRS  ffmpeg_build/include/)


###################################################
## Declare things to be passed to other projects ##
###################################################

## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
)

###########
## Build ##
###########
link_directories(
${catkin_LIB_DIRs} ffmpeg_build/lib/)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${avcodec_INCLUDE_DIRS}
  ${swscale_INCLUDE_DIRS}
)

## Build the USB camera library
add_library(${PROJECT_NAME} src/usb_cam.cpp)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES} libavutil.so
  ${catkin_LIBRARIES} libavcodec.so
  ${catkin_LIBRARIES} libswscale.so
)

## Declare a cpp executable
add_executable(${PROJECT_NAME}_node nodes/usb_cam_node.cpp)
target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}
  ${catkin_LIBRARIES} libavutil.so
  ${catkin_LIBRARIES} libavcodec.so
  ${catkin_LIBRARIES} libswscale.so
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}_node ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Copy launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  FILES_MATCHING PATTERN "*.launch"
)

install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
