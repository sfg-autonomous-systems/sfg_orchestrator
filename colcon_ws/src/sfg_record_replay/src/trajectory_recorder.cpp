#include "sfg_record_replay/trajectory_recorder.hpp"

namespace sfg_record_replay
{
    TrajectoryRecorder::TrajectoryRecorder(const rclcpp::NodeOptions &options) : Node("trajectory_recorder", options)
    {
        RCLCPP_INFO(this->get_logger(), "Started trajectory recorder.");
    }
}