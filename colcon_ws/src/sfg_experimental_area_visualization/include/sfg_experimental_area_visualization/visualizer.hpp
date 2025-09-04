#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_handle.hpp"
#include "sfg_agent_msgs/msg/agent_discovery_event.hpp"

namespace sfg_experimental_area_visualization
{
    class Visualizer : public rclcpp::Node
    {
    public:
        Visualizer(const rclcpp::NodeOptions &options);

    private:
        void agent_discovery_event_callback(
            const sfg_agent_msgs::msg::AgentMetadata &metadata,
            uint8_t event_type);

        rerun::RecordingStream m_recording_stream;

        rclcpp::Subscription<sfg_agent_msgs::msg::AgentDiscoveryEvent>::SharedPtr m_agent_discovery_event_subscriber;
        std::map<std::string, std::vector<std::shared_ptr<message_visualizers::MessageVisualizerHandle>>> m_message_visualizers;
    };
}