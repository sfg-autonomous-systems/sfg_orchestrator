#include "sfg_experimental_area_visualization/message_visualizers/plugins/point_cloud2_visualizer.hpp"

#include <rerun/archetypes/clear.hpp>

namespace sfg_experimental_area_visualization::message_visualizers::plugins
{
    void PointCloud2Visualizer::callback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg)
    {
        std::uint32_t x_offset = 0, y_offset = 0, z_offset = 0;

        for (const auto &field : msg->fields)
        {
            if (field.name == "x")
            {
                x_offset = field.offset;
            }
            else if (field.name == "y")
            {
                y_offset = field.offset;
            }
            else if (field.name == "z")
            {
                z_offset = field.offset;
            }
        }

        std::vector<rerun::Position3D> points(msg->width * msg->height);

        for (size_t row = 0; row < msg->height; row++)
        {
            for (size_t column = 0; column < msg->width; column++)
            {
                auto point_offset = row * msg->row_step + column * msg->point_step;

                rerun::Position3D position;
                std::memcpy(&position.xyz.xyz[0], &msg->data[point_offset + x_offset], sizeof(float));
                std::memcpy(&position.xyz.xyz[1], &msg->data[point_offset + y_offset], sizeof(float));
                std::memcpy(&position.xyz.xyz[2], &msg->data[point_offset + z_offset], sizeof(float));
                points[row * msg->width + column] = position;
            }
        }
        set_timestamp(msg->header.stamp.sec, msg->header.stamp.nanosec);
        m_recording_stream.log(m_topic_names[0].c_str(), rerun::Points3D(points));
    }

    void PointCloud2Visualizer::clear(bool recursive)
    {
        m_recording_stream.log(m_topic_names[0].c_str(), rerun::archetypes::Clear(recursive));
    }
}

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_factory.hpp"

SFG_EXPERIMENTAL_AREA_VISUALIZATION__REGISTER_MESSAGE_VISUALIZER(sfg_experimental_area_visualization::message_visualizers::plugins::PointCloud2Visualizer)