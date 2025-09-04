#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_handle.hpp"

namespace sfg_experimental_area_visualization
{
    class Visualizer : public rclcpp::Node
    {
    public:
        Visualizer(const rclcpp::NodeOptions &options);

    private:
        rerun::RecordingStream m_recording_stream;

        std::map<std::string, std::vector<std::shared_ptr<message_visualizers::MessageVisualizerHandle>>> m_message_visualizers;
    };
}