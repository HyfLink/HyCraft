#include "HyJson/Json.hpp"

namespace hy::json
{
    Json::Json(const JPair &value) noexcept
        : mType(JType::Object), mObject()
    {
        mObject[value.first] = value.second;
    }
    Json::Json(const JString &key, const Json &value) noexcept
        : mType(JType::Object), mObject()
    {
        mObject[key] = value;
    }
    Json::Json(const JString &key, Json &&value) noexcept
        : mType(JType::Object), mObject()
    {
        mObject[key] = std::move(value);
    }
    Json::Json(JPair &&value) noexcept
    {
        mObject[value.first] = std::move(value.second);
    }
    Json::Json(const Json &other) noexcept : mType(other.mType)
    {
        switch (mType) {
        case JType::Integer: mInteger = other.mInteger; break;
        case JType::Number: mNumber = other.mNumber; break;
        case JType::String: new (&mString) JString(other.mString); break;
        case JType::Object: new (&mObject) JObject(other.mObject); break;
        case JType::Array: new (&mArray) JArray(other.mArray); break;
        }
    }
    Json::Json(std::initializer_list<JPair> list) noexcept
        : mType(JType::Object), mObject()
    {
        for (auto pair : list)
        {
            mObject[pair.first] = pair.second;
        }
    }
    Json::Json(Json &&other) noexcept : mType(other.mType)
    {
        switch (mType) {
        case JType::Integer: mInteger = other.mInteger; break;
        case JType::Number: mNumber = other.mNumber; break;
        case JType::String: new (&mString) JString(std::move(other.mString)); break;
        case JType::Object: new (&mObject) JObject(std::move(other.mObject)); break;
        case JType::Array: new (&mArray) JArray(std::move(other.mArray)); break;
        }
    }

    Json &Json::operator=(JNull) noexcept
    {
        destory();
        mType = JType::Null;
        return *this;
    }
    Json &Json::operator=(JBool value) noexcept
    {
        destory();
        mType = value ? JType::True : JType::False;
        return *this;
    }
    Json &Json::operator=(const JObject &value) noexcept
    {
        destory();
        mType = JType::Object;
        new (&mObject) JObject(value);
        return *this;
    }
    Json &Json::operator=(const JArray &value) noexcept
    {
        destory();
        mType = JType::Array;
        new (&mArray) JArray(value);
        return *this;
    }
    Json &Json::operator=(const JPair &value) noexcept
    {
        destory();
        mType = JType::Object;
        new (&mObject) JObject();
        mObject[value.first] = value.second;
        return *this;
    }
    Json &Json::operator=(const Json &other) noexcept
    {
        destory();
        switch (mType = other.mType)
        {
        case JType::Integer: mInteger = other.mInteger; break;
        case JType::Number: mNumber = other.mNumber; break;
        case JType::String: new (&mString) JString(other.mString); break;
        case JType::Object: new (&mObject) JObject(other.mObject); break;
        case JType::Array: new (&mArray) JArray(other.mArray); break;
        }
        return *this;
    }
    Json &Json::operator=(JString &&value) noexcept
    {
        destory();
        mType = JType::String;
        new (&mString) JString(std::move(value));
        return *this;
    }
    Json &Json::operator=(JObject &&value) noexcept
    {
        destory();
        mType = JType::Object;
        new (&mObject) JObject(std::move(value));
        return *this;
    }
    Json &Json::operator=(JArray &&value) noexcept
    {
        destory();
        mType = JType::Array;
        new (&mArray) JArray(std::move(value));
        return *this;
    }
    Json &Json::operator=(JPair &&value) noexcept
    {
        destory();
        mType = JType::Object;
        new (&mObject) JObject();
        mObject[value.first] = std::move(value.second);
        return *this;
    }
    Json &Json::operator=(std::initializer_list<JPair> list) noexcept
    {
        destory();
        mType = JType::Object;
        new (&mObject) JObject();
        for (auto pair : list)
        {
            mObject[pair.first] = pair.second;
        }
        return *this;
    }
    Json &Json::operator=(Json &&other) noexcept
    {
        destory();
        switch (mType = other.mType) {
        case JType::Integer: mInteger = other.mInteger; break;
        case JType::Number: mNumber = other.mNumber; break;
        case JType::String: new (&mString) JString(std::move(other.mString)); break;
        case JType::Object: new (&mObject) JObject(std::move(other.mObject)); break;
        case JType::Array: new (&mArray) JArray(std::move(other.mArray)); break;
        }
        return *this;
    }

    void Json::destory() noexcept
    {
        switch (mType) {
        case JType::Object: mObject.~map(); break;
        case JType::String: mString.~basic_string(); break;
        case JType::Array: mArray.~vector(); break;
        }
    }

    JReal &Json::as_number()
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_number())
            throw JsonTypeError("not number type");
#endif // HY_JSON_NO_EXCPTION

        return mNumber;
    }
    JInt &Json::as_integer()
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_integer())
            throw JsonTypeError("not integral type");
#endif // HY_JSON_NO_EXCPTION

        return mInteger;
    }
    JArray &Json::as_array()
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_array())
            throw JsonTypeError("not array type");
#endif // HY_JSON_NO_EXCPTION

        return mArray;
    }
    JString &Json::as_string()
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_string())
            throw JsonTypeError("not string type");
#endif // HY_JSON_NO_EXCPTION

        return mString;
    }
    JObject &Json::as_object()
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_object())
            throw JsonTypeError("not object type");
#endif // HY_JSON_NO_EXCPTION

        return mObject;
    }

    JReal Json::as_number() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_number())
            throw JsonTypeError("not number type");
#endif // HY_JSON_NO_EXCPTION

        return mNumber;
    }
    JInt Json::as_integer() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_integer())
            throw JsonTypeError("not integral type");
#endif // HY_JSON_NO_EXCPTION

        return mInteger;
    }
    JBool Json::as_boolean() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_bool())
            throw JsonTypeError("not boolean type");
#endif // HY_JSON_NO_EXCPTION

        return is_true();
    }
    const JArray &Json::as_array() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_array())
            throw JsonTypeError("not array type");
#endif // HY_JSON_NO_EXCPTION

        return mArray;
    }
    const JString &Json::as_string() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_string())
            throw JsonTypeError("not string type");
#endif // HY_JSON_NO_EXCPTION

        return mString;
    }
    const JObject &Json::as_object() const
    {
#ifndef HY_JSON_NO_EXCPTION
        if (!is_object())
            throw JsonTypeError("not object type");
#endif // HY_JSON_NO_EXCPTION

        return mObject;
    }

    Json &Json::operator[](size_t index)
    {
        if (!is_array())
            throw JsonTypeError("not array type");
        return mArray[index];
    }
    const Json &Json::operator[](size_t index) const
    {
        if (!is_array())
            throw JsonTypeError("not array type");
        return mArray[index];
    }
    Json &Json::operator[](const JString &key)
    {
        if (!is_object())
            throw JsonTypeError("not object type");
        return mObject[key];
    }
    const Json &Json::operator[](const JString &key) const
    {
        if (!is_object())
            throw JsonTypeError("not object type");
        if (mObject.find(key) == mObject.end())
            throw JsonInvalidKey();
        return mObject.at(key);
    }

} // namespace hy::json
