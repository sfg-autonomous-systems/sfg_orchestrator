#pragma once

#include <sensor_msgs/msg/point_cloud2.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer.hpp"

namespace sfg_experimental_area_visualization::message_visualizers::plugins
{
    class PointCloud2Visualizer : public MessageVisualizer<sensor_msgs::msg::PointCloud2>
    {
    public:
        using MessageVisualizer<sensor_msgs::msg::PointCloud2>::MessageVisualizer;

    private:
        void callback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg) override;
        void clear(bool recursive) override;
    };
}