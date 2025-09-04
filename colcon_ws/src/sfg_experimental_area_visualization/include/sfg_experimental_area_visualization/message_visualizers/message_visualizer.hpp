#pragma once

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_base.hpp"

namespace sfg_experimental_area_visualization::message_visualizers
{
    template <typename... MsgTypes>
    class MessageVisualizer : public MessageVisualizerBase
    {
    public:
        using MsgTypesTuple = std::tuple<MsgTypes...>;

        MessageVisualizer(
            rerun::RecordingStream &recording_stream,
            rclcpp::Node &node,
            const std::vector<std::string> &topic_names,
            const rclcpp::QoS &qos);

    protected:
        virtual void callback(const typename MsgTypes::ConstSharedPtr &...msgs) = 0;

        using SyncPolicy = message_filters::sync_policies::ApproximateTime<MsgTypes...>;
        using Synchronizer = message_filters::Synchronizer<SyncPolicy>;

        std::tuple<message_filters::Subscriber<MsgTypes>...> m_subscribers;
        std::shared_ptr<Synchronizer> m_synchronizer;

    private:
        template <size_t... Is>
        void initialize_subscribers(rclcpp::Node &node, const std::vector<std::string> &topics, const rclcpp::QoS &qos, std::index_sequence<Is...>);

        template <size_t... Is>
        void register_callback(std::index_sequence<Is...>);
    };
}

namespace sfg_experimental_area_visualization::message_visualizers
{
    template <typename MsgType>
    class MessageVisualizer<MsgType> : public MessageVisualizerBase
    {
    public:
        using MsgTypesTuple = std::tuple<MsgType>;

        MessageVisualizer(
            rerun::RecordingStream &stream,
            rclcpp::Node &node,
            const std::vector<std::string> &topic_names,
            const rclcpp::QoS &qos);

    protected:
        virtual void callback(const typename MsgType::ConstSharedPtr &msg) = 0;

        typename rclcpp::Subscription<MsgType>::SharedPtr m_subscriber;
    };
}

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer.tpp"