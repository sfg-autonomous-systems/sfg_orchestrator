#include "sfg_record_replay/trajectory_replayer.hpp"

namespace sfg_record_replay
{
    TrajectoryReplayer::TrajectoryReplayer(const rclcpp::NodeOptions &options) : Node("trajectory_replayer", options)
    {
        RCLCPP_INFO(this->get_logger(), "Started trajectory replayer.");
    }
}