cmake_minimum_required(VERSION 2.8.3)
project(gazebo_moos)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  tf_conversions
  robotx_gazebo
)

find_package(MOOS REQUIRED)

find_package(Boost 1.58 COMPONENTS thread system REQUIRED)
	
find_package(Eigen3 REQUIRED)
catkin_package(

)
find_path( MOOSIVP_SOURCE_TREE_BASE
           NAMES build-ivp.sh build-moos.sh configure-ivp.sh
           PATHS "$ENV{HOME}/moos-ivp"  "../../moos-ivp/trunk/" "../moos-ivp/trunk/"
           DOC "Base directory of the MOOS-IvP source tree"
           NO_DEFAULT_PATH
)
#=============================================================================
# Specify where to find IvP's headers and libraries...
#=============================================================================

FILE(GLOB IVP_INCLUDE_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/ivp/src/lib_* )
INCLUDE_DIRECTORIES(${IVP_INCLUDE_DIRS})

FILE(GLOB IVP_LIBRARY_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${IVP_LIBRARY_DIRS})


#===============================================================================
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(
# include
  ${MOOS_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${MOOS_LIBRARY_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

link_directories(${MOOS_LIBRARY_DIRS})
set(LIBS ${LIBS} ${MOOS_LIBRARIES})

INCLUDE(FindPackageMessage) 

message("----------------------------------------------")
if(MOOS_FOUND)
  message("MOOS FOUND!")
else(MOOS_FOUND)
  message("MOOS NOT FOUND")
endif(MOOS_FOUND)
message("----------------------------------------------")

add_executable(gazebo_wamv_alpha 
  src/gazebo_wamv_alpha.cpp
)

target_link_libraries(gazebo_wamv_alpha ${catkin_LIBRARIES})
target_link_libraries(gazebo_wamv_alpha MOOS)
target_link_libraries(gazebo_wamv_alpha ${Boost_LIBRARIES} ${Eigen_INCLUDE_DIRS})