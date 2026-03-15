#pragma once

#include <format>
#include <stdexcept>
#include <string_view>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };

constexpr Genre GenreFromString(std::string_view s) {
    if (s == "Fiction") {
        return Genre::Fiction;
    }
    else if (s == "NonFiction") {
        return Genre::NonFiction;
    }
    else if (s == "SciFi") {
        return Genre::SciFi;
    }
    else if (s == "Biography") {
        return Genre::Biography;
    }
    else if (s == "Mystery") {
        return Genre::Mystery;
    }

    return Genre::Unknown;
}

struct Book {
    // string_view для экономии памяти, чтобы ссылаться на оригинальную строку, хранящуюся в другом контейнере
    std::string_view author;
    std::string title;

    int year;
    Genre genre;
    double rating;
    int read_count;

    constexpr Book(std::string title, std::string_view author, int year, Genre genre, double rating, int read_count)
        : title(title), author(author), year(year), genre(genre), rating(rating), read_count(read_count) {}
    constexpr Book(std::string title, std::string_view author, int year, std::string genre, double rating, int read_count)
        : title(title), author(author), year(year), genre(GenreFromString(genre)), rating(rating), read_count(read_count) {}
};
}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        std::string genre_str;

        // clang-format off
        using bookdb::Genre;
        switch (g) {
            case Genre::Fiction:    genre_str = "Fiction"; break;
            case Genre::Mystery:    genre_str = "Mystery"; break;
            case Genre::NonFiction: genre_str = "NonFiction"; break;
            case Genre::SciFi:      genre_str = "SciFi"; break;
            case Genre::Biography:  genre_str = "Biography"; break;
            case Genre::Unknown:    genre_str = "Unknown"; break;
            default:
                throw logic_error{"Unsupported bookdb::Genre"};
            }
        // clang-format on
        return format_to(fc.out(), "{}", genre_str);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<bookdb::Book> {
    template <typename FormatContext>
    auto format(const bookdb::Book b, FormatContext& fc) const {
        return format_to(fc.out(), "{}, {}, {}, {}, {}, {}", b.title, b.author, b.year, b.genre, b.rating, b.read_count);
    }

    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

// Ваш код для std::formatter<Book> здесь

}  // namespace std
