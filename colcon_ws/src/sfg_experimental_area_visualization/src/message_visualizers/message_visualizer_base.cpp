#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_base.hpp"

namespace sfg_experimental_area_visualization::message_visualizers
{
    MessageVisualizerBase::MessageVisualizerBase(
        rerun::RecordingStream &recording_stream,
        const std::vector<std::string> &topic_names) : m_recording_stream(recording_stream), m_topic_names(topic_names)
    {
    }

    void MessageVisualizerBase::set_parameters(const std::vector<rclcpp::Parameter> &parameters)
    {
        (void)parameters;
    }

    void MessageVisualizerBase::declare_parameters() {}

    void MessageVisualizerBase::undeclare_parameters() {}

    void MessageVisualizerBase::set_timestamp(std::int32_t seconds, std::uint32_t nanosecs)
    {
        m_recording_stream.set_time_timestamp_secs_since_epoch("timestamp", seconds + nanosecs * 1e-9);
    }
}