from pathlib import Path

import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from sfg_utils import get_agent_name, sanitize_agent_name

package_directory = Path(get_package_share_directory("sfg_experimental_area"))
sanitized_agent_name = sanitize_agent_name(get_agent_name())
local_namespace = "/local"
global_namespace = "/global/" + sanitized_agent_name


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
                    package_directory / "config" / "agent_discoverer.yaml",
                ],
            ),
            ComposableNode(
                package="sfg_agent",
                plugin="sfg_agent::AgentDecoder",
                namespace=local_namespace,
                parameters=[
                    package_directory / "config" / "agent_decoder.yaml",
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
