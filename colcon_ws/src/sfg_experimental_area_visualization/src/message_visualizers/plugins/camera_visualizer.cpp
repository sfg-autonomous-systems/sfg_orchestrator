#include "sfg_experimental_area_visualization/message_visualizers/plugins/camera_visualizer.hpp"

namespace sfg_experimental_area_visualization::message_visualizers::plugins
{
    void CameraVisualizer::callback(const sensor_msgs::msg::CameraInfo::ConstSharedPtr &camera_info_msg, const sensor_msgs::msg::Image::ConstSharedPtr &image_msg)
    {
        (void)camera_info_msg;
        (void)image_msg;

        // ToDo: Implement this.
    }

    void CameraVisualizer::clear(bool recursive)
    {
        (void)recursive;

        // ToDo: Implement this.
    }
}

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_factory.hpp"

SFG_EXPERIMENTAL_AREA_VISUALIZATION__REGISTER_MESSAGE_VISUALIZER(sfg_experimental_area_visualization::message_visualizers::plugins::CameraVisualizer)