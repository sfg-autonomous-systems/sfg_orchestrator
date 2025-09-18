import launch
import sfg_utils.launch_utils
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch_ros.substitutions import FindPackageShare
from rospkg import get_package_name
from sfg_utils.fqn import RosFqnBuilder, RosFqnSegment, Scope

package_name = get_package_name(__file__)
local_namespace, global_namespace = (
    RosFqnBuilder()
    .scope(Scope.Local)
    .agent()
    .build(begin=RosFqnSegment.Scope, end=RosFqnSegment.Agent),
    RosFqnBuilder()
    .scope(Scope.Global)
    .agent()
    .build(begin=RosFqnSegment.Scope, end=RosFqnSegment.Agent),
)


def generate_launch_description() -> launch.LaunchDescription:
    agent_nodes, agent_composable_nodes = sfg_utils.launch_utils.get_nodes(
        "sfg_agent", "agent.launch.py"
    )

    agent_discoverer_node = ComposableNode(
        package="sfg_agent",
        plugin="sfg_agent::Discoverer",
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
    )

    agent_decoder_node = ComposableNode(
        package="sfg_agent",
        plugin="sfg_agent::Decoder",
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
                "container_name": f"{local_namespace}/bringup_container",
            },
        ],
    )

    return launch.LaunchDescription(
        [
            *agent_nodes,
            ComposableNodeContainer(
                package="rclcpp_components",
                executable="component_container_mt",
                namespace=local_namespace,
                name="bringup_container",
                composable_node_descriptions=(
                    *agent_composable_nodes,
                    agent_discoverer_node,
                    agent_decoder_node,
                ),
                output="screen",
            ),
        ]
    )
