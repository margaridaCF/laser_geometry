cmake_minimum_required(VERSION 2.8.3)
project(laser_free_to_cloud)

find_package(catkin REQUIRED
    COMPONENTS
        angles
        cmake_modules
        roscpp
        sensor_msgs
        tf
        tf2
)

find_package(Boost REQUIRED COMPONENTS system thread)

find_package(Eigen REQUIRED)

catkin_python_setup()

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES laser_free_to_cloud
  DEPENDS Boost Eigen
)

include_directories(include
    ${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${Eigen_INCLUDE_DIRS}
)

add_library(laser_free_to_cloud src/laser_geometry.cpp)
target_link_libraries(laser_free_to_cloud ${Boost_LIBRARIES} ${tf_LIBRARIES})


add_executable(free_cloud_node src/free_cloud_node.cpp)
target_link_libraries(free_cloud_node
  ${catkin_LIBRARIES} laser_free_to_cloud
)

add_executable(laser_scan_to_cloud_node src/laser_scan_to_cloud_node.cpp)
target_link_libraries(laser_scan_to_cloud_node
  ${catkin_LIBRARIES} laser_free_to_cloud
)

if(CATKIN_ENABLE_TESTING)
  catkin_add_gtest(projection_test test/projection_test.cpp)
  target_link_libraries(projection_test laser_free_to_cloud)
  catkin_add_nosetests(test/projection_test.py)
endif()

install(TARGETS laser_free_to_cloud
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})
install(DIRECTORY include/laser_geometry/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
