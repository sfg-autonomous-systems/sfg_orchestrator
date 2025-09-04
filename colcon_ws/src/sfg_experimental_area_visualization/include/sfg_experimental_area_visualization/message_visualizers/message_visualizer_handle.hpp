#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_base.hpp"
#include "sfg_experimental_area_visualization/message_visualizers/topic_info.hpp"

namespace sfg_experimental_area_visualization::message_visualizers
{
    class MessageVisualizerHandle
    {
    public:
        MessageVisualizerHandle(
            rerun::RecordingStream &recording_stream,
            rclcpp::Node &node,
            const std::vector<TopicInfo> &topics,
            const rclcpp::QoS &qos);

        ~MessageVisualizerHandle();
        void clear(bool recursive = true);
        void set_parameters(const std::vector<rclcpp::Parameter> &parameters);

    private:
        std::unique_ptr<MessageVisualizerBase> m_implementation;
    };
}