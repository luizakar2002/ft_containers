#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include "iterator.hpp"
# include "utils.hpp"
# include "pair.hpp"

namespace ft
{
	enum _bin_tree_color { _S_red = false, _S_black = true };

	struct _bin_tree_node_base
	{
		typedef _bin_tree_node_base* _Base_ptr;
		typedef const _bin_tree_node_base* _Const_Base_ptr;

		_bin_tree_color	_M_color;
		_Base_ptr		_M_parent;
		_Base_ptr		_M_left;
		_Base_ptr		_M_right;

		static _Base_ptr
		_S_minimum (_Base_ptr x)
		{
			while (x->_M_left != 0)
				x = x->_M_left;
			return (x);
		}

		static _Const_Base_ptr
		_S_minimum (_Const_Base_ptr x)
		{
			while (x->_M_left != 0)
				x = x->_M_left;
			return (x);
		}

		static _Base_ptr
		_S_maximum (_Base_ptr x)
		{
			while (x->_M_right != 0)
				x = x->_M_right;
			return (x);
		}

		static _Const_Base_ptr
		_S_maximum (_Const_Base_ptr x)
		{
			while (x->_M_right != 0)
				x = x->_M_right;
			return (x);
		}
	};

	template<typename _Val>
		struct _bin_tree_node : public _bin_tree_node_base
		{
			typedef _bin_tree_node<_Val>* _Link_type;
			_Val _M_value_field;
		};

	_bin_tree_node_base*
	_bin_tree_increment(_bin_tree_node_base* x) throw ();

	const _bin_tree_node_base*
	_bin_tree_increment(const _bin_tree_node_base* x) throw ();

	_bin_tree_node_base*
	_bin_tree_decrement(_bin_tree_node_base* x) throw ();

	const _bin_tree_node_base*
	_bin_tree_decrement(const _bin_tree_node_base* x) throw ();

	template<typename _Tp>
		struct _bin_tree_iterator
		{
			typedef _Tp	value_type;
			typedef _Tp& reference;
			typedef _Tp* pointer;

			typedef std::bidirectional_iterator_tag 		iterator_category;
			typedef ptrdiff_t						difference_type;

			typedef _bin_tree_iterator<_Tp>			_Self;
			typedef _bin_tree_node_base::_Base_ptr	_Base_ptr;
			typedef _bin_tree_node<_Tp>*			_Link_type;

			_bin_tree_iterator (void)
			: _M_node()
			{}

			explicit
			_bin_tree_iterator(_Base_ptr x)
			: _M_node(x)
			{}

			reference
			operator* (void) const
			{
				return (static_cast<_Link_type>(_M_node)->_M_value_field);
			}

			pointer
			operator-> (void) const
			{
				return (ft::addressof(static_cast<_Link_type>(_M_node)->_M_value_field));
			}

			_Self&
			operator++ (void)
			{
				_M_node = _bin_tree_increment(_M_node);
				return (*this);
			}

			_Self
			operator++ (int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_increment(_M_node);
				return (tmp);
			}

			_Self&
			operator-- (void)
			{
				_M_node = _bin_tree_decrement(_M_node);
				return (*this);
			}

			_Self
			operator-- (int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_decrement(_M_node);
				return (tmp);
			}

			bool
			operator== (const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!= (const _Self& x) const
			{
				return (_M_node != x._M_node);
			}

			_Base_ptr _M_node;
	};

	template<typename _Tp>
		struct _bin_tree_const_iterator
		{
			typedef _Tp			value_type;
			typedef const _Tp&	reference;
			typedef const _Tp*	pointer;

			typedef _bin_tree_iterator<_Tp>		iterator;

			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t					difference_type;

			typedef _bin_tree_const_iterator<_Tp>			_Self;
			typedef _bin_tree_node_base::_Const_Base_ptr	_Base_ptr;
			typedef const _bin_tree_node<_Tp>*				_Link_type;

			_bin_tree_const_iterator (void)
			: _M_node()
			{}

			explicit
			_bin_tree_const_iterator (_Base_ptr x)
			: _M_node(x)
			{}

			_bin_tree_const_iterator (const iterator& it)
			: _M_node(it._M_node)
			{}

			iterator
			_M_const_cast (void) const
			{
				return (iterator(const_cast<typename iterator::_Base_ptr>(_M_node)));
			}

			reference
			operator* (void) const
			{
				return (static_cast<_Link_type>(_M_node)->_M_value_field);
			}

			pointer
			operator-> (void) const
			{
				return (ft::addressof(static_cast<_Link_type>(_M_node)->_M_value_field)); }

			_Self&
			operator++ (void)
			{
				_M_node = _bin_tree_increment(_M_node);
				return (*this);
			}

			_Self
			operator++(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_increment(_M_node);
				return (tmp);
			}

			_Self&
			operator-- (void)
			{
				_M_node = _bin_tree_decrement(_M_node);
				return (*this);
			}

			_Self
			operator--(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_decrement(_M_node);
				return (tmp);
			}

			bool
			operator==(const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!=(const _Self& x) const
			{
				return (_M_node != x._M_node);
			}

			_Base_ptr _M_node;
		};

	template<typename _Val>
		inline bool
		operator==(const _bin_tree_iterator<_Val>& x,
							 const _bin_tree_const_iterator<_Val>& y)
		{
			return (x._M_node == y._M_node);
		}

	template<typename _Val>
		inline bool
		operator!=(const _bin_tree_iterator<_Val>& x,
							 const _bin_tree_const_iterator<_Val>& y)
		{
			return (x._M_node != y._M_node);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc = std::allocator<_Val> >
		class _bin_tree
		{
			typedef typename _Alloc::template
				rebind<_bin_tree_node<_Val> >::other _Node_allocator;

			typedef _Node_allocator _Alloc_traits;

		protected:
			typedef _bin_tree_node_base* 		_Base_ptr;
			typedef const _bin_tree_node_base* 	_Const_Base_ptr;
			typedef _bin_tree_node<_Val>* 		_Link_type;
			typedef const _bin_tree_node<_Val>*	_Const_Link_type;

		private:
			struct _Reuse_or_alloc_node
			{
				_Reuse_or_alloc_node(_bin_tree& t)
				: _M_root(t._M_root()), _M_nodes(t._M_rightmost()), _M_t(t)
				{
					if (_M_root)
					{
						_M_root->_M_parent = 0;

						if (_M_nodes->_M_left)
							_M_nodes = _M_nodes->_M_left;
					}
					else
						_M_nodes = 0;
				}

				~_Reuse_or_alloc_node (void)
				{
					_M_t._M_erase(static_cast<_Link_type>(_M_root));
				}

				template<typename Arg>
					_Link_type
					operator()(const Arg& arg)
					{
						_Link_type node = static_cast<_Link_type>(_M_extract());
						if (node)
						{
							_M_t._M_destroy_node(node);
							_M_t._M_construct_node(node, arg);
							return (node);
						}
						return (_M_t._M_create_node(arg));
					}

				private:
				_Base_ptr
				_M_extract (void)
				{
					if (!_M_nodes)
						return (_M_nodes);
					_Base_ptr node = _M_nodes;
					_M_nodes = _M_nodes->_M_parent;
					if (_M_nodes)
					{
						if (_M_nodes->_M_right == node)
						{
							_M_nodes->_M_right = 0;

							if (_M_nodes->_M_left)
							{
								_M_nodes = _M_nodes->_M_left;
								while (_M_nodes->_M_right)
									_M_nodes = _M_nodes->_M_right;
								if (_M_nodes->_M_left)
									_M_nodes = _M_nodes->_M_left;
							}
						}	
						else
						_M_nodes->_M_left = 0;
					}
					else
						_M_root = 0;
					return (node);
				}

				_Base_ptr _M_root;
				_Base_ptr _M_nodes;
				_bin_tree& _M_t;
			};

			struct _Alloc_node
			{
				_Alloc_node(_bin_tree& t)
				: _M_t(t)
				{}

				template<typename Arg>
					_Link_type
					operator()(const Arg& arg) const
					{
						return (_M_t._M_create_node(arg));
					}

				private:
					_bin_tree& _M_t;
			};

		public:
			typedef _Key 				key_type;
			typedef _Val 				value_type;
			typedef value_type* 		pointer;
			typedef const value_type* 	const_pointer;
			typedef value_type& 		reference;
			typedef const value_type& 	const_reference;
			typedef size_t 				size_type;
			typedef ptrdiff_t 			difference_type;
			typedef _Alloc 				allocator_type;

			_Node_allocator&
			_M_get_Node_allocator (void)
			{
				return (*static_cast<_Node_allocator*>(&this->_M_impl));
			}
			
			const _Node_allocator&
			_M_get_Node_allocator (void) const
			{
				return (*static_cast<const _Node_allocator*>(&this->_M_impl));
			}

			allocator_type
			get_allocator (void) const
			{
				return (allocator_type(_M_get_Node_allocator()));
			}

		protected:
			_Link_type
			_M_get_node (void)
			{
				return (_M_get_Node_allocator().allocate(1));
			}

			void
			_M_put_node(_Link_type p)
			{
				_M_get_Node_allocator().deallocate(p, 1);
			}

			void
			_M_construct_node(_Link_type node, const value_type& x)
			{
				try
				{
					get_allocator().construct(ft::addressof(node->_M_value_field), x);
				}
				catch(std::exception &e)
				{
					_M_put_node(node);
					throw;
				}
			}

			_Link_type
			_M_create_node(const value_type& x)
			{
				_Link_type tmp = _M_get_node();
				_M_construct_node(tmp, x);
				return (tmp);
			}

			void
			_M_destroy_node(_Link_type p)
			{
				get_allocator().destroy(ft::addressof(p->_M_value_field));
			}

			void
			_M_drop_node(_Link_type p)
			{
				_M_destroy_node(p);
				_M_put_node(p);
			}

			template<typename _NodeGen>
				_Link_type
				_M_clone_node(_Const_Link_type x, _NodeGen& node_gen)
				{
					_Link_type tmp = node_gen(x->_M_value_field);
					tmp->_M_color = x->_M_color;
					tmp->_M_left = 0;
					tmp->_M_right = 0;
					return (tmp);
				}

			template<typename _Key_compare>
				struct _bin_tree_impl : public _Node_allocator
				{
					_Key_compare			_M_key_compare;
					_bin_tree_node_base		_M_header;
					size_type				_M_node_count;

					_bin_tree_impl (void)
					: _Node_allocator(), _M_key_compare(), _M_header(), _M_node_count(0)
					{
						_M_initialize();
					}

					_bin_tree_impl(const _Key_compare& comp, const _Node_allocator& a)
					: _Node_allocator(a), _M_key_compare(comp), _M_header(),
						_M_node_count(0)
					{
						_M_initialize();
					}

					void
					_M_reset (void)
					{
						this->_M_header._M_parent = 0;
						this->_M_header._M_left = &this->_M_header;
						this->_M_header._M_right = &this->_M_header;
						this->_M_node_count = 0;
					}

				private:
					void
					_M_initialize (void)
					{
						this->_M_header._M_color = _S_red;
						this->_M_header._M_parent = 0;
						this->_M_header._M_left = &this->_M_header;
						this->_M_header._M_right = &this->_M_header;
					}			
				};

			_bin_tree_impl<_Compare> _M_impl;

			_Base_ptr&
			_M_root (void)
			{
				return (this->_M_impl._M_header._M_parent);
			}

			_Const_Base_ptr
			_M_root (void) const
			{
				return (this->_M_impl._M_header._M_parent);
			}

			_Base_ptr&
			_M_leftmost (void)
			{
				return (this->_M_impl._M_header._M_left);
			}

			_Const_Base_ptr
			_M_leftmost (void) const
			{
				return (this->_M_impl._M_header._M_left);
			}

			_Base_ptr&
			_M_rightmost (void)
			{
				return (this->_M_impl._M_header._M_right);
			}

			_Const_Base_ptr
			_M_rightmost (void) const
			{
				return (this->_M_impl._M_header._M_right);
			}

			_Link_type
			_M_begin (void)
			{
				return (static_cast<_Link_type>(this->_M_impl._M_header._M_parent));
			}

			_Const_Link_type
			_M_begin (void) const
			{
				return (static_cast<_Const_Link_type>(this->_M_impl._M_header._M_parent));
			}

			_Base_ptr
			_M_end (void)
			{
				return (&this->_M_impl._M_header);
			}

			_Const_Base_ptr
			_M_end (void) const
			{
				return (&this->_M_impl._M_header);
			}

			static const_reference
			_S_value(_Const_Link_type x)
			{
				return (x->_M_value_field);
			}

			static const _Key&
			_S_key(_Const_Link_type x)
			{
				return (_KeyOfValue()(_S_value(x)));
			}

			static _Link_type
			_S_left(_Base_ptr x)
			{
				return (static_cast<_Link_type>(x->_M_left));
			}

			static _Const_Link_type
			_S_left(_Const_Base_ptr x)
			{
				return (static_cast<_Const_Link_type>(x->_M_left));
			}

			static _Link_type
			_S_right(_Base_ptr x)
			{
				return (static_cast<_Link_type>(x->_M_right));
			}

			static _Const_Link_type
			_S_right(_Const_Base_ptr x)
			{
				return (static_cast<_Const_Link_type>(x->_M_right));
			}

			static const_reference
			_S_value(_Const_Base_ptr x)
			{
				return (static_cast<_Const_Link_type>(x)->_M_value_field);
			}

			static const _Key&
			_S_key(_Const_Base_ptr x)
			{
				return (_KeyOfValue()(_S_value(x)));
			}

			static _Base_ptr
			_S_minimum(_Base_ptr x)
			{
				return (_bin_tree_node_base::_S_minimum(x));
			}

			static _Const_Base_ptr
			_S_minimum(_Const_Base_ptr x)
			{
				return (_bin_tree_node_base::_S_minimum(x));
			}

			static _Base_ptr
			_S_maximum(_Base_ptr x)
			{
				return (_bin_tree_node_base::_S_maximum(x));
			}

			static _Const_Base_ptr
			_S_maximum(_Const_Base_ptr x)
			{
				return (_bin_tree_node_base::_S_maximum(x));
			}

		public:
			typedef _bin_tree_iterator<value_type>			iterator;
			typedef _bin_tree_const_iterator<value_type>	const_iterator;

			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_unique_pos(const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_equal_pos(const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_hint_unique_pos(const_iterator pos,
						const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_hint_equal_pos(const_iterator pos,
					 const key_type& k);

		private:
			template<typename _NodeGen>
				iterator
				_M_insert_(_Base_ptr x, _Base_ptr y,
						 const value_type& v, _NodeGen&);

			iterator
			_M_insert_lower(_Base_ptr y, const value_type& v);

			iterator
			_M_insert_equal_lower(const value_type& x);

			template<typename _NodeGen>
				_Link_type
				_M_copy(_Const_Link_type x, _Base_ptr p, _NodeGen&);

			_Link_type
			_M_copy(_Const_Link_type x, _Base_ptr p)
			{
				_Alloc_node an(*this);
				return (_M_copy(x, p, an));
			}

			void
			_M_erase(_Link_type x);

			iterator
			_M_lower_bound(_Link_type x, _Base_ptr y,
				 const _Key& k);

			const_iterator
			_M_lower_bound(_Const_Link_type x, _Const_Base_ptr y,
				 const _Key& k) const;

			iterator
			_M_upper_bound(_Link_type x, _Base_ptr y,
				 const _Key& k);

			const_iterator
			_M_upper_bound(_Const_Link_type x, _Const_Base_ptr y,
				 const _Key& k) const;

		public:
			_bin_tree (void)
			{}

			_bin_tree(const _Compare& comp,
				 const allocator_type& a = allocator_type())
			: _M_impl(comp, _Node_allocator(a))
			{}

			_bin_tree(const _bin_tree& x)
			: _M_impl(x._M_impl._M_key_compare, x._M_get_Node_allocator())
			{
				if (x._M_root() != 0)
				{
					_M_root() = _M_copy(x._M_begin(), _M_end());
					_M_leftmost() = _S_minimum(_M_root());
					_M_rightmost() = _S_maximum(_M_root());
					_M_impl._M_node_count = x._M_impl._M_node_count;
				}
			}

			~_bin_tree (void)
			{
				_M_erase(_M_begin());
			}

			_bin_tree&
			operator=(const _bin_tree& x);

			_Compare
			key_comp (void) const
			{
				return (_M_impl._M_key_compare);
			}

			iterator
			begin (void)
			{
				return (iterator(this->_M_impl._M_header._M_left));
			}

			const_iterator
			begin (void) const
			{
				return (const_iterator(this->_M_impl._M_header._M_left));
			}

			iterator
			end (void)
			{
				return (iterator(&this->_M_impl._M_header));
			}

			const_iterator
			end (void) const
			{
				return (const_iterator(&this->_M_impl._M_header));
			}

			reverse_iterator
			rbegin (void)
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator
			rbegin (void) const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator
			rend (void)
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator
			rend (void) const
			{
				return (const_reverse_iterator(begin()));
			}

			bool
			empty (void) const
			{
				return (_M_impl._M_node_count == 0);
			}

			size_type
			size (void) const 
			{
				return (_M_impl._M_node_count);
			}

			size_type
			max_size (void) const
			{
				return (_M_get_Node_allocator().max_size());
			}

			void
			swap(_bin_tree& t);

			pair<iterator, bool>
			_M_insert_unique(const value_type& x);

			iterator
			_M_insert_equal(const value_type& x);

			template<typename _NodeGen>
				iterator
				_M_insert_unique_(const_iterator pos, const value_type& x,
							_NodeGen&);

			iterator
			_M_insert_unique_(const_iterator pos, const value_type& x)
			{
				_Alloc_node an(*this);
				return (_M_insert_unique_(pos, x, an));
			}

			template<typename _NodeGen>
				iterator
				_M_insert_equal_(const_iterator pos, const value_type& x,
						 _NodeGen&);

			iterator
			_M_insert_equal_(const_iterator pos, const value_type& x)
			{
				_Alloc_node an(*this);
				return (_M_insert_equal_(pos, x, an));
			}

			template<typename _InputIterator>
				void
				_M_insert_unique(_InputIterator first, _InputIterator last);

			template<typename _InputIterator>
				void
				_M_insert_equal(_InputIterator first, _InputIterator last);

		private:
			void
			_M_erase_aux(const_iterator position);

			void
			_M_erase_aux(const_iterator first, const_iterator last);

		public:
			void
			erase(iterator position)
			{
				_M_erase_aux(position);
			}

			void
			erase(const_iterator position)
			{
				_M_erase_aux(position);
			}

			size_type
			erase(const key_type& x);

			void
			erase(iterator first, iterator last)
			{
				_M_erase_aux(first, last);
			}

			void
			erase(const_iterator first, const_iterator last)
			{
				_M_erase_aux(first, last);
			}

			void
			erase(const key_type* first, const key_type* last);

			void
			clear (void)
			{
				_M_erase(_M_begin());
				_M_impl._M_reset();
			}

			iterator
			find(const key_type& k);

			const_iterator
			find(const key_type& k) const;

			size_type
			count(const key_type& k) const;

			iterator
			lower_bound(const key_type& k)
			{
				return (_M_lower_bound(_M_begin(), _M_end(), k));
			}

			const_iterator
			lower_bound(const key_type& k) const
			{
				return (_M_lower_bound(_M_begin(), _M_end(), k));
			}

			iterator
			upper_bound(const key_type& k)
			{
				return (_M_upper_bound(_M_begin(), _M_end(), k));
			}

			const_iterator
			upper_bound(const key_type& k) const
			{
				return (_M_upper_bound(_M_begin(), _M_end(), k));
			}

			pair<iterator, iterator>
			equal_range(const key_type& k);

			pair<const_iterator, const_iterator>
			equal_range(const key_type& k) const;

			// Debugging.
			bool
			rb_verify (void) const;

		};

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator==(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				 const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator<(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (ft::itinf(x.begin(), x.end(), 
								y.begin(), y.end()));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator!=(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				 const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (!(x == y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator>(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (y < x);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator<=(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				 const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (!(y < x));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline bool
		operator>=(const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
				 const _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			return (!(x < y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		inline void
		swap(_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& x,
	 _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& y)
		{
			x.swap(y);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>&
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		operator=(const _bin_tree& x)
		{
			if (this != &x)
			{
				_Reuse_or_alloc_node roan(*this);
				_M_impl._M_reset();
				_M_impl._M_key_compare = x._M_impl._M_key_compare;
				if (x._M_root() != 0)
				{
					_M_root() = _M_copy(x._M_begin(), _M_end(), roan);
					_M_leftmost() = _S_minimum(_M_root());
					_M_rightmost() = _S_maximum(_M_root());
					_M_impl._M_node_count = x._M_impl._M_node_count;
				}
			}
			return (*this);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
			_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
			_M_insert_(_Base_ptr x, _Base_ptr p,
						const _Val& v,
						_NodeGen& node_gen)
			{
				bool insert_left = (x != 0 || p == _M_end()
									|| _M_impl._M_key_compare(_KeyOfValue()(v),
										_S_key(p)));
				_Link_type z = node_gen(v);
				_bin_tree_insert_and_rebalance(insert_left, z, p,
										this->_M_impl._M_header);
				++_M_impl._M_node_count;
				return (iterator(z));
			}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_insert_lower(_Base_ptr p, const _Val& v)
		{
			bool insert_left = (p == _M_end()
					|| !_M_impl._M_key_compare(_S_key(p),
									_KeyOfValue()(v)));
			_Link_type z = _M_create_node(v);
			_bin_tree_insert_and_rebalance(insert_left, z, p,
						this->_M_impl._M_header);
			++_M_impl._M_node_count;
			return (iterator(z));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_insert_equal_lower(const _Val& v)
		{
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
			{
				y = x;
				x = !_M_impl._M_key_compare(_S_key(x), _KeyOfValue()(v)) ?
							_S_left(x) : _S_right(x);
			}
			return (_M_insert_lower(y, v));
		}

	template<typename _Key, typename _Val, typename _KoV,
		 typename _Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type
			_bin_tree<_Key, _Val, _KoV, _Compare, _Alloc>::
			_M_copy(_Const_Link_type x, _Base_ptr p, _NodeGen& node_gen)
			{
				// Structural copy.  __x and __p must be non-null.
				_Link_type top = _M_clone_node(x, node_gen);
				top->_M_parent = p;
				try
				{
					if (x->_M_right)
						top->_M_right = _M_copy(_S_right(x), top, node_gen);
					p = top;
					x = _S_left(x);
					while (x != 0)
					{
						_Link_type y = _M_clone_node(x, node_gen);
						p->_M_left = y;
						y->_M_parent = p;
						if (x->_M_right)
							y->_M_right = _M_copy(_S_right(x), y, node_gen);
						p = y;
						x = _S_left(x);
					}
				}
				catch(std::exception &e)
				{
					_M_erase(top);
					throw;
				}
				return (top);
			}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		void
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_erase(_Link_type x)
		{
			// Erase without rebalancing.
			while (x != 0)
			{
				_M_erase(_S_right(x));
				_Link_type y = _S_left(x);
				_M_drop_node(x);
				x = y;
			}
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_lower_bound(_Link_type x, _Base_ptr y,
			 const _Key& k)
		{
			while (x != 0)
				if (!_M_impl._M_key_compare(_S_key(x), k))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return (iterator(y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::const_iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_lower_bound(_Const_Link_type x, _Const_Base_ptr y,
			 const _Key& k) const
		{
			while (x != 0)
				if (!_M_impl._M_key_compare(_S_key(x), k))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return (const_iterator(y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_upper_bound(_Link_type x, _Base_ptr y,
			 const _Key& k)
		{
			while (x != 0)
				if (_M_impl._M_key_compare(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return (iterator(y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::const_iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_upper_bound(_Const_Link_type x, _Const_Base_ptr y,
			 const _Key& k) const
		{
			while (x != 0)
				if (_M_impl._M_key_compare(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return (const_iterator(y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::iterator,
	 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::iterator>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		equal_range(const _Key& k)
		{
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
			{
				if (_M_impl._M_key_compare(_S_key(x), k))
					x = _S_right(x);
				else if (_M_impl._M_key_compare(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
				{
					_Link_type xu(x);
					_Base_ptr yu(y);
					y = x, x = _S_left(x);
					xu = _S_right(xu);
					return (pair<iterator,
							iterator>(_M_lower_bound(x, y, k),
							_M_upper_bound(xu, yu, k)));
				}
			}
			return (pair<iterator, iterator>(iterator(y),
											iterator(y)));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::const_iterator,
	 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::const_iterator>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		equal_range(const _Key& k) const
		{
			_Const_Link_type x = _M_begin();
			_Const_Base_ptr y = _M_end();
			while (x != 0)
			{
				if (_M_impl._M_key_compare(_S_key(x), k))
					x = _S_right(x);
				else if (_M_impl._M_key_compare(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
				{
					_Const_Link_type xu(x);
					_Const_Base_ptr yu(y);
					y = x, x = _S_left(x);
					xu = _S_right(xu);
					return (pair<const_iterator,
							const_iterator>(_M_lower_bound(x, y, k),
							_M_upper_bound(xu, yu, k)));
				}
			}
			return (pair<const_iterator, const_iterator>(const_iterator(y),
														const_iterator(y)));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		void
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		swap(_bin_tree& t)
		{
			if (_M_root() == 0)
			{
				if (t._M_root() != 0)
				{
					_M_root() = t._M_root();
					_M_leftmost() = t._M_leftmost();
					_M_rightmost() = t._M_rightmost();
					_M_root()->_M_parent = _M_end();
					_M_impl._M_node_count = t._M_impl._M_node_count;
					t._M_impl._M_reset();
				}
			}
			else if (t._M_root() == 0)
			{
				t._M_root() = _M_root();
				t._M_leftmost() = _M_leftmost();
				t._M_rightmost() = _M_rightmost();
				t._M_root()->_M_parent = t._M_end();
				t._M_impl._M_node_count = _M_impl._M_node_count;
				_M_impl._M_reset();
			}
			else
			{
				ft::swap(_M_root(),t._M_root());
				ft::swap(_M_leftmost(),t._M_leftmost());
				ft::swap(_M_rightmost(),t._M_rightmost());
				_M_root()->_M_parent = _M_end();
				t._M_root()->_M_parent = t._M_end();
				ft::swap(this->_M_impl._M_node_count, t._M_impl._M_node_count);
			}
			ft::swap(this->_M_impl._M_key_compare, t._M_impl._M_key_compare);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr,
	 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_unique_pos(const key_type& k)
		{
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			bool comp = true;
			while (x != 0)
			{
				y = x;
				comp = _M_impl._M_key_compare(k, _S_key(x));
				x = comp ? _S_left(x) : _S_right(x);
			}
			iterator j = iterator(y);
			if (comp)
			{
				if (j == begin())
					return (_Res(x, y));
				else
					--j;
			}
			if (_M_impl._M_key_compare(_S_key(j._M_node), k))
				return (_Res(x, y));
			return (_Res(j._M_node, 0));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr,
	 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_equal_pos(const key_type& k)
		{
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
			{
				y = x;
				x = _M_impl._M_key_compare(k, _S_key(x)) ?
								_S_left(x) : _S_right(x);
			}
			return (_Res(x, y));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::iterator, bool>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_insert_unique(const _Val& v)
		{
			typedef pair<iterator, bool> _Res;
			pair<_Base_ptr, _Base_ptr> res = _M_get_insert_unique_pos(_KeyOfValue()(v));
			if (res.second)
			{
				_Alloc_node an(*this);
				return (_Res(_M_insert_(res.first, res.second, v, an), true));
			}
			return (_Res(iterator(res.first), false));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_insert_equal(const _Val& v)
		{
			pair<_Base_ptr, _Base_ptr> res = _M_get_insert_equal_pos(_KeyOfValue()(v));
			_Alloc_node an(*this);
			return (_M_insert_(res.first, res.second, v, an));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr,
				 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_hint_unique_pos(const_iterator position,
					const key_type& k)
		{
			iterator pos = position._M_const_cast();
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			if (pos._M_node == _M_end())
			{
				if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), k))
					return (_Res(0, _M_rightmost()));
				else
					return (_M_get_insert_unique_pos(k));
			}
			else if (_M_impl._M_key_compare(k, _S_key(pos._M_node)))
			{
				// First, try before...
				iterator before = pos;
				if (pos._M_node == _M_leftmost()) // begin()
					return (_Res(_M_leftmost(), _M_leftmost()));
				else if (_M_impl._M_key_compare(_S_key((--before)._M_node), k))
				{
					if (_S_right(before._M_node) == 0)
						return (_Res(0, before._M_node));
					else
						return (_Res(pos._M_node, pos._M_node));
				}
				else
					return (_M_get_insert_unique_pos(k));
			}
			else if (_M_impl._M_key_compare(_S_key(pos._M_node), k))
			{
				// ... then try after.
				iterator after = pos;
				if (pos._M_node == _M_rightmost())
					return (_Res(0, _M_rightmost()));
				else if (_M_impl._M_key_compare(k, _S_key((++after)._M_node)))
				{
					if (_S_right(pos._M_node) == 0)
						return (_Res(0, pos._M_node));
					else
						return (_Res(after._M_node, after._M_node));
				}
				else
					return (_M_get_insert_unique_pos(k));
			}
			else
				return (_Res(pos._M_node, 0));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
			_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
			_M_insert_unique_(const_iterator position,
			const _Val& v,
			_NodeGen& node_gen)
		{
			pair<_Base_ptr, _Base_ptr> res = _M_get_insert_hint_unique_pos(position, _KeyOfValue()(v));
			if (res.second)
				return (_M_insert_(res.first, res.second, v, node_gen));
			return (iterator(res.first));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		pair<typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr,
				 typename _bin_tree<_Key, _Val, _KeyOfValue,
				 _Compare, _Alloc>::_Base_ptr>
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_hint_equal_pos(const_iterator position, const key_type& k)
		{
			iterator pos = position._M_const_cast();
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			if (pos._M_node == _M_end())
			{
				if (size() > 0 && !_M_impl._M_key_compare(k, _S_key(_M_rightmost())))
					return (_Res(0, _M_rightmost()));
				else
					return (_M_get_insert_equal_pos(k));
			}
			else if (!_M_impl._M_key_compare(_S_key(pos._M_node), k))
			{
				iterator before = pos;
				if (pos._M_node == _M_leftmost())
					return (_Res(_M_leftmost(), _M_leftmost()));
				else if (!_M_impl._M_key_compare(k, _S_key((--before)._M_node)))
				{
					if (_S_right(before._M_node) == 0)
						return (_Res(0, before._M_node));
					else
						return (_Res(pos._M_node, pos._M_node));
				}
				else
					return (_M_get_insert_equal_pos(k));
			}
			else
			{
				iterator after = pos;
				if (pos._M_node == _M_rightmost())
					return (_Res(0, _M_rightmost()));
				else if (!_M_impl._M_key_compare(_S_key((++after)._M_node), k))
				{
					if (_S_right(pos._M_node) == 0)
						return (_Res(0, pos._M_node));
					else
						return (_Res(after._M_node, after._M_node));
				}
				else
					return (_Res(0, 0));
			}
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
			_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
			_M_insert_equal_(const_iterator position,
					 const _Val& v,
					 _NodeGen& node_gen)
			{
				pair<_Base_ptr, _Base_ptr> res = _M_get_insert_hint_equal_pos(position, _KeyOfValue()(v));
				if (res.second)
					return (_M_insert_(res.first, res.second, v, node_gen));
				return (_M_insert_equal_lower(v));
			}

	template<typename _Key, typename _Val, typename _KoV,
					 typename _Cmp, typename _Alloc>
		template<class _II>
			void
			_bin_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
			_M_insert_unique(_II first, _II last)
			{
				_Alloc_node an(*this);
				for (; first != last; ++first)
					_M_insert_unique_(end(), *first, an);
			}

	template<typename _Key, typename _Val, typename _KoV,
					 typename _Cmp, typename _Alloc>
		template<class _II>
			void
			_bin_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
			_M_insert_equal(_II first, _II last)
			{
				_Alloc_node an(*this);
				for (; first != last; ++first)
					_M_insert_equal_(end(), *first, an);
			}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		void
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_erase_aux(const_iterator position)
		{
			_Link_type y = static_cast<_Link_type>(_bin_tree_rebalance_for_erase
							(const_cast<_Base_ptr>(position._M_node),
				 				this->_M_impl._M_header));
			_M_drop_node(y);
			--_M_impl._M_node_count;
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		void
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_erase_aux(const_iterator first, const_iterator last)
		{
			if (first == begin() && last == end())
				clear();
			else
				while (first != last)
					erase(first++);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		erase(const _Key& x)
		{
			pair<iterator, iterator> p = equal_range(x);
			const size_type old_size = size();
			erase(p.first, p.second);
			return old_size - size();
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		void
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		erase(const _Key* first, const _Key* last)
		{
			while (first != last)
				erase(*first++);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		find(const _Key& k)
		{
			iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return ((j == end()
				|| _M_impl._M_key_compare(k,
					_S_key(j._M_node))) ? end() : j);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue,
					_Compare, _Alloc>::const_iterator
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		find(const _Key& k) const
		{
			const_iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return ((j == end()
				|| _M_impl._M_key_compare(k, 
					_S_key(j._M_node))) ? end() : j);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		typename _bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
		_bin_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		count(const _Key& k) const
		{
			pair<const_iterator, const_iterator> p = equal_range(k);
			const size_type n = ft::distance(p.first, p.second);
			return (n);
		}

	unsigned int
	_bin_tree_black_count(const _bin_tree_node_base* node,
						  const _bin_tree_node_base* root) throw ();

	template<typename _Key, typename _Val, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
		bool
		_bin_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::rb_verify (void) const
		{
			if (_M_impl._M_node_count == 0 || begin() == end())
				return (_M_impl._M_node_count == 0 && begin() == end()
					 && this->_M_impl._M_header._M_left == _M_end()
					 && this->_M_impl._M_header._M_right == _M_end());
			unsigned int len = _bin_tree_black_count(_M_leftmost(), _M_root());
			for (const_iterator it = begin(); it != end(); ++it)
			{
				_Const_Link_type x = static_cast<_Const_Link_type>(it._M_node);
				_Const_Link_type L = _S_left(x);
				_Const_Link_type R = _S_right(x);
				if (x->_M_color == _S_red)
					if ((L && L->_M_color == _S_red)
						|| (R && R->_M_color == _S_red))
						return (false);
				if (L && _M_impl._M_key_compare(_S_key(x), _S_key(L)))
					return (false);
				if (R && _M_impl._M_key_compare(_S_key(R), _S_key(x)))
					return (false);

				if (!L && !R && _bin_tree_black_count(x, _M_root()) != len)
					return (false);
			}
			if (_M_leftmost() != _bin_tree_node_base::_S_minimum(_M_root()))
				return (false);
			if (_M_rightmost() != _bin_tree_node_base::_S_maximum(_M_root()))
				return (false);
			return (true);
		}

}

#endif

#include "tree.cc"
