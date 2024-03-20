cmake_minimum_required(VERSION 3.0.2)
project(rosneuro_windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(ROSNEURO_DATA_MIN_VERSION "1.0.0")

##############################################################################
# Find dependencies
##############################################################################


find_package(catkin REQUIRED COMPONENTS 
			 roscpp 
			 roslib
			 rosconsole
			 std_msgs
			 pluginlib
       rosneuro_filters)

find_package(Eigen3 REQUIRED)
find_package(PkgConfig)
find_package(GTest REQUIRED)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(${catkin_INCLUDE_DIRS} 
                    ${EIGEN3_INCLUDE_DIRS}
          include)


##############################################################################
# Define package
##############################################################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES 
  ${PROJECT_NAME}
	
  CATKIN_DEPENDS
  	roscpp
    rosneuro_filters
	roslib
  DEPENDS
)

##############################################################################
# Test
##############################################################################

catkin_add_gtest(TestWindow test/TestWindow.cpp)
target_link_libraries(TestWindow ${GTEST_BOTH_LIBRARIES} pthread gmock)
target_link_libraries(TestWindow ${PROJECT_NAME} ${catkin_LIBRARIES})

##############################################################################
# Build
##############################################################################

include_directories(${catkin_INCLUDE_DIRS} 
                    ${EIGEN3_INCLUDE_DIRS}
					include)

add_definitions(${EIGEN3_DEFINITIONS})

add_library(${PROJECT_NAME} src/Window.cpp)

target_link_libraries(${PROJECT_NAME} ${Eigen3_LIBRARIES} 
									  ${catkin_LIBRARIES})


