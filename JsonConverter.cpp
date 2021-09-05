#include "JsonConverter.h"

namespace json = boost::json;

QJsonValue JsonConverter::convert(const json::value &value)
{
    switch (value.kind())
    {
    case json::kind::null:
        return QJsonValue();

    case json::kind::bool_:
        return value.get_bool();

    case json::kind::int64:
        return double(value.get_int64());

    case json::kind::uint64:
        return double(value.get_uint64());

    case json::kind::double_:
        return value.get_double();

    case json::kind::string:
        return value.get_string().c_str();

    case json::kind::array:
        return convert(value.get_array());

    case json::kind::object:
        return convert(value.get_object());
    }
}

QJsonObject JsonConverter::convert(const boost::json::object &object)
{
    QJsonObject qjsonObject;

    for (const auto &pair : object)
    {
        const QString key(QByteArray(pair.key().data(), pair.key().length()));

        qjsonObject.insert(key, convert(pair.value()));
    }

    return qjsonObject;
}

QJsonArray JsonConverter::convert(const boost::json::array &array)
{
    QJsonArray qjsonArray;

    std::transform(array.begin(), array.end(), std::back_inserter(qjsonArray), *this);

    return qjsonArray;
}

QJsonValue JsonConverter::operator()(const boost::json::value &value)
{
    return convert(value);
}

json::value JsonConverter::convert(const QJsonValue &value)
{
    switch (value.type())
    {
    case QJsonValue::Null:
        return nullptr;

    case QJsonValue::Bool:
        return value.toBool();

    case QJsonValue::Double:
        return value.toDouble();

    case QJsonValue::String:
        return boost::string_view(value.toString().toStdString());

    case QJsonValue::Array:
        return convert(value.toArray());

    case QJsonValue::Object:
        return convert(value.toObject());

    case QJsonValue::Undefined:
        throw std::runtime_error("Undefined QJsonValue");
    }
}

json::object JsonConverter::convert(const QJsonObject &object)
{
    json::object bjsonObject;

    for (auto it = object.begin(); it != object.end(); ++it)
    {
        auto key = boost::string_view(it.key().toStdString());

        bjsonObject.emplace(std::move(key), convert(it.value()));
    }

    return bjsonObject;
}

json::array JsonConverter::convert(const QJsonArray &array)
{
    json::array bjsonArray(array.size());

    std::transform(array.begin(), array.end(), bjsonArray.begin(), *this);

    return bjsonArray;
}

boost::json::value JsonConverter::operator()(const QJsonValue &value)
{
    return convert(value);
}

boost::json::object JsonConverter::operator()(const QJsonObject &object)
{
    return convert(object);
}

boost::json::array JsonConverter::operator()(const QJsonArray &array)
{
    return convert(array);
}
