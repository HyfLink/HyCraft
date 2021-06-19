#pragma once
#ifndef HY_JSON_NO_EXCPTION
#include <stdexcept>

namespace hy::json
{
    class JsonExcption : public std::exception
    {
    public:
        JsonExcption() noexcept;
        explicit JsonExcption(const std::string &msg) noexcept;
        virtual ~JsonExcption() = default;

        virtual const char *what() const noexcept override;

    private:
        std::string mMsg;
    };

    struct JsonTypeError : public JsonExcption
    {
        using JsonExcption::JsonExcption;
        inline JsonTypeError() : JsonExcption("Type Error") {}
        virtual ~JsonTypeError() = default;
    };

    struct JsonInvalidKey : public JsonExcption
    {
        using JsonExcption::JsonExcption;
        inline JsonInvalidKey() : JsonExcption("Invalid Key") {}
        virtual ~JsonInvalidKey() = default;
    };

    struct JsonParseError : public JsonExcption
    {
        using JsonExcption::JsonExcption;
        inline JsonParseError() : JsonExcption("Parse Error") {}
        virtual ~JsonParseError() = default;
    };

} // namespace hy::json

#endif // HY_JSON_NO_EXCPTION