#pragma once
#include <defs.hpp>

#include <fmt/ranges.h>
#include <sstream>
#include <charconv>

#include <util/time.hpp>

namespace util::formatting {
    // example: 2.123s, 69.123ms
    template <typename Rep, typename Period>
    std::string formatDuration(time::duration<Rep, Period> time) {
        auto seconds = time::asSecs(time);
        auto millis = time::asMillis(time);
        auto micros = time::asMicros(time);

        if (seconds > 0) {
            return std::to_string(seconds) + "." + std::to_string(millis % 1000) + "s";
        } else if (millis > 0) {
            return std::to_string(millis) + "." + std::to_string(micros % 1000) + "ms";
        } else {
            return std::to_string(micros) + "μs";
        }
    }

    // example: 2023-11-16 19:43:50.200
    std::string formatDateTime(time::system_time_point tp);

    // example: 123.4KiB
    std::string formatBytes(uint64_t bytes);

    // format an HTTP error message into a nicer string
    std::string formatErrorMessage(std::string message);

    // parse a string to an integer
    template <typename T>
    inline std::optional<T> parse(const std::string_view src) {
        T output;

        auto result = std::from_chars(&*src.begin(), &*src.end(), output);
        if (result.ec != std::errc()) {
            return std::nullopt;
        }

        return output;
    }
}