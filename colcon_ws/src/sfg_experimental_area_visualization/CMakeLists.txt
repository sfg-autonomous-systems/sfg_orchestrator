cmake_minimum_required(VERSION 3.8)
project(sfg_experimental_area_visualization)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ########################################################################################################
# Find dependencies.                                                                                     #
# ########################################################################################################
find_package(ament_cmake REQUIRED)
find_package(message_filters REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(sfg_agent_msgs REQUIRED)
find_package(sfg_utils REQUIRED)

include(FetchContent)
FetchContent_Declare(rerun_sdk
  URL "https://github.com/rerun-io/rerun/releases/download/0.24.1/rerun_cpp_sdk.zip")
FetchContent_MakeAvailable(rerun_sdk)
set_target_properties(rerun_sdk PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

# ########################################################################################################
# Add nodes and libraries.                                                                               #
# ########################################################################################################
sfg_utils__add_component("visualizer" "${PROJECT_NAME}::Visualizer"
  SOURCES
  "src/message_visualizers/camera_visualizer.cpp"
  "src/message_visualizers/message_visualizer_handle.cpp"
  "src/message_visualizers/message_visualizer_base.cpp"
  "src/message_visualizers/message_visualizer_factory.cpp"
  "src/message_visualizers/point_cloud2_visualizer.cpp"
  "src/visualizer.cpp"
  "src/visualizer_component.cpp"
  AMENT_DEPENDENCIES
  message_filters
  rclcpp
  rclcpp_components
  sensor_msgs
  sfg_agent_msgs
  sfg_utils
  SYSTEM_DEPENDENCIES
  PRIVATE rerun_sdk
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  # The following line skips the linter which checks for copyrights.
  # Comment the line when a copyright and license is added to all source files.
  set(ament_cmake_copyright_FOUND TRUE)

  # The following line skips cpplint (only works in a git repo).
  # Comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files.
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()