#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;

    bool operator()(const Book& l, const std::string& r) const {
        return l.title < r;
    }
};

struct TransparentStringEqual {};

struct TransparentStringHash {};

}  // namespace bookdb
