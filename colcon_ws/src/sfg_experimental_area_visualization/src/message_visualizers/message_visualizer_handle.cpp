#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_handle.hpp"

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_factory.hpp"

#include <rerun/archetypes/clear.hpp>

namespace sfg_experimental_area_visualization::message_visualizers
{
    MessageVisualizerHandle::MessageVisualizerHandle(
        rerun::RecordingStream &recording_stream,
        rclcpp::Node &node,
        const std::vector<TopicInfo> &topics,
        const rclcpp::QoS &qos) : m_implementation(MessageVisualizerFactory::instance().create(recording_stream,
                                                                                               node,
                                                                                               topics,
                                                                                               qos))
    {
    }

    MessageVisualizerHandle::~MessageVisualizerHandle()
    {
        m_implementation->clear();
        m_implementation->undeclare_parameters();
    }

    void MessageVisualizerHandle::clear(bool recursive)
    {
        m_implementation->clear(recursive);
    }

    void MessageVisualizerHandle::set_parameters(const std::vector<rclcpp::Parameter> &parameters)
    {
        m_implementation->set_parameters(parameters);
    }
}