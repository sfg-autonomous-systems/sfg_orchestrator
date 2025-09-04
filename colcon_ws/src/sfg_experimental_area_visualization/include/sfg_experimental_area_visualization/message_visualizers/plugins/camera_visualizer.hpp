#pragma once

#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer.hpp"

namespace sfg_experimental_area_visualization::message_visualizers::plugins
{
    class CameraVisualizer : public MessageVisualizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image>
    {
    public:
        using MessageVisualizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image>::MessageVisualizer;

    private:
        void callback(const sensor_msgs::msg::CameraInfo::ConstSharedPtr &camera_info_msg, const sensor_msgs::msg::Image::ConstSharedPtr &image_msg) override;
        void clear(bool recursive) override;
    };
}