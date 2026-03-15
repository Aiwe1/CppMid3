#pragma once

#include <algorithm>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string_view>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <numeric>

#include "book_database.hpp"

#include <print>

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(const BookDatabase<T> &cont, Comparator comp = {}) {
	std::map<std::string_view, int> res;

	for (auto& a : cont.GetAuthors()) {
		res.insert({ a, 1 });
	}

	return res;
}

template <BookIterator It>
auto calculateGenreRatings(It first, It last) {
	std::unordered_map<Genre, std::pair<double, int>> pre_res;
	std::unordered_map<Genre, double> res;

	for (auto i = first; i != last; ++i) {
		pre_res[i->genre].first += i->rating;
		pre_res[i->genre].second++;
	}

	for (auto& e : pre_res) {
		res.insert({ e.first, (e.second.first / (double)(e.second.second)) });
	}

	return res;
}

template <BookContainerLike T>
auto calculateAverageRating(const BookDatabase<T>& db) {
	double res = std::accumulate(db.cbegin(), db.cend(), 0.0, [](double sum, const Book& b) {return sum + b.rating; }) / db.size();

	return res;
}

template <BookContainerLike T>
auto sampleRandomBooks(const BookDatabase<T>& db, int count) {
	std::vector<std::reference_wrapper<const Book>> res;

	std::for_each(db.GetBooks().crbegin(), db.GetBooks().crbegin() + count, [&res](const Book& b) {res.push_back(std::cref(b)); });

	return res;
} 

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto getTopNBy(BookDatabase<T>& db, int count, Comparator comp = comp::LessByRating{}) {
	std::sort(db.begin(), db.end(), comp);

	return sampleRandomBooks(db, count);
}


}  // namespace bookdb
