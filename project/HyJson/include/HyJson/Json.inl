namespace hy::json
{
    constexpr Json::Json() noexcept
        : mType(JType::Null), mInteger(0) {}

    constexpr Json::Json(JNull) noexcept
        : mType(JType::Null), mInteger(0) {}

    constexpr Json::Json(JBool value) noexcept
        : mType(value ? JType::True : JType::False), mInteger(0) {}

    inline Json::Json(const JObject &value) noexcept
        : mType(JType::Object), mObject(value) {}
    
    inline Json::Json(const JArray &value) noexcept
        : mType(JType::Array), mArray(value) {}

    inline Json::Json(JString &&value) noexcept
        : mType(JType::String), mString(std::move(value)) {}
    
    inline Json::Json(JObject &&value) noexcept
        : mType(JType::Object), mObject(std::move(value)) {}
    
    inline Json::Json(JArray &&value) noexcept
        : mType(JType::Array), mArray(std::move(value)) {}

    template <typename T, std::enable_if_t<std::is_integral_v<T>, int>>
    constexpr Json::Json(T value) noexcept
        : mType(JType::Integer), mInteger(value) {}

    template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int>>
    constexpr Json::Json(T value) noexcept
        : mType(JType::Number), mNumber(value) {}

    template <typename T, std::enable_if_t<std::is_constructible_v<JString, T>, int>>
    inline Json::Json(const T &value) noexcept
        : mType(JType::String), mString(value) {}

    inline Json::~Json() noexcept { destory(); }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, int>>
    Json &Json::operator=(T value) noexcept
    {
        destory();
        mType = JType::Integer;
        mInteger = value;
        return *this;
    }

    template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int>>
    Json &Json::operator=(T value) noexcept
    {
        destory();
        mType = JType::Number;
        mNumber = value;
        return *this;
    }

    template <typename T, std::enable_if_t<std::is_constructible_v<JString, T>, int>>
    Json &Json::operator=(const T &value) noexcept
    {
        destory();
        mType = JType::String;
        new (&mString) JString(value);
        return *this;
    }

    inline JType Json::type() const noexcept { return mType; }
    inline bool Json::is_null() const noexcept { return (mType == JType::Null); }
    inline bool Json::is_bool() const noexcept { return is_true() || is_false(); }
    inline bool Json::is_true() const noexcept { return (mType == JType::True); }
    inline bool Json::is_false() const noexcept { return (mType == JType::False); }
    inline bool Json::is_numeric() const noexcept { return is_integer() || is_number(); }
    inline bool Json::is_integer() const noexcept { return (mType == JType::Integer); }
    inline bool Json::is_number() const noexcept { return (mType == JType::Number); }
    inline bool Json::is_string() const noexcept { return (mType == JType::String); }
    inline bool Json::is_object() const noexcept { return (mType == JType::Object); }
    inline bool Json::is_array() const noexcept { return (mType == JType::Array); }

} // namespace hy::json
