import launch
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch_ros.substitutions import FindPackageShare
from rospkg import get_package_name
from sfg_utils import get_ros_namespaces

package_name = get_package_name(__file__)
local_namespace, global_namespace = get_ros_namespaces()


def generate_launch_description():
    experimental_area_container = ComposableNodeContainer(
        package="rclcpp_components",
        executable="component_container_mt",
        namespace=local_namespace,
        name="experimental_area_container",
        composable_node_descriptions=(
            ComposableNode(
                package="sfg_agent",
                plugin="sfg_agent::AgentStatusProvider",
                namespace=local_namespace,
                extra_arguments=[{"use_intra_process_comms": True}],
            ),
            ComposableNode(
                package="sfg_agent",
                plugin="sfg_agent::AgentDiscoverer",
                namespace=local_namespace,
                parameters=[
                    PathJoinSubstitution(
                        [
                            FindPackageShare(package_name),
                            "config",
                            "agent_discoverer.yaml",
                        ]
                    ),
                ],
            ),
            ComposableNode(
                package="sfg_agent",
                plugin="sfg_agent::AgentDecoder",
                namespace=local_namespace,
                parameters=[
                    PathJoinSubstitution(
                        [
                            FindPackageShare(package_name),
                            "config",
                            "agent_decoder.yaml",
                        ]
                    ),
                    {
                        "container_name": local_namespace
                        + "/experimental_area_container"
                    },
                ],
            ),
        ),
        output="screen",
    )

    return launch.LaunchDescription([experimental_area_container])
