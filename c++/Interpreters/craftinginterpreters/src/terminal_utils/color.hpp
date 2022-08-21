#pragma once
#ifndef TERMINAL_UTILS_COLOR_HPP
#define TERMINAL_UTILS_COLOR_HPP

namespace Terinal_Utils {
    class Color {
        public:
            static constexpr const char* RESET = "\033[0m";
            static constexpr const char* BLACK = "\033[30m";
            static constexpr const char* RED = "\033[31m";
            static constexpr const char* GREEN = "\033[32m";
            static constexpr const char* YELLOW = "\033[33m";
            static constexpr const char* BLUE = "\033[34m";
            static constexpr const char* MAGENTA = "\033[35m";
            static constexpr const char* CYAN = "\033[36m";
            static constexpr const char* WHITE = "\033[37m";
            static constexpr const char* BOLD = "\033[1m";
            static constexpr const char* UNDERLINE = "\033[4m";
            static constexpr const char* BLINK = "\033[5m";
            static constexpr const char* REVERSE = "\033[7m";
            static constexpr const char* HIDDEN = "\033[8m";
            static constexpr const char* BLACK_BG = "\033[40m";
            static constexpr const char* RED_BG = "\033[41m";
            static constexpr const char* GREEN_BG = "\033[42m";
            static constexpr const char* YELLOW_BG = "\033[43m";
            static constexpr const char* BLUE_BG = "\033[44m";
            static constexpr const char* MAGENTA_BG = "\033[45m";
            static constexpr const char* CYAN_BG = "\033[46m";
            static constexpr const char* WHITE_BG = "\033[47m";
            static constexpr const char* BOLD_BG = "\033[100m";
            static constexpr const char* UNDERLINE_BG = "\033[104m";
            static constexpr const char* BLINK_BG = "\033[105m";
            static constexpr const char* REVERSE_BG = "\033[107m";
            static constexpr const char* HIDDEN_BG = "\033[108m";
    };
}

#endif