#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

namespace sfg_experimental_area_visualization::message_visualizers
{
    class MessageVisualizerHandle;

    class MessageVisualizerBase
    {
    public:
        virtual void clear(bool recursive = true) = 0;
        virtual void set_parameters(const std::vector<rclcpp::Parameter> &parameters);

    protected:
        MessageVisualizerBase(rerun::RecordingStream &recording_stream, const std::vector<std::string> &topic_names);
        virtual void declare_parameters();
        virtual void undeclare_parameters();
        void set_timestamp(std::int32_t seconds, std::uint32_t nanosecs);

        rerun::RecordingStream &m_recording_stream;
        std::vector<std::string> m_topic_names;

        friend class MessageVisualizerHandle;
    };
}