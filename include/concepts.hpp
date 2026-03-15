#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike = requires(T t) {
	typename T::value_type;
	typename T::iterator;
	{ t.begin() } -> std::same_as<typename T::iterator>;
	{ t.end() } -> std::same_as<typename T::iterator>;
	{ t.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept BookIterator = std::input_iterator<T> && requires(T i) {
	{ ++i } -> std::same_as<T&>; 
	{ *i };                     
};

template <typename S, typename I>
concept BookSentinel = true;


template<typename P, typename... Args>
concept BookPredicate = std::predicate<P, Args...>;

template <typename C>
concept BookComparator = true;

}  // namespace bookdb