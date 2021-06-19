#include <iostream>
#include <cctype>
#include "HyJson/Json.hpp"

namespace hy::json
{
    
    namespace detail
    {
        std::ostream &out(std::ostream &os, const JArray &array)
        {
            if (array.empty()) return os << "[]";

            auto iter = array.begin(), end = array.end();
            os << '[' << *iter;
            for (++iter; iter != end; ++iter)
                os << ',' << *iter;
            return os << ']';
        }
        std::ostream &out(std::ostream &os, const JObject &object)
        {
            if (object.empty()) return os << "{}";

            auto iter = object.begin(), end = object.end();
            os << '{' << '"' << iter->first << '"' << ':' << iter->second;
            for (++iter; iter != end; ++iter)
                os << ',' << '"' << iter->first << '"' << ':' << iter->second;
            return os << '}';
        }

    } // namespace detail

    std::ostream &operator<<(std::ostream &os, const Json &json)
    {
        switch (json.type()) {
        case JType::Null: return os << "null";
        case JType::True: return os << "true";
        case JType::False: return os << "false";
        case JType::Integer: return os << json.mInteger;
        case JType::Number: return os << json.mNumber;
        case JType::String: return os << '"' << json.mString << '"';
        case JType::Object: return detail::out(os, json.mObject);
        case JType::Array: return detail::out(os, json.mArray);
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Json &json)
    {
        return is;
    }

} // namespace hy::json
