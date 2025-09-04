#pragma once

#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_base.hpp"
#include "sfg_experimental_area_visualization/message_visualizers/topic_info.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>

#define SFG_EXPERIMENTAL_AREA_VISUALIZATION__REGISTER_MESSAGE_VISUALIZER(MessageVisualizer)                                                 \
    namespace                                                                                                                               \
    {                                                                                                                                       \
        template <typename Tuple, std::size_t... Is>                                                                                        \
        std::vector<std::string> get_msg_types_impl(std::index_sequence<Is...>)                                                             \
        {                                                                                                                                   \
            return {rosidl_generator_traits::name<typename std::tuple_element<Is, Tuple>::type>()...};                                      \
        }                                                                                                                                   \
                                                                                                                                            \
        template <typename Tuple>                                                                                                           \
        std::vector<std::string> get_msg_types()                                                                                            \
        {                                                                                                                                   \
            return get_msg_types_impl<Tuple>(std::make_index_sequence<std::tuple_size<Tuple>::value>{});                                    \
        }                                                                                                                                   \
                                                                                                                                            \
        const bool _ = []()                                                                                                                 \
        {                                                                                                                                   \
            sfg_experimental_area_visualization::message_visualizers::MessageVisualizerFactory::instance().enroll(                          \
                get_msg_types<typename MessageVisualizer::MsgTypesTuple>(),                                                                 \
                #MessageVisualizer,                                                                                                         \
                [](rerun::RecordingStream &stream, rclcpp::Node &node, const std::vector<std::string> &topic_names, const rclcpp::QoS &qos) \
                {                                                                                                                           \
                    return std::make_unique<MessageVisualizer>(stream, node, topic_names, qos);                                             \
                });                                                                                                                         \
                                                                                                                                            \
            return true;                                                                                                                    \
        }();                                                                                                                                \
    }

namespace sfg_experimental_area_visualization::message_visualizers
{
    class MessageVisualizerFactory
    {
    public:
        using FactoryFunction = std::function<std::unique_ptr<MessageVisualizerBase>(
            rerun::RecordingStream &,
            rclcpp::Node &,
            const std::vector<std::string> &,
            const rclcpp::QoS &qos)>;

        struct MessageVisualizerInfo
        {
            std::string name;
            std::vector<std::string> msg_types;
            FactoryFunction factory;
        };

        static MessageVisualizerFactory &instance();

        void enroll(
            const std::vector<std::string> &msg_types,
            const std::string &name,
            FactoryFunction factory);

        std::unique_ptr<MessageVisualizerBase> create(
            rerun::RecordingStream &stream,
            rclcpp::Node &node,
            const std::vector<TopicInfo> &topics,
            const rclcpp::QoS &qos) const;

        std::vector<MessageVisualizerInfo> get_infos() const;

    private:
        MessageVisualizerFactory() = default;
        std::string compute_key(std::vector<std::string> msg_types) const;

        std::map<std::string, MessageVisualizerInfo> m_message_visualizers;
        std::map<std::string, std::string> m_name_to_key;
    };
}
