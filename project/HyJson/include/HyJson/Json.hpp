#pragma once
#include "HyJson/JsonDef.hpp"
#include "HyJson/Excption.hpp"

namespace hy::json
{
    class Json
    {
    public:
        constexpr Json() noexcept;
        constexpr Json(JNull value) noexcept;
        constexpr Json(JBool value) noexcept;
        Json(const JObject &value) noexcept;
        Json(const JArray &value) noexcept;
        Json(const Json &other) noexcept;
        Json(const JPair &value) noexcept;
        Json(const JString &key, const Json &value) noexcept;
        Json(const JString &key, Json &&value) noexcept;
        Json(JString &&value) noexcept;
        Json(JObject &&value) noexcept;
        Json(JArray &&value) noexcept;
        Json(Json &&other) noexcept;
        Json(JPair &&value) noexcept;
        Json(std::initializer_list<JPair> list) noexcept;

        template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        explicit constexpr Json(T value) noexcept;

        template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        explicit constexpr Json(T value) noexcept;

        template <typename T, std::enable_if_t<std::is_constructible_v<JString, T>, int> = 0>
        explicit Json(const T &value) noexcept;

        ~Json() noexcept;

        Json &operator=(JNull value) noexcept;
        Json &operator=(JBool value) noexcept;
        Json &operator=(const JObject &value) noexcept;
        Json &operator=(const JArray &value) noexcept;
        Json &operator=(const Json &other) noexcept;
        Json &operator=(const JPair &value) noexcept;
        Json &operator=(JString &&value) noexcept;
        Json &operator=(JObject &&value) noexcept;
        Json &operator=(JArray &&value) noexcept;
        Json &operator=(Json &&other) noexcept;
        Json &operator=(JPair &&value) noexcept;
        Json &operator=(std::initializer_list<JPair> list) noexcept;

        template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Json &operator=(T value) noexcept;

        template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Json &operator=(T value) noexcept;

        template <typename T, std::enable_if_t<std::is_constructible_v<JString, T>, int> = 0>
        Json &operator=(const T &value) noexcept;

        JType type() const noexcept;
        bool is_null() const noexcept;
        bool is_bool() const noexcept;
        bool is_true() const noexcept;
        bool is_false() const noexcept;
        bool is_numeric() const noexcept;
        bool is_integer() const noexcept;
        bool is_number() const noexcept;
        bool is_string() const noexcept;
        bool is_object() const noexcept;
        bool is_array() const noexcept;

        JArray &as_array();
        JReal &as_number();
        JString &as_string();
        JObject &as_object();
        JInt &as_integer();

        JReal as_number() const;
        JInt as_integer() const;
        JBool as_boolean() const;
        const JArray &as_array() const;
        const JString &as_string() const;
        const JObject &as_object() const;

        Json &operator[](size_t index);
        const Json &operator[](size_t index) const;
        Json &operator[](const JString &key);
        const Json &operator[](const JString &key) const;

    protected:
        void destory() noexcept;
        friend std::ostream &operator<<(std::ostream &os, const Json &json);
        friend std::istream &operator>>(std::istream &os, Json &json);

    protected:
        JType mType;
        union {
            JArray mArray;
            JObject mObject;
            JString mString;
            JReal mNumber;
            JInt mInteger;
        };
    };

} // namespace hy::json

#include "Json.inl"