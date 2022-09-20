#ifndef UTILS_HPP
# define UTILS_HPP

# include <memory>
# include <iostream>
# include <cstddef>
# include <limits>

namespace ft
{
	template <typename T>
	void
	swap(T& a, T& b)
	{
		T	c;

		c = a;
		a = b;
		b = c;
	}

	template <typename T>
	inline const T&
	max(const T& a, const T& b)
	{
		if (a < b)
			return (b);
		return (a);
	}

	template <typename T>
	inline bool
	itcmp	(const T& lhs, const T& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typedef typename T::const_iterator const_iterator;
		const_iterator	it1;
		const_iterator	it2;
		const_iterator	end1;
		const_iterator	end2;

		it1 = lhs.begin();
		it2 = rhs.begin();
		end1 = lhs.end();
		end2 = rhs.end();
		if (it1 == it2 && end1 == end2)
			return (true);
		while (it1 != end1 && it2 != end2 && *it1 == *it2)
		{
			it1++;
			it2++;
		}
		return (*it1 == *it2);
	}

	template <typename IT1, typename IT2>
	inline bool
	itcmp	(IT1 first1, IT1 last1, IT2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			first1++;
			first2++;
		}
		return (*first1 == *first2);
	}

	template <typename T>
	inline bool
	itinf (const T& lhs, const T& rhs)
	{
		typedef typename T::const_iterator const_iterator;
		const_iterator	it1;
		const_iterator	it2;

		it1 = lhs.begin();
		it2 = rhs.begin();
		while (it1 != lhs.end())
		{
			if (it2 == rhs.end() || *it2 < *it1)
				return (false);
			else if (*it1 < *it2)
				return (true);
			++it1;
			++it2;
		}
		return (it2 != rhs.end());
	}

	template <class InputIterator1, class InputIterator2>
	bool itinf (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || (*first2) < (*first1))
				return (false);
			else if ((*first1) < (*first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<typename Arg1, typename Arg2, typename Result>
		struct binary_function
		{
			typedef Arg1	first_argument_type;
			typedef Arg2	second_argument_type;
			typedef Result	result_type;
		};

	template <typename Arg, typename Result>
		struct unary_function
		{
			typedef Arg		argument_type;
			typedef Result	result_type;
		};

	template<typename T>
		struct _Identity
		: public unary_function<T, T>
		{
			T&
			operator() (T& x) const
			{
				return (x);
			}

			const T&
			operator() (const T& x) const
			{
				return (x);
			}
		};

	template <typename P>
		struct _Select1st
		: public unary_function<P, typename P::first_type>
		{
			typename P::first_type&
				operator()(P& x) const
				{
					return (x.first);
				}

			const typename P::first_type&
				operator()(const P& x) const
				{
					return (x.first);
				}
		};

	template<typename T>
		struct less
		: public binary_function<T, T, bool>
		{
			bool
			operator() (const T& x, const T& y) const
			{
				return (x < y);
			}
		};

	struct true_type {};
	struct false_type {};

	template<typename _Tp>
		struct is_integer
		{
			enum { value = 0 };
			typedef false_type type;
		};

	template<>
		struct is_integer<bool>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<signed char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<short>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned short>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<int>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned int>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<long long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned long long>
		{
			enum { value = 1 };
			typedef true_type type;
		};
}

# include "iterator.hpp"
# include "pair.hpp"
# include "binary_tree.hpp"
# include "list.hpp"
# include "vector.hpp"
# include "map.hpp"
# include "stack.hpp"
# include "queue.hpp"
# include "set.hpp"
# include "multiset.hpp"
# include "multimap.hpp"

#endif
