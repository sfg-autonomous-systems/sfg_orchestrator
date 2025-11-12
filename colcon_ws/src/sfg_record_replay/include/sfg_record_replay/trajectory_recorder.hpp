#pragma once

#include <rclcpp/rclcpp.hpp>

namespace sfg_record_replay
{
    class TrajectoryRecorder : public rclcpp::Node
    {
    public:
        TrajectoryRecorder(const rclcpp::NodeOptions &options);
    };
}