#include <rclcpp/rclcpp.hpp>
#include <rerun.hpp>

namespace sfg_experimental_area_visualization::message_visualizers
{
    template <typename... MsgTypes>
    MessageVisualizer<MsgTypes...>::MessageVisualizer(
        rerun::RecordingStream &recording_stream,
        rclcpp::Node &node,
        const std::vector<std::string> &topic_names,
        const rclcpp::QoS &qos) : MessageVisualizerBase(recording_stream, topic_names)
    {
        if (sizeof...(MsgTypes) != topic_names.size())
        {
            throw std::invalid_argument("The number of message types and topic names must be equal.");
        }

        if (sizeof...(MsgTypes) > 9)
        {
            throw std::invalid_argument("A maximum of 9 message types is supported.");
        }

        initialize_subscribers(node, topic_names, qos, std::index_sequence_for<MsgTypes...>{});
        m_synchronizer = std::apply(
            [&](auto &...subscribers)
            {
                return std::make_shared<Synchronizer>(SyncPolicy(qos.depth()), subscribers...);
            },
            m_subscribers);
        register_callback(std::index_sequence_for<MsgTypes...>{});
    }

    template <typename... MsgTypes>
    template <size_t... Is>
    void MessageVisualizer<MsgTypes...>::initialize_subscribers(rclcpp::Node &node, const std::vector<std::string> &topics, const rclcpp::QoS &qos, std::index_sequence<Is...>)
    {
        (std::get<message_filters::Subscriber<MsgTypes>>(m_subscribers).subscribe(&node, topics[Is], qos.get_rmw_qos_profile()), ...);
    }

    template <typename... MsgTypes>
    template <size_t... Is>
    void MessageVisualizer<MsgTypes...>::register_callback(std::index_sequence<Is...>)
    {
        constexpr auto placeholders = std::make_tuple(
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
            std::placeholders::_4, std::placeholders::_5, std::placeholders::_6,
            std::placeholders::_7, std::placeholders::_8, std::placeholders::_9);

        m_synchronizer->registerCallback(std::bind(&MessageVisualizer<MsgTypes...>::callback, this, std::get<Is>(placeholders)...));
    }
}

namespace sfg_experimental_area_visualization::message_visualizers
{
    template <typename MsgType>
    MessageVisualizer<MsgType>::MessageVisualizer(
        rerun::RecordingStream &recording_stream,
        rclcpp::Node &node,
        const std::vector<std::string> &topic_names,
        const rclcpp::QoS &qos) : MessageVisualizerBase(recording_stream, topic_names)
    {
        if (topic_names.size() != 1)
        {
            throw std::invalid_argument("The number of message types and topic names must be equal.");
        }

        m_subscriber = node.create_subscription<MsgType>(
            topic_names[0],
            qos,
            std::bind(&MessageVisualizer<MsgType>::callback, this, std::placeholders::_1));
    }

}