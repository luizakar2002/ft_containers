#ifndef LIST_HPP
# define LIST_HPP

namespace	ft
{
	namespace	detail
	{
		struct _List_node_base
		{
			_List_node_base*	_M_next;
			_List_node_base*	_M_prev;

			static void
			swap(_List_node_base& x, _List_node_base& y)
			{
				if (x._M_next != &x)
				{
					if (y._M_next != &y)
						{
							ft::swap(x._M_next,y._M_next);
							ft::swap(x._M_prev,y._M_prev);
							x._M_next->_M_prev = x._M_prev->_M_next = &x;
							y._M_next->_M_prev = y._M_prev->_M_next = &y;
						}
					else
						{
							y._M_next = x._M_next;
							y._M_prev = x._M_prev;
							y._M_next->_M_prev = y._M_prev->_M_next = &y;
							x._M_next = x._M_prev = &x;
						}
				}
				else if ( y._M_next != &y )
				{
					x._M_next = y._M_next;
					x._M_prev = y._M_prev;
					x._M_next->_M_prev = x._M_prev->_M_next = &x;
					y._M_next = y._M_prev = &y;
				}
			}

			void
			_M_transfer(_List_node_base* const first,
						_List_node_base* const last)
			{
				if (this != last)
				{
					last->_M_prev->_M_next = this;
					first->_M_prev->_M_next = last;
					this->_M_prev->_M_next = first;

					_List_node_base* const tmp = this->_M_prev;
					this->_M_prev = last->_M_prev;
					last->_M_prev = first->_M_prev;
					first->_M_prev = tmp;
				}
			}

			void
			_M_reverse(void)
			{
				_List_node_base*	tmp;

				tmp = this;
				do
				{
					ft::swap(tmp->_M_next, tmp->_M_prev);
					tmp = tmp->_M_prev;
				}	while (tmp != this);
			}

			void
			_M_hook(_List_node_base* const position)
			{
				this->_M_next = position;
				this->_M_prev = position->_M_prev;
				position->_M_prev->_M_next = this;
				position->_M_prev = this;
			}

			void
			_M_unhook(void)
			{
				_List_node_base* const next_node = this->_M_next;
				_List_node_base* const prev_node = this->_M_prev;
				prev_node->_M_next = next_node;
				next_node->_M_prev = prev_node;
			}
		};
	}

	template <typename _Tp>
		struct _List_node : public detail::_List_node_base
		{
			_Tp		_M_data;

			_Tp*
			_MValptr(void)
			{
				return (&_M_data);
			}

			_Tp const*
			_MValptr(void) const
			{
				return (&_M_data);
			}
		};

	template<typename _Tp>
		struct _List_iterator
		{
			typedef _List_iterator<_Tp>				_Self;
			typedef _List_node<_Tp>					_Node;

			typedef ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef _Tp*							pointer;
			typedef _Tp&							reference;

			detail::_List_node_base*	_M_node;

			_List_iterator (void) : _M_node() {}

			explicit
			_List_iterator(detail::_List_node_base* x)
			: _M_node(x)
			{}

			_Self
			_M_const_cast(void) const
			{
				return (*this);
			}

			reference
			operator*	(void) const
			{
				return (*static_cast<_Node*>(_M_node)->_MValptr());
			}

			pointer
			operator->	(void) const
			{
				return (static_cast<_Node*>(_M_node)->_MValptr());
			}

			_Self&
			operator++	(void)
			{
				_M_node = _M_node->_M_next;
				return (*this);
			}

			_Self
			operator++	(int)
			{
				_Self	tmp;
				
				tmp = *this;
				_M_node = _M_node->_M_next;
				return (tmp);
			}

			_Self&
			operator--	(void)
			{
				_M_node = _M_node->_M_prev;
				return (*this);
			}

			_Self
			operator--	(int)
			{
				_Self	tmp;
				
				tmp = *this;
				_M_node = _M_node->_M_prev;
				return (tmp);
			}

			bool
			operator==	(const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!=	(const _Self& x) const
			{
				return (_M_node != x._M_node);
			}
		};

	template<typename _Tp>
		struct _List_const_iterator
		{
			typedef _List_const_iterator<_Tp>		_Self;
			typedef const _List_node<_Tp>			_Node;
			typedef _List_iterator<_Tp>				iterator;

			typedef ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef const _Tp*						pointer;
			typedef const _Tp&						reference;

			const detail::_List_node_base*	_M_node;

			_List_const_iterator (void)
			: _M_node()
			{}

			explicit
			_List_const_iterator(const detail::_List_node_base* x)
			: _M_node(x)
			{}

			_List_const_iterator(const iterator& x)
			: _M_node(x._M_node)
			{}

			iterator
			_M_const_cast(void) const
			{
				return (iterator(const_cast<detail::_List_node_base*>(_M_node)));
			}

			reference
			operator*	(void) const
			{
				return (*(static_cast<_Node*>(_M_node)->_MValptr()));
			}

			pointer
			operator->	(void) const
			{
				return (static_cast<_Node*>(_M_node)->_MValptr());
			}

			_Self&
			operator++	(void)
			{
				_M_node = _M_node->_M_next;
				return (*this);
			}

			_Self
			operator++	(int)
			{
				_Self	tmp;

				tmp = *this;
				_M_node = _M_node->_M_next;
				return (tmp);
			}

			_Self&
			operator--	(void)
			{
				_M_node = _M_node->_M_prev;
				return (*this);
			}

			_Self
			operator--	(int)
			{
				_Self	tmp;
				
				tmp = *this;
				_M_node = _M_node->_M_prev;
				return (tmp);
			}

			bool
			operator==	(const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!=	(const _Self& x) const
			{
				return (_M_node != x._M_node);
			}
		};

	template <typename _Tp, typename _Alloc>
		class _List_base
		{
			protected:
				typedef typename _Alloc::template
					rebind<_Tp>::other									_Tp_alloc_type;
				typedef _Tp_alloc_type			 						_Tp_alloc_traits;
				typedef typename _Tp_alloc_traits::template
					rebind<_List_node<_Tp> >::other						_Node_alloc_type;
				typedef _Node_alloc_type								_Node_alloc_traits;

				static size_t
				_S_distance(const detail::_List_node_base* first,
				const detail::_List_node_base* last)
				{
					size_t n = 0;
					while (first != last)
					{
						first = first->_M_next;
						++n;
					}
					return (n);
				}

				detail::_List_node_base _M_node;

				struct _List_impl
				: public _Node_alloc_type
				{
					detail::_List_node_base _M_node;

					_List_impl(void)
					: _Node_alloc_type(), _M_node()
					{}

					_List_impl(const _Node_alloc_type& a)
					: _Node_alloc_type(a), _M_node()
					{}
				};

				_List_impl	_M_impl;
				
				size_t _M_node_count (void) const
				{
					return (_S_distance(_M_impl._M_node._M_next,
							&(_M_impl._M_node)));
				}

				typename _Node_alloc_traits::pointer
				_M_get_node(void)
				{
					return (_Node_alloc_traits().allocate(1));
				}

				void
				_M_put_node(typename _Node_alloc_traits::pointer p)
				{
					_Node_alloc_traits().deallocate(p, 1);
				}

				_Node_alloc_type&
				_M_get_Node_allocator(void)
				{
					return (_M_impl);
				}

				const _Node_alloc_type&
				_M_get_Node_allocator(void) const
				{
					return (_M_impl);
				}

			public:
				_List_base (void)
				: _M_impl()
				{
					_M_init();
				}

				_List_base(const _Node_alloc_type& a)
				: _M_impl(a)
				{
					_M_init();
				}

				~_List_base(void)
				{}

				void
				_M_init (void)
				{
					this->_M_impl._M_node._M_next = &this->_M_impl._M_node;
					this->_M_impl._M_node._M_prev = &this->_M_impl._M_node;
				}
		};

	template<typename Val>
		inline bool
		operator==	(const _List_iterator<Val>& x,
				 	const _List_const_iterator<Val>& y)
		{
			return (x._M_node == y._M_node);
		}

	template<typename Val>
		inline bool
		operator!=	(const _List_iterator<Val>& x,
				 const _List_const_iterator<Val>& y)
		{
			return (x._M_node != y._M_node);
		}

	template <typename T, typename Alloc = std::allocator<T> >
	class	list : public _List_base<T, Alloc>
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::_List_iterator<T>						iterator;
			typedef ft::_List_const_iterator<T>					const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;


			explicit list (const allocator_type& alloc = allocator_type());
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <typename InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			list (const list& x);

			~list(void);

			list& operator= (const list& x);

			iterator begin(void);
			const_iterator begin(void) const;

			iterator end(void);
			const_iterator end(void) const;

			reverse_iterator rbegin(void);
			const_reverse_iterator rbegin(void) const;

			reverse_iterator rend(void);
			const_reverse_iterator rend(void) const;

			bool empty(void) const;

			size_type size(void) const;

			size_type max_size(void) const;

			reference front(void);
			const_reference front(void) const;

			reference back(void);
			const_reference back(void) const;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);

			void push_front (const value_type& val);

			void pop_front (void);

			void push_back (const value_type& val);

			void pop_back (void);

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);

			void swap (list& x);

			void resize (size_type n, value_type val = value_type());

			void clear(void);

			void splice (iterator position, list& x);
			void splice (iterator position, list& x, iterator i);
			void splice (iterator position, list& x, iterator first, iterator last);

			void remove (const value_type& val);

			template <class Predicate>
			void remove_if (Predicate pred);
			
			void unique(void);
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred);

			void merge (list& x);
			template <class Compare>
			void merge (list& x, Compare comp);

			void sort(void);
			template <class Compare>
			void sort (Compare comp);

			void reverse(void);

		private:
			typedef _List_base<T, Alloc>				_Base;
			typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
			typedef typename _Base::_Tp_alloc_traits	_Tp_alloc_traits;
			typedef typename _Base::_Node_alloc_type	_Node_alloc_type;
			typedef typename _Base::_Node_alloc_traits	_Node_alloc_traits;

		protected:
			typedef _List_node<T>				 _Node;

			using _Base::_M_impl;
			using _Base::_M_put_node;
			using _Base::_M_get_node;
			using _Base::_M_get_Node_allocator;

			_Node*
			_M_create_node(const value_type& x)
			{
				_Node* p = this->_M_get_node();
				try
				{
					_Tp_alloc_type tmpalloc(_M_get_Node_allocator());
					tmpalloc.construct(p->_MValptr(), x);
				}
				catch(std::exception& e)
				{
					_M_put_node(p);
					throw;
				}
				return (p);
			}

			void
			_M_insert(iterator position, const value_type& x)
			{
				_Node* tmp = _M_create_node(x);
				tmp->_M_hook(position._M_node);
			}

			void
			_M_erase(iterator position)
			{
				position._M_node->_M_unhook();
				_Node* n = static_cast<_Node*>(position._M_node);
				_Tp_alloc_type(_M_get_Node_allocator()).destroy(n->_MValptr());
				_M_put_node(n);
			}

			template <typename InputIterator>
			void
			_M_init(InputIterator first, InputIterator last, false_type)
			{
				for (;first != last;++first)
					push_back(*first);
			}

			void
			_M_init(size_type n, const value_type& val, true_type)
			{
				for (; n; --n)
					push_back(val);
			}

			void
			_M_fill(size_type n, const value_type& val)
			{
				iterator	it;

				it = begin();
				for (; it != end() && n > 0; ++it, --n)
					*it = val;
				if (n > 0)
					insert(end(), n, val);
				else
					erase(it, end());
			}

			void
			_M_transfer(iterator position, iterator first, iterator last)
			{
				position._M_node->_M_transfer(first._M_node, last._M_node);
			}
	};


	template <typename T, typename Alloc>
	list<T, Alloc>::list (const allocator_type& alloc)
	: _Base(alloc)
	{}

	template <typename T, typename Alloc>
	list<T, Alloc>::list (size_type n, const value_type& val, const allocator_type& alloc)
	: _Base(alloc)
	{
		_M_init(n, val, true_type());
	}

	template <typename T, typename Alloc>
	template <typename InputIterator>
	list<T, Alloc>::list (InputIterator first, InputIterator last, const allocator_type& alloc)
	: _Base(alloc)
	{
		typedef typename ft::is_integer<InputIterator>::type is_int;
		_M_init(first, last, is_int());
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::list (const list& src)
	: _Base()
	{
		_M_init(src.begin(), src.end(), false_type());
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::~list (void)
	{
		erase(begin(), end());
	}

	template <typename T, typename Alloc>
	list<T, Alloc>&
	list<T, Alloc>::operator=	(const list& rhs)
	{
		if (this != &(rhs))
			_M_init(rhs.begin(), rhs.end(), false_type());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::begin (void)
	{
		return (iterator(this->_M_impl._M_node._M_next));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::begin (void) const
	{
		return (const_iterator(this->_M_impl._M_node._M_next));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::end (void)
	{
		return (iterator(&this->_M_impl._M_node));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::end (void) const
	{
		return (const_iterator(&this->_M_impl._M_node));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reverse_iterator
	list<T, Alloc>::rbegin (void)
	{
		return (reverse_iterator(this->end()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reverse_iterator
	list<T, Alloc>::rbegin (void) const
	{
		return (const_reverse_iterator(this->end()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reverse_iterator
	list<T, Alloc>::rend (void)
	{
		return (reverse_iterator(this->start()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reverse_iterator
	list<T, Alloc>::rend (void) const
	{
		return (const_reverse_iterator(this->start()));
	}

	template <typename T, typename Alloc>
	bool
	list<T, Alloc>::empty (void) const
	{
		return (this->_M_impl._M_node._M_next == &this->_M_impl._M_node);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::size (void) const
	{
		return (this->_M_node_count());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::max_size (void) const
	{
		return (_M_get_Node_allocator().max_size());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reference
	list<T, Alloc>::front (void)
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reference
	list<T, Alloc>::front (void) const
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reference
	list<T, Alloc>::back (void)
	{
		iterator tmp = end();
		--tmp;
		return (*tmp);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reference
	list<T, Alloc>::back (void) const
	{
		iterator tmp = end();
		--tmp;
		return (*tmp);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::assign (size_type n, const value_type& val)
	{
		_M_fill(n, val);
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	void
	list<T, Alloc>::assign (InputIterator first, InputIterator last)
	{
		typedef typename ft::is_integer<InputIterator>::type is_int;
		_M_init(first, last, is_int());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::push_front (const value_type& val)
	{
		this->_M_insert(begin(), val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::pop_front (void)
	{
		this->_M_erase(begin());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::push_back (const value_type& val)
	{
		this->_M_insert(end(), val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::pop_back (void)
	{	
		this->_M_erase(iterator(this->_M_impl._M_node._M_prev));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::insert (iterator position, const value_type& val)
	{
		this->_M_insert(position, val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::insert (iterator position, size_type n, const value_type& val)
	{
		list<T>		tmp(n, val);

		splice(position, tmp);
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	void
	list<T, Alloc>::insert (iterator position, InputIterator first, InputIterator last)
	{
		list<T>		tmp(first, last);

		splice(position, tmp);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::erase (iterator position)
	{
		iterator	tmp;

		tmp = iterator(position._M_node->_M_next);
		_M_erase(position._M_const_cast());
		return (tmp);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::erase (iterator first, iterator last)
	{
		while (first != last)
			first = erase(first);
		return (last._M_const_cast());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::swap (list& x)
	{
		detail::_List_node_base::swap(this->_M_impl._M_node,
					x._M_impl._M_node);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::resize (size_type n, value_type val)
	{
		size_type	len;

		len = size();
		if (len > n)
		{
			for (;len > n;len--)
				pop_back();
		}
		else if (len < n)
		{
			list	tmp(n - len, val);

			splice(end(), tmp);
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::clear(void)
	{
		erase(begin(), end());
		_Base::_M_init();
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::splice (iterator position, list& x)
	{
		if (x.empty() == 0)
		{
			this->_M_transfer(position._M_const_cast(),
				x.begin(), x.end());
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::splice (iterator position, list& x, iterator i)
	{
		iterator j;

		(void)x;
		j = i._M_const_cast();
		++j;
		if (position == i || position == j)
			return;
		this->_M_transfer(position._M_const_cast(),
				i._M_const_cast(), j);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::splice (iterator position, list& x, iterator first, iterator last)
	{
		(void)x;
		if (first != last)
			this->_M_transfer(position._M_const_cast(),
								first._M_const_cast(),
								last._M_const_cast());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::remove (const value_type& val)
	{
		iterator	it;

		it = begin();
		while (it != end())
		{
			if (*it == val)
				it = erase(it);
			else
				it++;
		}
	}

	template <typename T, typename Alloc>
	template <class Predicate>
	void
	list<T, Alloc>::remove_if (Predicate pred)
	{
		iterator	it;

		it = begin();
		while (it != end())
		{
			if (pred(*it))
				it = erase(it);
			else
				it++;
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::unique (void)
	{
		iterator	it1;
		iterator	it2;

		it1 = begin();
		it2 = begin();
		it2++;
		while (it2 != end())
		{
			if (*it1 == *it2)
				it2 = erase(it2);
			else
			{
				it1++;
				it2++;
			}
		}
	}

	template <typename T, typename Alloc>
	template <class BinaryPredicate>
	void
	list<T, Alloc>::unique (BinaryPredicate binary_pred)
	{
		iterator	it1;
		iterator	it2;

		it1 = begin();
		it2 = begin();
		it2++;
		while (it2 != end())
		{
			if (binary_pred(*it2, *it1))
				it2 = erase(it2);
			else
			{
				it1++;
				it2++;
			}
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::merge (list& x)
	{
		if (this != &(x))
		{
			iterator	first1;
			iterator	last1;
			iterator	first2;
			iterator	last2;
			iterator	next;

			first1 = begin();
			last1 = end();
			first2 = x.begin();
			last2 = x.end();
			try {
				while (first1 != last1 && first2 != last2)
					if (*first2 < *first1)
					{
						next = first2;
						_M_transfer(first1, first2, ++next);
						first2 = next;
					}
					else
						++first1;
				if (first2 != last2)
					_M_transfer(last1, first2, last2);
			}
			catch(std::exception& e)
			{
				throw;
			}
		}
	}

	template <typename T, typename Alloc>
	template <class Compare>
	void
	list<T, Alloc>::merge (list& x, Compare comp)
	{
		if (this != &(x))
		{
			iterator	first1;
			iterator	last1;
			iterator	first2;
			iterator	last2;
			iterator	next;

			first1 = begin();
			last1 = end();
			first2 = x.begin();
			last2 = x.end();
			try {
				while (first1 != last1 && first2 != last2)
					if (comp(*first2, *first1))
					{
						next = first2;
						_M_transfer(first1, first2, ++next);
						first2 = next;
					}
					else
						++first1;
				if (first2 != last2)
					_M_transfer(last1, first2, last2);
			}
			catch(std::exception& e)
			{
				throw;
			}
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::sort (void)
	{
		if (this->_M_impl._M_node._M_next != &this->_M_impl._M_node
		&& this->_M_impl._M_node._M_next->_M_next != &this->_M_impl._M_node)
		{
			list	carry;
			list	tmp[64];
			list*	fill = tmp;
			list*	counter;
			try
			{
				do
				{
					carry.splice(carry.begin(), *this, begin());
					for(counter = tmp;
						counter != fill && !counter->empty();
						++counter)
					{
						counter->merge(carry);
						carry.swap(*counter);
					}
					carry.swap(*counter);
					if (counter == fill)
						++fill;
				}	while ( !empty() );
				for (counter = tmp + 1; counter != fill; ++counter)
					counter->merge(*(counter - 1));
				swap(*(fill - 1));
			}
			catch(std::exception& e)
			{
				this->splice(this->end(), carry);
				for (size_t i = 0; i < sizeof(tmp)/sizeof(tmp[0]); ++i)
					this->splice(this->end(), tmp[i]);
				throw;
			}
		}
	}

	template <typename T, typename Alloc>
	template <class Compare>
	void
	list<T, Alloc>::sort (Compare comp)
	{
		if (this->_M_impl._M_node._M_next != &this->_M_impl._M_node
		&& this->_M_impl._M_node._M_next->_M_next != &this->_M_impl._M_node)
		{
			list	carry;
			list	tmp[64];
			list*	fill = tmp;
			list*	counter;
			try
			{
				do
				{
					carry.splice(carry.begin(), *this, begin());
					for(counter = tmp;
						counter != fill && !counter->empty();
						++counter)
					{
						counter->merge(carry, comp);
						carry.swap(*counter);
					}
					carry.swap(*counter);
					if (counter == fill)
						++fill;
				}	while (!empty());
				for (counter = tmp + 1; counter != fill; ++counter)
					counter->merge(*(counter - 1), comp);
				swap(*(fill - 1));
			}
			catch(std::exception& e)
			{
				this->splice(this->end(), carry);
				for (size_t i = 0; i < sizeof(tmp)/sizeof(tmp[0]); ++i)
					this->splice(this->end(), tmp[i]);
				throw;
			}
		}
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::reverse (void)
	{
		this->_M_impl._M_node._M_reverse();
	}


	template <class T, class Alloc>
	inline bool
	operator==	(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return (ft::itcmp(lhs, rhs));
	}

	template <class T, class Alloc>
	inline bool
	operator!=	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	inline bool
	operator<	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (ft::itinf(lhs, rhs));
	}

	template <class T, class Alloc>
	inline bool
	operator<=	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	inline bool
	operator>	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	inline bool
	operator>=	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template<class T, class Alloc>
	inline void
	swap(list<T, Alloc>& x, list<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
