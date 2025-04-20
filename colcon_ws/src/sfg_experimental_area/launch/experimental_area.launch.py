import socket
from pathlib import Path

import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from sfg_utils import sanitize_hostname

package_directory = Path(get_package_share_directory("sfg_experimental_area"))
sanitized_hostname = sanitize_hostname(socket.gethostname())
local_namespace = "/local/" + sanitized_hostname
global_namespace = "/global/" + sanitized_hostname


def generate_launch_description():
    agent_status_provider_node = Node(
        package="sfg_agent",
        executable="agent_status_provider",
        namespace=local_namespace,
        name="agent_status_provider",
        parameters=[
            package_directory / "config" / "agent_status_provider.yaml",
        ],
        output="screen",
    )

    return launch.LaunchDescription([agent_status_provider_node])
