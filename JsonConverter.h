#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <boost/json.hpp>

class JsonConverter
{
public:
    JsonConverter() = default;

    // boost::json to QJson
    QJsonValue convert(const boost::json::value &value);
    QJsonObject convert(const boost::json::object &object);
    QJsonArray convert(const boost::json::array &array);

    QJsonValue operator()(const boost::json::value &value);
    QJsonObject operator()(const boost::json::object &object);
    QJsonArray operator()(const boost::json::array &array);

    // QJson to boost::json
    boost::json::value convert(const QJsonValue &value);
    boost::json::object convert(const QJsonObject &object);
    boost::json::array convert(const QJsonArray &array);

    boost::json::value operator()(const QJsonValue &value);
    boost::json::object operator()(const QJsonObject &object);
    boost::json::array operator()(const QJsonArray &array);
};

