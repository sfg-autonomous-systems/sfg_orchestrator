import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    example_container = ComposableNodeContainer(
        package="rclcpp_components",
        executable="component_container",
        name="example_container",
        namespace="example_namespace",
        composable_node_descriptions=(
            ComposableNode(
                package="isaac_ros_h264_decoder",
                plugin="nvidia::isaac_ros::h264_decoder::DecoderNode",
                remappings=[
                    (
                        "image_compressed",
                        "/global/sfg_go2_01/camera_head/color_compressed",
                    )
                ],
            ),
        ),
        output="screen",
    )

    return launch.LaunchDescription([example_container])
