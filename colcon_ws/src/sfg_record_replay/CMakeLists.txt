cmake_minimum_required(VERSION 3.8)
project(sfg_record_replay)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ########################################################################################################
# Find dependencies.                                                                                     #
# ########################################################################################################
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sfg_utils REQUIRED)

# ########################################################################################################
# Add nodes and libraries.                                                                               #
# ########################################################################################################
sfg_utils__add_component("trajectory_recorder" "${PROJECT_NAME}::TrajectoryRecorder"
    SOURCES
    "src/trajectory_recorder_component.cpp"
    "src/trajectory_recorder.cpp"
    AMENT_DEPENDENCIES
    rclcpp
    rclcpp_components
    sfg_utils
)

sfg_utils__add_component("trajectory_replayer" "${PROJECT_NAME}::TrajectoryReplayer"
    SOURCES
    "src/trajectory_replayer_component.cpp"
    "src/trajectory_replayer.cpp"
    AMENT_DEPENDENCIES
    rclcpp
    rclcpp_components
    sfg_utils
)

# ########################################################################################################
# Add other files/directories.                                                                           #
# ########################################################################################################
install(DIRECTORY
    "config"
    "launch"
    DESTINATION "share/${PROJECT_NAME}/"
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