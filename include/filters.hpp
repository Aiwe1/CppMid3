#pragma once

#include <algorithm>
#include <functional>

#include "book.hpp"
#include "concepts.hpp"

namespace bookdb {
	// filterBooks(db.begin(), db.end(), all_of(YearBetween(1900, 1999), RatingAbove(4.5)));

	auto YearBetween(int l, int r) {
		return [l, r](const Book& b) {
			return (b.year >= l) && (b.year <= r);
			};
	}

	auto RatingAbove(double r) {
		return [r](const Book& b) {
			return b.rating > r;
			};
	}

	auto GenreIs(Genre g) {
		return [g](const Book& b) {
			return b.genre == g;
			};
	}

	template <typename... Pred>
	auto all_of(Pred... pred) {
		return [pred...](const Book& b) {
			return (pred(b) && ...);
			};
		
	}

	template <typename... Pred>
	auto any_of(Pred... pred) {
		return [pred...](const Book& b) {
			return (pred(b) || ...);
			};

	}

	template <BookIterator It, typename Pred>
	auto  filterBooks(It first, It last, Pred pred) {
		std::vector<std::reference_wrapper<const Book>> res;

		std::for_each(first, last, [pred, &res](const Book& b) {
			if (pred(b)) {
				res.push_back(std::cref(b));
			}
			});

		return res;
	}
}  // namespace bookdb