/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukarape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:36:34 by lukarape          #+#    #+#             */
/*   Updated: 2022/09/22 20:36:36 by lukarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "binary_tree.hpp"

namespace ft
{
	template <typename Key, typename _Tp, typename Compare = ft::less<Key>,
						typename _Alloc = std::allocator<ft::pair<const Key, _Tp> > >
		class map
		{
			public:
				typedef Key								key_type;
				typedef _Tp								mapped_type;
				typedef ft::pair<const Key, _Tp>		value_type;
				typedef Compare							keyCompare;
				typedef _Alloc							allocator_type;

			public:
				class valueCompare
				: public ft::binary_function<value_type, value_type, bool>
				{
					friend class map<Key, _Tp, Compare, _Alloc>;
					protected:
						Compare comp;

						valueCompare(Compare c)
						: comp(c)
						{}

					public:
						bool operator()(const value_type& x, const value_type& y) const
						{
							return (comp(x.first, y.first));
						}
				};

			private:
				typedef typename _Alloc::template
					rebind<value_type>::other _Pair_alloc_type;

				typedef _bin_tree<key_type, value_type, _Select1st<value_type>,
						 keyCompare, _Pair_alloc_type> _Rep_type;

				_Rep_type _M_t;

				typedef _Pair_alloc_type _Alloc_traits;

			public:
				typedef typename _Alloc_traits::pointer					pointer;
				typedef typename _Alloc_traits::const_pointer			const_pointer;
				typedef typename _Alloc_traits::reference				reference;
				typedef typename _Alloc_traits::const_reference			const_reference;
				typedef typename _Rep_type::iterator					iterator;
				typedef typename _Rep_type::const_iterator				const_iterator;
				typedef typename _Rep_type::size_type					size_type;
				typedef typename _Rep_type::difference_type				difference_type;
				typedef typename _Rep_type::reverse_iterator			reverse_iterator;
				typedef typename _Rep_type::const_reverse_iterator		const_reverse_iterator;

				map (void)
				: _M_t()
				{}

				explicit
				map (const Compare& comp,
					const allocator_type& a = allocator_type())
				: _M_t(comp, _Pair_alloc_type(a))
				{}

				map (const map& x)
				: _M_t(x._M_t) { }

				template<typename _InputIterator>
					map (_InputIterator first, _InputIterator last)
				: _M_t()
				{
					_M_t._M_insert_unique(first, last);
				}

				template<typename _InputIterator>
					map (_InputIterator first, _InputIterator last,
						const Compare& comp,
						const allocator_type& a = allocator_type())
				: _M_t(comp, _Pair_alloc_type(a))
				{
					_M_t._M_insert_unique(first, last);
				}

				map&
				operator=(const map& x)
				{
					_M_t = x._M_t;
					return (*this);
				}

				allocator_type
				get_allocator (void) const
				{
					return (allocator_type(_M_t.get_allocator()));
				}

				iterator
				begin (void)
				{
					return (_M_t.begin());
				}

				const_iterator
				begin (void) const
				{
					return (_M_t.begin());
				}

				iterator
				end (void)
				{
					return (_M_t.end());
				}

				const_iterator
				end (void) const
				{
					return (_M_t.end());
				}

				reverse_iterator
				rbegin (void)
				{
					return (_M_t.rbegin());
				}

				const_reverse_iterator
				rbegin (void) const
				{
					return (_M_t.rbegin());
				}

				reverse_iterator
				rend (void)
				{
					return (_M_t.rend());
				}

				const_reverse_iterator
				rend (void) const
				{
					return (_M_t.rend());
				}

				bool
				empty (void) const
				{
					return (_M_t.empty());
				}

				size_type
				size (void) const
				{
					return (_M_t.size());
				}

				size_type
				max_size (void) const
				{
					return (_M_t.max_size());
				}

				mapped_type&
				operator[](const key_type& k)
				{
					iterator i = lower_bound(k);
					if (i == end() || key_comp()(k, (*i).first))
							i = insert(i, value_type(k, mapped_type()));
					return ((*i).second);
				}

				mapped_type&
				at(const key_type& k)
				{
					iterator i = lower_bound(k);
					if (i == end() || key_comp()(k, (*i).first))
						throw std::out_of_range("Out of range");
					return ((*i).second);
				}

				const mapped_type&
				at(const key_type& k) const
				{
					const_iterator i = lower_bound(k);
					if (i == end() || key_comp()(k, (*i).first))
						throw std::out_of_range("Out of range");
					return ((*i).second);
				}

				ft::pair<iterator, bool>
				insert(const value_type& x)
				{
					return (_M_t._M_insert_unique(x));
				}

				iterator
				insert(iterator position, const value_type& x)
				{
					return (_M_t._M_insert_unique_(position, x));
				}

				template<typename _InputIterator>
					void
					insert(_InputIterator first, _InputIterator last)
					{
						_M_t._M_insert_unique(first, last);
					}

				void
				erase(iterator position)
				{
					_M_t.erase(position);
				}

				size_type
				erase(const key_type& x)
				{
					return (_M_t.erase(x));
				}

				void
				erase(iterator first, iterator last)
				{
					_M_t.erase(first, last);
				}

				void
				swap(map& x)
				{
					_M_t.swap(x._M_t);
				}

				void
				clear (void)
				{
					_M_t.clear();
				}

				keyCompare
				key_comp (void) const
				{
					return (_M_t.key_comp());
				}

				valueCompare
				value_comp (void) const
				{
					return (valueCompare(_M_t.key_comp()));
				}

				iterator
				find(const key_type& x)
				{
					return (_M_t.find(x));
				}

				const_iterator
				find(const key_type& x) const
				{
					return (_M_t.find(x));
				}

				size_type
				count(const key_type& x) const
				{
					return (_M_t.find(x) == _M_t.end() ? 0 : 1);
				}

				iterator
				lower_bound(const key_type& x)
				{
					return (_M_t.lower_bound(x));
				}

				const_iterator
				lower_bound(const key_type& x) const
				{
					return (_M_t.lower_bound(x));
				}

				iterator
				upper_bound(const key_type& x)
				{
					return (_M_t.upper_bound(x));
				}

				const_iterator
				upper_bound(const key_type& x) const
				{
					return (_M_t.upper_bound(x));
				}

				ft::pair<iterator, iterator>
				equal_range(const key_type& x)
				{
					return (_M_t.equal_range(x));
				}

				ft::pair<const_iterator, const_iterator>
				equal_range(const key_type& x) const
				{
					return (_M_t.equal_range(x));
				}

				template<typename _K1, typename _T1, typename _C1, typename _A1>
					friend bool
					operator==(const map<_K1, _T1, _C1, _A1>&,
				 const map<_K1, _T1, _C1, _A1>&);

				template<typename _K1, typename _T1, typename _C1, typename _A1>
					friend bool
					operator<(const map<_K1, _T1, _C1, _A1>&,
				const map<_K1, _T1, _C1, _A1>&);
			};

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator==(const map<Key, _Tp, Compare, _Alloc>& x,
							 const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (x._M_t == y._M_t);
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator<(const map<Key, _Tp, Compare, _Alloc>& x,
							const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (x._M_t < y._M_t);
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator!=(const map<Key, _Tp, Compare, _Alloc>& x,
							 const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (!(x == y));
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator>(const map<Key, _Tp, Compare, _Alloc>& x,
							const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (y < x);
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator<=(const map<Key, _Tp, Compare, _Alloc>& x,
							 const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (!(y < x));
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline bool
		operator>=(const map<Key, _Tp, Compare, _Alloc>& x,
							 const map<Key, _Tp, Compare, _Alloc>& y)
		{
			return (!(x < y));
		}

	template<typename Key, typename _Tp, typename Compare, typename _Alloc>
		inline void
		swap(map<Key, _Tp, Compare, _Alloc>& x,
	 		 map<Key, _Tp, Compare, _Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
