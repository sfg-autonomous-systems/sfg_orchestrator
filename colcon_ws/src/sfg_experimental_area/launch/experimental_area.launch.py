import socket
from pathlib import Path

import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from sfg_utils import sanitize_hostname

package_directory = Path(get_package_share_directory("sfg_experimental_area"))
sanitized_hostname = sanitize_hostname(socket.gethostname())
local_namespace = "/local/"
global_namespace = "/global/" + sanitized_hostname


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
                parameters=[
                    package_directory / "config" / "agent_status_provider.yaml",
                ],
                extra_arguments=[{"use_intra_process_comms": True}],
            ),
            ComposableNode(
                package="sfg_agent",
                plugin="sfg_agent::AgentDiscoverer",
                namespace=local_namespace,
                parameters=[
                    package_directory / "config" / "agent_discoverer.yaml",
                ],
                extra_arguments=[{"use_intra_process_comms": True}],
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
                extra_arguments=[{"use_intra_process_comms": True}],
            ),
        ),
        output="screen",
    )

    return launch.LaunchDescription([experimental_area_container])
