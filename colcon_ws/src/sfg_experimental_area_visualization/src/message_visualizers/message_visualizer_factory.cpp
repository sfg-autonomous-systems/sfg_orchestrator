#include "sfg_experimental_area_visualization/message_visualizers/message_visualizer_factory.hpp"

namespace sfg_experimental_area_visualization::message_visualizers
{
    MessageVisualizerFactory &MessageVisualizerFactory::instance()
    {
        static MessageVisualizerFactory instance;
        return instance;
    }

    void MessageVisualizerFactory::enroll(const std::vector<std::string> &msg_types, const std::string &name, FactoryFunction factory)
    {
        auto key = compute_key(msg_types);

        if (m_message_visualizers.find(key) != m_message_visualizers.end())
        {
            throw std::runtime_error("Message visualizer for message types '" + key + "' is already registered.");
        }

        if (m_name_to_key.find(name) != m_name_to_key.end())
        {
            throw std::runtime_error("Message visualizer with name '" + name + "' is already registered.");
        }

        m_message_visualizers[key] = m_message_visualizers[name] = {name, msg_types, factory};
        m_name_to_key[name] = key;
    }

    std::unique_ptr<MessageVisualizerBase> MessageVisualizerFactory::create(
        rerun::RecordingStream &stream,
        rclcpp::Node &node,
        const std::vector<TopicInfo> &topics,
        const rclcpp::QoS &qos) const
    {
        std::vector<std::string> topic_names;
        std::vector<std::string> msg_types;

        for (const auto &topic : topics)
        {
            topic_names.push_back(topic.topic_name);
            msg_types.push_back(topic.msg_type);
        }

        auto key = compute_key(msg_types);
        auto iterator = m_message_visualizers.find(key);

        if (iterator == m_message_visualizers.end())
        {
            throw std::runtime_error("Unsupported message types '" + key + "'.");
        }
        return iterator->second.factory(stream, node, topic_names, qos);
    }

    std::vector<MessageVisualizerFactory::MessageVisualizerInfo> MessageVisualizerFactory::get_infos() const
    {
        std::vector<MessageVisualizerInfo> infos;
        infos.reserve(m_message_visualizers.size());

        for (const auto &[key, info] : m_message_visualizers)
        {
            infos.push_back(info);
        }
        return infos;
    }

    std::string MessageVisualizerFactory::compute_key(std::vector<std::string> msg_types) const
    {
        std::string key;
        std::sort(msg_types.begin(), msg_types.end());

        for (const auto &msg_type : msg_types)
        {
            key += msg_type + ", ";
        }

        if (!key.empty())
        {
            key.erase(key.size() - 2);
        }
        return key;
    }
}