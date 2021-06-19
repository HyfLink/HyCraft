#ifndef HY_JSON_NO_EXCPTION
#include "HyJson/Excption.hpp"

namespace hy::json
{
    JsonExcption::JsonExcption() noexcept
        : mMsg("[HyJson]Execption")
    {
    }

    JsonExcption::JsonExcption(const std::string &msg) noexcept
        : mMsg("[HyJson]" + msg)
    {
    }

    const char *JsonExcption::what() const noexcept
    {
        return mMsg.c_str();
    }

} // namespace hy::json
#endif // HY_JSON_NO_EXCPTION