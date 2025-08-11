import launch
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch_ros.substitutions import FindPackageShare
from rospkg import get_package_name
from sfg_utils.fqn import RosFQNBuilder, RosFQNSegment, Scope

package_name = get_package_name(__file__)
local_namespace, global_namespace = (
    RosFQNBuilder().scope(Scope.Local).agent().build(end=RosFQNSegment.Agent),
    RosFQNBuilder().scope(Scope.Global).agent().build(end=RosFQNSegment.Agent),
)


def generate_launch_description():
    bringup_container = ComposableNodeContainer(
        package="rclcpp_components",
        executable="component_container_mt",
        namespace=local_namespace,
        name=f"{package_name}_bringup_container",
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
                extra_arguments=[{"use_intra_process_comms": True}],
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
                    {"container_name": local_namespace + f"/{package_name}_container"},
                ],
            ),
        ),
        output="screen",
    )

    return launch.LaunchDescription([bringup_container])
