#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include "utils.hpp"

namespace	ft
{
	template<typename _Tp, typename _Alloc>
		struct _Vector_base
		{
			private:
				typedef _Alloc								allocator_type;
				typedef typename allocator_type::pointer	pointer;

				struct _Vector_impl
				: public _Alloc
				{
					pointer _M_start;
					pointer _M_finish;
					pointer _M_end_of_storage;

					_Vector_impl (void)
					: allocator_type(), _M_start(), _M_finish(), _M_end_of_storage()
					{}

					_Vector_impl(_Alloc const& a)
					: allocator_type(a), _M_start(), _M_finish(), _M_end_of_storage()
					{}

					void
					_M_swap_data (_Vector_impl& x)
					{
						ft::swap(_M_start, x._M_start);
						ft::swap(_M_finish, x._M_finish);
						ft::swap(_M_end_of_storage, x._M_end_of_storage);
					}
				};

			public:
				allocator_type&
				_M_get_Tp_allocator (void)
				{
					return (*static_cast<allocator_type*>(&this->_M_impl));
				}

				const allocator_type&
				_M_get_Tp_allocator (void) const
				{
					return (*static_cast<const allocator_type*>(&this->_M_impl));
				}

				allocator_type
				get_allocator (void) const
				{
					return (allocator_type(_M_get_Tp_allocator()));
				}

				_Vector_base (void)
				: _M_impl()
				{}

				_Vector_base (const allocator_type& a)
				: _M_impl(a)
				{}

				_Vector_base (size_t n)
				: _M_impl()
				{
					_M_create_storage(n);
				}

				_Vector_base (size_t n, const allocator_type& a)
				: _M_impl(a)
				{
					_M_create_storage(n);
				}

				~_Vector_base (void)
				{
					_M_deallocate(this->_M_impl._M_start,
						this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				}


				_Vector_impl	_M_impl;

				pointer
				_M_allocate (size_t n)
				{
					allocator_type	alloc;
					
					alloc = _M_get_Tp_allocator();
					return n != 0 ? alloc.allocate(n) : pointer();
				}

				void
				_M_deallocate (pointer p, size_t n)
				{
					allocator_type	alloc;
					
					alloc = _M_get_Tp_allocator();
					if (p)
						alloc.deallocate(p, n);
				}

			private:
				void
				_M_create_storage (size_t n)
				{
					this->_M_impl._M_start = this->_M_allocate(n);
					this->_M_impl._M_finish = this->_M_impl._M_start;
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
				}
		};


	template<typename T, typename Alloc = std::allocator<T> >
		class vector
		: protected _Vector_base<T, Alloc>
		{
			typedef _Vector_base<T, Alloc>							_Base;	

			public:
				typedef T											value_type;
				typedef	Alloc										allocator_type;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef ft::normal_iterator<pointer, vector>		iterator;
				typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef ptrdiff_t									difference_type;
				typedef size_t										size_type;

			public:
				explicit vector (const allocator_type& alloc = allocator_type());
				explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
				template <class InputIterator>
					vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
				vector (const vector& x);

				~vector (void);

				vector& operator=	(const vector& x);

				iterator begin (void);
				const_iterator begin (void) const;

				iterator end (void);
				const_iterator end (void) const;

				reverse_iterator rbegin (void);
				const_reverse_iterator rbegin(void) const;

				reverse_iterator rend (void);
				const_reverse_iterator rend(void) const;

				size_type size (void) const;

				size_type max_size (void) const;

				void resize (size_type n, value_type val = value_type());

				size_type capacity (void) const;

				bool empty (void) const;

				void reserve (size_type n);

				reference operator[]	(size_type n);
				const_reference operator[]	(size_type n) const;

				reference at (size_type n);
				const_reference at (size_type n) const;

				reference front (void);
				const_reference front (void) const;

				reference back (void);
				const_reference back(void) const;

				template <class InputIterator>
					void assign (InputIterator first, InputIterator last);
				void assign (size_type n, const value_type& val);

				void push_back (const value_type& val);

				void pop_back (void);

				iterator insert (iterator position, const value_type& val);
				void insert (iterator position, size_type n, const value_type& val);
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last);

				iterator erase (iterator position);
				iterator erase (iterator first, iterator last);

				void swap (vector& x);

				void clear (void);
			

			protected:
				using _Base::_M_allocate;
				using _Base::_M_deallocate;
				using _Base::_M_impl;
				using _Base::_M_get_Tp_allocator;

			private:
				allocator_type	_alloc;

				void
				_M_init_dispatch(size_type n, const value_type& val, true_type)
				{
					this->_M_impl._M_start = _M_allocate(n);
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
					_M_init_fill(n, val);
				}

				template <typename InputIterator>
				void
				_M_init_dispatch(InputIterator first, InputIterator last, false_type)
				{
					typedef typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
					_M_init_range(first, last, IterCategory());
				}

				template<typename InputIterator>
				void
				_M_init_range(InputIterator first, InputIterator last, std::input_iterator_tag)
				{
					try
					{
						for (;first != last; ++first)
							push_back(*first);
					}
					catch(std::exception& e)
					{
						clear();
						throw;
					}
				}

				template<typename ForwardIterator>
				void
				_M_init_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
				{
					const size_type n = ft::distance(first, last);
		
					this->_M_impl._M_start = this->_M_allocate(n);
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
					_M_cpy_range(first, last);
				}

				void
				_M_init_fill(size_type n, const value_type& val)
				{
					pointer	cur = this->_M_impl._M_start;
					try
					{
						for (;n > 0;--n, ++cur)
							_alloc.construct(cur, val);
						this->_M_impl._M_finish = cur;
					}
					catch(std::exception& e)
					{
						_M_deallocate(this->_M_impl._M_start, n * sizeof(val));
						throw;
					}
				}

				template <typename InputIterator>
				void
				_M_cpy_range(InputIterator first, InputIterator last)
				{
					pointer cur = this->_M_impl._M_start;
					try
					{
						for (;first != last; ++first, ++cur)
							_alloc.construct(cur, *first);
						this->_M_impl._M_finish = cur;
					}
					catch(std::exception& e)
					{
						_alloc.destroy(this->_M_impl._M_start);
						throw;
					}
				}

				void
				_M_check_range(size_type n) const
				{
					if (n >= this->size())
						throw std::out_of_range("Index out of range");
				}

				void
				_M_assign_dispatch(size_type n, value_type& val, true_type)
				{
					reserve(n);
					_M_init_fill(n, val);
				}

				template <typename InputIterator>
				void
				_M_assign_dispatch(InputIterator first, InputIterator last, false_type)
				{
					typedef typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
					_M_assign_range(first, last, IterCategory());
				}

				template <typename InputIterator>
				void
				_M_assign_range(InputIterator first, InputIterator last, std::input_iterator_tag)
				{
					try
					{
						for (;first != last; ++first)
							push_back(*first);
					}
					catch(std::exception& e)
					{
						clear();
						throw;
					}
				}

				template <typename InputIterator>
				void
				_M_assign_range(InputIterator first, InputIterator last, std::forward_iterator_tag)
				{
					const size_type n = ft::distance(first, last);
		
					reserve(n);
					_M_cpy_range(first, last);
				}

				iterator
				_M_insert_dispatch(iterator position, size_type n, const value_type& val, true_type)
				{
					long long _n = n;
					long long pos = position.base() - this->_M_impl._M_start;
					reserve(size() + n);
					if (pos == static_cast<long long>(size()))
					{
						for (;n > 0;n--)
							push_back(val);
					}
					else
					{
						this->_M_impl._M_finish += n;
						for (long long i = size() - 1;i >= pos + _n;i--)
							this->at(i) = this->at(i - n);
						for (;n > 0;n--)
							_alloc.construct(this->_M_impl._M_start + pos + n - 1, val);
					}
					return (iterator(this->_M_impl._M_start + pos));
				}

				template <typename InputIterator>
				void
				_M_insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type)
				{
					typedef typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
					_M_insert_range(position, first, last, IterCategory());
				}

				template <typename InputIterator>
				void
				_M_insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
				{
					for (;first != last;first++)
					{
						position = insert(position, *first);
						position++;
					}
				}

				template <typename InputIterator>
				void
				_M_insert_range(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
				{
					if (first != last)
					{
						size_type	n = ft::distance(first, last);
						size_type pos = position.base() - this->_M_impl._M_start;
						reserve(size() + n);
						this->_M_impl._M_finish += n;
						for (size_type i = size() - 1; i >= pos + n;i--)
							this->at(i) = this->at(i - n);
						last--;
						for (;n > 0;n--, last--)
							_alloc.construct(this->_M_impl._M_start + pos + n - 1, *last);
					}
				}
		};
	
	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (const allocator_type& alloc)
	: _Base(alloc)
	{}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (size_type n, const value_type& val, const allocator_type& alloc)
	: _Base(n, alloc)
	{
		_M_init_fill(n, val);
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc)
	: _Base(alloc)
	{
		// Check whether it's an integral type.  If so, it's not an iterator.
		typedef typename ft::is_integral<InputIterator>::type _Integral;
		_M_init_dispatch(first, last, _Integral());
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (const vector& x)
	: _Base(x.size(), x._M_get_Tp_allocator())
	{
		_M_cpy_range(x.begin(), x.end());
	}

	/**
	*  The dtor only erases the elements, and note that if the
	*  elements themselves are pointers, the pointed-to memory is
	*  not touched in any way.  Managing the pointer is the user's
	*  responsibility.
	*/
	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector(void)
	{
		clear();
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>&
	vector<T, Alloc>::operator=	(const vector& x)
	{
		if (&x != this)
			this->assign(x.begin(), x.end());
		return (*this);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::begin (void)
	{
		return (iterator(this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::begin (void) const
	{
		return (const_iterator(this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::end (void)
	{
		return (iterator(this->_M_impl._M_finish));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::end (void) const
	{
		return (const_iterator(this->_M_impl._M_finish));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rbegin (void)
	{
		return (reverse_iterator(end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rbegin(void) const
	{
		return (const_reverse_iterator(end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rend (void)
	{
		return (reverse_iterator(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rend(void) const
	{
		return (const_reverse_iterator(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::size (void) const
	{
		return (size_type(this->_M_impl._M_finish - this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::max_size (void) const
	{
		return (_alloc.max_size());
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::resize (size_type n, value_type val)
	{
		if (n <= size())
		{
			_alloc.destroy(this->_M_impl._M_start + n);
		}
		else
		{
			reserve(n);
			pointer ptr = this->_M_impl._M_start + size();
			for (size_type i = n - size();i > 0;i--, ptr++)
				_alloc.construct(ptr, val);
		}
		this->_M_impl._M_finish = this->_M_impl._M_start + n;
	}

	/**
	*  Returns the total number of elements that the %vector can
	*  hold before needing to allocate more memory.
	*/
	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::capacity (void) const
	{
		return (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_start));
	}

	/**
	*  Returns true if the %vector is empty.  (Thus begin() would
	*  equal end().)
	*/
	template <typename T, typename Alloc>
	bool
	vector<T, Alloc>::empty (void) const
	{
		return (begin() == end());
	}

	/**
	*  The advantage of this function is that if optimal code is a
	*  necessity and the user can determine the number of elements
	*  that will be required, the user can reserve the memory in
	*  %advance, and thus prevent a possible reallocation of memory
	*  and copying of %vector data.
	*/
	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("Greater than maximum size");
		if (n > capacity())
		{
			vector<T> tmp = *this;
			pointer ptr = this->_M_impl._M_start;
			size_type len = this->_M_impl._M_end_of_storage - this->_M_impl._M_start;
			this->_M_impl._M_start = _M_allocate(n);
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
			_M_cpy_range(tmp.begin(), tmp.end());
			_M_deallocate(ptr, len);
		}
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference
	vector<T, Alloc>::operator[] (size_type n)
	{
		return (*(this->_M_impl._M_start + n));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
	vector<T, Alloc>::operator[] (size_type n) const
	{
		return (*(this->_M_impl._M_start + n));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference
	vector<T, Alloc>::at (size_type n)
	{
		_M_check_range(n);
		return (*(this->_M_impl._M_start + n));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
	vector<T, Alloc>::at (size_type n) const
	{
		_M_check_range(n);
		return (*(this->_M_impl._M_start + n));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference
	vector<T, Alloc>::front (void)
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
	vector<T, Alloc>::front (void) const
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference
	vector<T, Alloc>::back (void)
	{
		return (*(end() - 1));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
	vector<T, Alloc>::back(void) const
	{
		return (*(end() - 1));
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	void
	vector<T, Alloc>::assign (InputIterator first, InputIterator last)
	{
		typedef typename ft::is_integral<InputIterator>::type is_int;
		_M_assign_dispatch(first, last, is_int());
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::assign (size_type n, const value_type& val)
	{
		_M_assign_dispatch(n, val, true_type());
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::push_back (const value_type& val)
	{
		reserve(size() + 1);
		_alloc.construct(this->_M_impl._M_finish, val);
		this->_M_impl._M_finish++;
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::pop_back (void)
	{
		this->_M_impl._M_finish--;
		_alloc.destroy(this->_M_impl._M_finish);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::insert (iterator position, const value_type& val)
	{
		return(_M_insert_dispatch(position, 1, val, true_type()));
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val)
	{
		_M_insert_dispatch(position, n, val, true_type());
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	void
	vector<T, Alloc>::insert (iterator position, InputIterator first, InputIterator last)
	{
		typedef typename ft::is_integral<InputIterator>::type is_int;
		_M_insert_dispatch(position, first, last, is_int());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::erase (iterator position)
	{
		if (position == end())
			pop_back();
		else
		{
			size_type pos = position.base() - this->_M_impl._M_start;
			for (pointer cur = this->_M_impl._M_start + pos + 1;cur != this->_M_impl._M_finish;cur++)
				*(cur - 1) = *(cur);
			this->_M_impl._M_finish--;
		}
		return (position);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::erase (iterator first, iterator last)
	{
		if (first != last)
		{
			iterator	tmp = first;
			for (;first != last;last--)
				erase(last - 1);
			first = tmp;
		}
		return (first);
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::swap (vector& x)
	{
		this->_M_impl._M_swap_data(x._M_impl);
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::clear (void)
	{
		erase(begin(), end());
	}


	template <class T, class Alloc>
	bool
	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::itcmp(lhs, rhs));
	}

	template <class T, class Alloc>
	bool
	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool
	operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::itinf(lhs, rhs));
	}

	template <class T, class Alloc>
	bool
	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool
	operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool
	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	inline void
	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
