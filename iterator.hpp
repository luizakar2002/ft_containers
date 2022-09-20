#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace	ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
					 typename _Pointer = _Tp*, typename _Reference = _Tp&>
		struct iterator
		{
			typedef _Category	iterator_category;
			typedef _Tp			value_type;
			typedef _Distance	difference_type;
			typedef _Pointer	pointer;
			typedef _Reference	reference;
		};

	template<typename _Iterator>
		struct iterator_traits
		{
			typedef typename _Iterator::iterator_category	iterator_category;
			typedef typename _Iterator::value_type			value_type;
			typedef typename _Iterator::difference_type		difference_type;
			typedef typename _Iterator::pointer				pointer;
			typedef typename _Iterator::reference			reference;
		};

	template<typename _Tp>
		struct iterator_traits<_Tp*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef _Tp							value_type;
			typedef ptrdiff_t					difference_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
		};

	template<typename _Tp>
		struct iterator_traits<const _Tp*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef _Tp							value_type;
			typedef ptrdiff_t					difference_type;
			typedef const _Tp*					pointer;
			typedef const _Tp&					reference;
		};

	template<typename _Iter>
		typename ft::iterator_traits<_Iter>::iterator_category
		iterator_category(const _Iter&)
		{
			return (typename ft::iterator_traits<_Iter>::iterator_category());
		}

	template<typename _Iterator, bool _HasBase>
		struct _Iter_base
		{
			typedef _Iterator iterator_type;
			static iterator_type _S_base(_Iterator it)
			{
				return (it);
			}
		};

	template<typename _Iterator>
		struct _Iter_base<_Iterator, true>
		{
			typedef typename _Iterator::iterator_type iterator_type;
			static iterator_type _S_base(_Iterator it)
			{
				return (it.base());
			}
		};



	template<typename _InputIterator>
		typename ft::iterator_traits<_InputIterator>::difference_type
		distance(_InputIterator first, _InputIterator last,
							 input_iterator_tag)
		{
			typename ft::iterator_traits<_InputIterator>::difference_type n = 0;
			while (first != last)
			{
				++first;
				++n;
			}
			return (n);
		}

	template<typename _RandomAccessIterator>
		typename ft::iterator_traits<_RandomAccessIterator>::difference_type
		distance(_RandomAccessIterator first, _RandomAccessIterator last,
							 random_access_iterator_tag)
		{
			return (last - first);
		}

	template<typename _InputIterator>
		inline
		typename ft::iterator_traits<_InputIterator>::difference_type
		distance(_InputIterator first, _InputIterator last)
		{
			return (ft::distance(first, last,
					 ft::iterator_category(first)));
		}

	template<typename _InputIterator, typename _Distance>
		inline void
		advance(_InputIterator& i, _Distance n, input_iterator_tag)
		{
			while (n--)
				++i;
		}

	template<typename _BidirectionalIterator, typename _Distance>
		inline void
		advance(_BidirectionalIterator& i, _Distance n,
							bidirectional_iterator_tag)
		{
			if (n > 0)
				while (n--)
					++i;
			else
				while (n++)
					--i;
		}

	template<typename _RandomAccessIterator, typename _Distance>
		inline void
		advance(_RandomAccessIterator& i, _Distance n,
							random_access_iterator_tag)
		{
			i += n;
		}

	template<typename _InputIterator, typename _Distance>
		inline void
		advance(_InputIterator& i, _Distance n)
		{
			typename ft::iterator_traits<_InputIterator>::difference_type d = n;
			ft::advance(i, d, ft::iterator_category(i));
		}




	template<typename _Iterator>
		class reverse_iterator
		: public iterator<typename ft::iterator_traits<_Iterator>::iterator_category,
						typename ft::iterator_traits<_Iterator>::value_type,
						typename ft::iterator_traits<_Iterator>::difference_type,
						typename ft::iterator_traits<_Iterator>::pointer,
						typename ft::iterator_traits<_Iterator>::reference>
		{
		protected:
			_Iterator		current;

			typedef ft::iterator_traits<_Iterator>		traits_type;

		public:
			typedef _Iterator								iterator_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
			reverse_iterator(void) : current() {}
			reverse_iterator(iterator_type x) : current(x) {}
			reverse_iterator(const reverse_iterator& x) : current(x.current) {}

			template<typename _Iter>
				reverse_iterator(const reverse_iterator<_Iter>& x) : current(x.base()) {}

			iterator_type
			base(void) const
			{
				return (current);
			}

			reference
			operator*	(void) const
			{
				_Iterator tmp = current;
				return (*(--tmp));
			}

			pointer
			operator->	(void) const
			{
				return (&(operator*()));
			}

			reverse_iterator&
			operator++	(void)
			{
				--current;
				return (*this);
			}

			reverse_iterator
			operator++	(int)
			{
				reverse_iterator tmp = *this;
				--current;
				return (tmp);
			}

			reverse_iterator&
			operator--	(void)
			{
				++current;
				return (*this);
			}

			reverse_iterator
			operator--	(int)
			{
				reverse_iterator tmp = *this;
				++current;
				return (tmp);
			}

			reverse_iterator
			operator+	(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator&
			operator+=	(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator
			operator-	(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator&
			operator-=	(difference_type n)
			{
				current += n;
				return (*this);
			}

			reference
			operator[]	(difference_type n) const
			{
				return (*(*this + n));
			}
		};

	template<typename _Iterator>
		inline bool
		operator==	(const reverse_iterator<_Iterator>& x,
				 const reverse_iterator<_Iterator>& y)
		{
			return (x.base() == y.base());
		}

	template<typename _Iterator>
		inline bool
		operator<	(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{
			return (y.base() < x.base());
		}

	template<typename _Iterator>
		inline bool
		operator!=	(const reverse_iterator<_Iterator>& x,
				 const reverse_iterator<_Iterator>& y)
		{
			return (!(x == y));
		}

	template<typename _Iterator>
		inline bool
		operator>	(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{
			return (y < x);
		}

	template<typename _Iterator>
		inline bool
		operator<=	(const reverse_iterator<_Iterator>& x,
				 const reverse_iterator<_Iterator>& y)
		{
			return (!(y < x));
		}

	template<typename _Iterator>
		inline bool
		operator>=	(const reverse_iterator<_Iterator>& x,
				 const reverse_iterator<_Iterator>& y)
		{
			return (!(x < y));
		}


	template<typename _ItL, typename _ItR>
		inline bool
		operator==	(const reverse_iterator<_ItL>& x,
				 const reverse_iterator<_ItR>& y)
		{
			return (x.base() == y.base());
		}

	template<typename _ItL, typename _ItR>
		inline bool
		operator<	(const reverse_iterator<_ItL>& x,
				const reverse_iterator<_ItR>& y)
		{
			return (y.base() < x.base());
		}

	template<typename _ItL, typename _ItR>
		inline bool
		operator!=	(const reverse_iterator<_ItL>& x,
				 const reverse_iterator<_ItR>& y)
		{
			return (!(x == y));
		}

	template<typename _ItL, typename _ItR>
		inline bool
		operator>	(const reverse_iterator<_ItL>& x,
				const reverse_iterator<_ItR>& y)
		{
			return (y < x);
		}

	template<typename _ItL, typename _ItR>
		inline bool
		operator<=	(const reverse_iterator<_ItL>& x,
				 const reverse_iterator<_ItR>& y)
		{
			return (!(y < x));
		}

	template<typename _ItL, typename _ItR>
		inline bool
		operator>=	(const reverse_iterator<_ItL>& x,
				 const reverse_iterator<_ItR>& y)
		{
			return (!(x < y));
		}
	
	template<typename _Iterator>
		inline typename reverse_iterator<_Iterator>::difference_type
		operator-	(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{
			return (y.base() - x.base());
		}

	template<typename _ItL, typename _ItR>
		inline typename reverse_iterator<_ItL>::difference_type
		operator-	(const reverse_iterator<_ItL>& x,
				const reverse_iterator<_ItR>& y)
		{
			return (y.base() - x.base());
		}

	template<typename _Iterator>
		inline reverse_iterator<_Iterator>
		operator+	(typename reverse_iterator<_Iterator>::difference_type n,
				const reverse_iterator<_Iterator>& x)
		{
			return (reverse_iterator<_Iterator>(x.base() - n));
		}


	template<typename _Iterator, typename _Container>
		class normal_iterator
		{
		protected:
			_Iterator	_M_current;

			typedef ft::iterator_traits<_Iterator>	traits_type;

		public:
			typedef _Iterator									iterator_type;
			typedef typename traits_type::iterator_category		iterator_category;
			typedef typename traits_type::value_type			value_type;
			typedef typename traits_type::difference_type		difference_type;
			typedef typename traits_type::reference				reference;
			typedef typename traits_type::pointer				pointer;

			normal_iterator (void)
			: _M_current(_Iterator())
			{}

			explicit
			normal_iterator(const _Iterator& i)
			: _M_current(i)
			{}

			reference
			operator*	(void) const
			{
				return (*_M_current);
			}

			pointer
			operator->	(void) const
			{
				return (_M_current);
			}

			normal_iterator&
			operator++	(void)
			{
				++_M_current;
				return (*this);
			}

			normal_iterator
			operator++	(int)
			{
				return (normal_iterator(_M_current++));
			}

			normal_iterator&
			operator--	(void)
			{
				--_M_current;
				return (*this);
			}

			normal_iterator
			operator--	(int)
			{
				return (normal_iterator(_M_current--));
			}

			reference
			operator[]	(difference_type n) const
			{
				return (_M_current[n]);
			}

			normal_iterator&
			operator+=	(difference_type n)
			{
				_M_current += n;
				return (*this);
			}

			normal_iterator
			operator+	(difference_type n) const
			{
				return (normal_iterator(_M_current + n));
			}

			normal_iterator&
			operator-=	(difference_type n)
			{
				_M_current -= n; 
				return (*this);
			}

			normal_iterator
			operator-	(difference_type n) const
			{
				return (normal_iterator(_M_current - n));
			}

			const _Iterator&
			base(void) const
			{
				return (_M_current);
			}
		};

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator==	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator==	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator!=	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator!=	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return lhs.base() != rhs.base();
		}

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator<	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator<	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator>	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator>	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator<=	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator<=	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template<typename _ItL, typename _ItR, typename _Container>
		inline bool
		operator>=	(const normal_iterator<_ItL, _Container>& lhs,
					const normal_iterator<_ItR, _Container>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline bool
		operator>=	(const normal_iterator<_Iterator, _Container>& lhs,
					const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		inline typename normal_iterator<_IteratorL, _Container>::difference_type
		operator-	(const normal_iterator<_IteratorL, _Container>& lhs,
					const normal_iterator<_IteratorR, _Container>& rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline typename normal_iterator<_Iterator, _Container>::difference_type
		operator-(const normal_iterator<_Iterator, _Container>& lhs,
				const normal_iterator<_Iterator, _Container>& rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template<typename _Iterator, typename _Container>
		inline normal_iterator<_Iterator, _Container>
		operator+	(typename normal_iterator<_Iterator, _Container>::difference_type
					n, const normal_iterator<_Iterator, _Container>& i)
		{
			return (normal_iterator<_Iterator, _Container>(i.base() + n));
		}
}

#endif
