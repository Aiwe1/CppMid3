#pragma once

#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <set>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    // Type aliases
    using iterator = BookContainer::iterator;
    using const_iterator = BookContainer::const_iterator;
    using value_type = Book;
    using reference = Book&;            
    using const_reference = const Book&;      
    using pointer = Book*;            
    using size_type = std::size_t;   

    using AuthorContainer = std::set<std::string_view>; 

    BookDatabase() = default;

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    // Standard container interface methods

    iterator begin() { 
        return books_.begin(); 
    }

    iterator end() { 
        return books_.end(); 
    }

    const_iterator cbegin() const {
        return books_.cbegin();
    }

    const_iterator cend() const {
        return books_.cend();
    }

    size_type size() const noexcept {
        return books_.size();
    }

    void PushBack(value_type v) {
        books_.push_back(std::forward<value_type>(v));
        authors_.emplace(v.author);
    }

    template <typename... Args>
    void EmplaceBack(Args&&... args) {
        books_.emplace_back(std::forward<Args>(args)...);
        authors_.emplace((books_.end() - 1)->author);
    }

    BookDatabase(std::initializer_list<Book> book) {
        books_.PushBack(book);
    }
    const BookContainer& GetBooks() const noexcept { return books_;  }
    const AuthorContainer& GetAuthors() const noexcept { return authors_; }

private:
    BookContainer books_;
    AuthorContainer authors_;
};

}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {

        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }
        
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
