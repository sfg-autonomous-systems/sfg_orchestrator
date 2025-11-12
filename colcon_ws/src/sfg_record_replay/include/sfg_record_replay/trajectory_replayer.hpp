#pragma once

#include <rclcpp/rclcpp.hpp>

namespace sfg_record_replay
{
    class TrajectoryReplayer : public rclcpp::Node
    {
    public:
        TrajectoryReplayer(const rclcpp::NodeOptions &options);
    };
}