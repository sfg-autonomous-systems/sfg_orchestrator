#include "sfg_experimental_area_visualization/visualizer.hpp"

namespace sfg_experimental_area_visualization
{
    Visualizer::Visualizer(const rclcpp::NodeOptions &options) : Node("visualizer", options), m_recording_stream("visualizer")
    {
        // Declare and retrieve ROS parameters.
        if (declare_parameter("spawn_viewer", true))
        {
            m_recording_stream.spawn().exit_on_failure();
        }

        // Just for forcing the compiler to generate the template code.
        auto point_cloud_visualizer = message_visualizers::MessageVisualizerHandle(
            m_recording_stream,
            *this,
            {{"/points", "sensor_msgs/msg/PointCloud2"}},
            rclcpp::SensorDataQoS());

        auto camera_visualizer = message_visualizers::MessageVisualizerHandle(
            m_recording_stream,
            *this,
            {{"/camera_info", "sensor_msgs/msg/CameraInfo"}, {"/image", "sensor_msgs/msg/Image"}},
            rclcpp::SensorDataQoS());
    }

    void Visualizer::agent_discovery_event_callback(const sfg_agent_msgs::msg::AgentMetadata &metadata, uint8_t event_type)
    {
        switch (event_type)
        {
        case sfg_agent_msgs::msg::AgentDiscoveryEvent::DISCOVERED:
        {
            break;
        }
        case sfg_agent_msgs::msg::AgentDiscoveryEvent::LOST:
        {
            break;
        }
        }
    }
}