import socket
from pathlib import Path

import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node

package_directory = Path(get_package_share_directory("sfg_experimental_area"))
local_namespace = "/local/" + socket.gethostname().replace("-", "_")
global_namespace = "/global/" + socket.gethostname().replace("-", "_")


def generate_launch_description():
    status_provider_node = Node(
        package="sfg_agent",
        executable="status_provider",
        namespace=local_namespace,
        name="status_provider",
        parameters=[
            package_directory / "config" / "status_provider.yaml",
            {
                "metadata_filepath": str(
                    package_directory / "config" / "agent_metadata.yaml"
                )
            },
        ],
        output="screen",
    )

    return launch.LaunchDescription([status_provider_node])
