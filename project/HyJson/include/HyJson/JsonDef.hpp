#pragma once
#include <map>
#include <string>
#include <vector>
#include <iosfwd>

namespace hy::json
{
    enum class JType
    {
        Null,
        True,
        False,
        Integer,
        Number,
        String,
        Array,
        Object,
    };

    class Json;
    using JReal = double;
    using JBool = bool;
    using JInt = std::int64_t;
    using JNull = std::nullptr_t;
    using JArray = std::vector<Json>;
    using JString = std::basic_string<char>;
    using JObject = std::map<JString, Json>;
    using JPair = std::pair<JString, Json>;

    std::ostream &operator<<(std::ostream &os, const Json &json);
    
} // namespace hy::json
