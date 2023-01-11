/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukarape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:38:12 by lukarape          #+#    #+#             */
/*   Updated: 2022/09/22 20:38:13 by lukarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_CC
# define TREE_CC

# include "binary_tree.hpp"

namespace ft
{

	static _bin_tree_node_base*
	local_bin_tree_increment(_bin_tree_node_base* x) throw ()
	{
		if (x->_M_right != 0)
		{
			x = x->_M_right;
			while (x->_M_left != 0)
				x = x->_M_left;
		}
		else
		{
			_bin_tree_node_base* y = x->_M_parent;
			while (x == y->_M_right)
			{
				x = y;
				y = y->_M_parent;
			}
			if (x->_M_right != y)
				x = y;
		}
		return (x);
	}

	_bin_tree_node_base*
	_bin_tree_increment(_bin_tree_node_base* x) throw ()
	{
		return (local_bin_tree_increment(x));
	}

	const _bin_tree_node_base*
	_bin_tree_increment(const _bin_tree_node_base* x) throw ()
	{
		return (local_bin_tree_increment(const_cast<_bin_tree_node_base*>(x)));
	}

	static _bin_tree_node_base*
	local_bin_tree_decrement(_bin_tree_node_base* x) throw ()
	{
		if (x->_M_color == _S_red
				&& x->_M_parent->_M_parent == x)
			x = x->_M_right;
		else if (x->_M_left != 0)
		{
			_bin_tree_node_base* y = x->_M_left;
			while (y->_M_right != 0)
				y = y->_M_right;
			x = y;
		}
		else
		{
			_bin_tree_node_base* y = x->_M_parent;
			while (x == y->_M_left)
				{
					x = y;
					y = y->_M_parent;
				}
			x = y;
		}
		return (x);
	}

	_bin_tree_node_base*
	_bin_tree_decrement(_bin_tree_node_base* x) throw ()
	{
		return (local_bin_tree_decrement(x));
	}

	const _bin_tree_node_base*
	_bin_tree_decrement(const _bin_tree_node_base* x) throw ()
	{
		return (local_bin_tree_decrement(const_cast<_bin_tree_node_base*>(x)));
	}

	static void
	local_bin_tree_rotate_left(_bin_tree_node_base* const x,
								 _bin_tree_node_base*& root)
	{
		_bin_tree_node_base* const y = x->_M_right;
		x->_M_right = y->_M_left;
		if (y->_M_left !=0)
			y->_M_left->_M_parent = x;
		y->_M_parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_left)
			x->_M_parent->_M_left = y;
		else
			x->_M_parent->_M_right = y;
		y->_M_left = x;
		x->_M_parent = y;
	}

	void
	_bin_tree_rotate_left(_bin_tree_node_base* const x,
					 _bin_tree_node_base*& root)
	{
		local_bin_tree_rotate_left (x, root);
	}

	static void
	local_bin_tree_rotate_right(_bin_tree_node_base* const x,
					 _bin_tree_node_base*& root)
	{
		_bin_tree_node_base* const y = x->_M_left;
		x->_M_left = y->_M_right;
		if (y->_M_right != 0)
			y->_M_right->_M_parent = x;
		y->_M_parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_right)
			x->_M_parent->_M_right = y;
		else
			x->_M_parent->_M_left = y;
		y->_M_right = x;
		x->_M_parent = y;
	}

	void
	_bin_tree_rotate_right(_bin_tree_node_base* const x,
			_bin_tree_node_base*& root)
	{
		local_bin_tree_rotate_right (x, root);
	}

	void
	_bin_tree_insert_and_rebalance(const bool	insert_left,
												_bin_tree_node_base* x,
												_bin_tree_node_base* p,
												_bin_tree_node_base& header) throw ()
	{
		_bin_tree_node_base *& root = header._M_parent;
		x->_M_parent = p;
		x->_M_left = 0;
		x->_M_right = 0;
		x->_M_color = _S_red;
		if (insert_left)
		{
			p->_M_left = x;
			if (p == &header)
			{
				header._M_parent = x;
				header._M_right = x;
			}
			else if (p == header._M_left)
				header._M_left = x;
		}
		else
		{
			p->_M_right = x;

			if (p == header._M_right)
				header._M_right = x;
		}
		while (x != root && x->_M_parent->_M_color == _S_red)
		{
			_bin_tree_node_base* const xpp = x->_M_parent->_M_parent;

			if (x->_M_parent == xpp->_M_left)
			{
				_bin_tree_node_base* const y = xpp->_M_right;
				if (y && y->_M_color == _S_red)
				{
					x->_M_parent->_M_color = _S_black;
					y->_M_color = _S_black;
					xpp->_M_color = _S_red;
					x = xpp;
				}
				else
				{
					if (x == x->_M_parent->_M_right)
					{
						x = x->_M_parent;
						local_bin_tree_rotate_left(x, root);
					}
					x->_M_parent->_M_color = _S_black;
					xpp->_M_color = _S_red;
					local_bin_tree_rotate_right(xpp, root);
				}
			}
			else
			{
				_bin_tree_node_base* const y = xpp->_M_left;
				if (y && y->_M_color == _S_red)
				{
					x->_M_parent->_M_color = _S_black;
					y->_M_color = _S_black;
					xpp->_M_color = _S_red;
					x = xpp;
				}
				else
				{
					if (x == x->_M_parent->_M_left)
					{
						x = x->_M_parent;
						local_bin_tree_rotate_right(x, root);
					}
					x->_M_parent->_M_color = _S_black;
					xpp->_M_color = _S_red;
					local_bin_tree_rotate_left(xpp, root);
				}
			}
		}
		root->_M_color = _S_black;
	}

	_bin_tree_node_base*
	_bin_tree_rebalance_for_erase(_bin_tree_node_base* const z,
						 _bin_tree_node_base& header) throw ()
	{
		_bin_tree_node_base *& root = header._M_parent;
		_bin_tree_node_base *& leftmost = header._M_left;
		_bin_tree_node_base *& rightmost = header._M_right;
		_bin_tree_node_base* y = z;
		_bin_tree_node_base* x = 0;
		_bin_tree_node_base* x_parent = 0;
		if (y->_M_left == 0)
			x = y->_M_right;
		else
			if (y->_M_right == 0)
				x = y->_M_left;
			else
			{
				y = y->_M_right;
				while (y->_M_left != 0)
					y = y->_M_left;
				x = y->_M_right;
			}
		if (y != z)
		{
			z->_M_left->_M_parent = y;
			y->_M_left = z->_M_left;
			if (y != z->_M_right)
				{
					x_parent = y->_M_parent;
					if (x)
						x->_M_parent = y->_M_parent;
					y->_M_parent->_M_left = x;
					y->_M_right = z->_M_right;
					z->_M_right->_M_parent = y;
				}
			else
				x_parent = y;
			if (root == z)
				root = y;
			else if (z->_M_parent->_M_left == z)
				z->_M_parent->_M_left = y;
			else
				z->_M_parent->_M_right = y;
			y->_M_parent = z->_M_parent;
			ft::swap(y->_M_color, z->_M_color);
			y = z;
		}
		else
		{
			x_parent = y->_M_parent;
			if (x)
				x->_M_parent = y->_M_parent;
			if (root == z)
				root = x;
			else
				if (z->_M_parent->_M_left == z)
					z->_M_parent->_M_left = x;
				else
					z->_M_parent->_M_right = x;
			if (leftmost == z)
			{
				if (z->_M_right == 0)
					leftmost = z->_M_parent;
				else
					leftmost = _bin_tree_node_base::_S_minimum(x);
			}
			if (rightmost == z)
			{
				if (z->_M_left == 0)
					rightmost = z->_M_parent;
				else
					rightmost = _bin_tree_node_base::_S_maximum(x);
			}
		}
		if (y->_M_color != _S_red)
		{
			while (x != root && (x == 0 || x->_M_color == _S_black))
				if (x == x_parent->_M_left)
				{
					_bin_tree_node_base* w = x_parent->_M_right;
					if (w->_M_color == _S_red)
					{
						w->_M_color = _S_black;
						x_parent->_M_color = _S_red;
						local_bin_tree_rotate_left(x_parent, root);
						w = x_parent->_M_right;
					}
					if ((w->_M_left == 0 ||
						 w->_M_left->_M_color == _S_black) &&
						(w->_M_right == 0 ||
						 w->_M_right->_M_color == _S_black))
					{
						w->_M_color = _S_red;
						x = x_parent;
						x_parent = x_parent->_M_parent;
					}
					else
					{
						if (w->_M_right == 0
								|| w->_M_right->_M_color == _S_black)
							{
								w->_M_left->_M_color = _S_black;
								w->_M_color = _S_red;
								local_bin_tree_rotate_right(w, root);
								w = x_parent->_M_right;
							}
						w->_M_color = x_parent->_M_color;
						x_parent->_M_color = _S_black;
						if (w->_M_right)
							w->_M_right->_M_color = _S_black;
						local_bin_tree_rotate_left(x_parent, root);
						break;
					}
				}
				else
				{
					_bin_tree_node_base* w = x_parent->_M_left;
					if (w->_M_color == _S_red)
					{
						w->_M_color = _S_black;
						x_parent->_M_color = _S_red;
						local_bin_tree_rotate_right(x_parent, root);
						w = x_parent->_M_left;
					}
					if ((w->_M_right == 0 ||
						 w->_M_right->_M_color == _S_black) &&
						(w->_M_left == 0 ||
						 w->_M_left->_M_color == _S_black))
					{
						w->_M_color = _S_red;
						x = x_parent;
						x_parent = x_parent->_M_parent;
					}
					else
					{
						if (w->_M_left == 0 || w->_M_left->_M_color == _S_black)
						{
							w->_M_right->_M_color = _S_black;
							w->_M_color = _S_red;
							local_bin_tree_rotate_left(w, root);
							w = x_parent->_M_left;
						}
						w->_M_color = x_parent->_M_color;
						x_parent->_M_color = _S_black;
						if (w->_M_left)
							w->_M_left->_M_color = _S_black;
						local_bin_tree_rotate_right(x_parent, root);
						break;
					}
				}
			if (x)
				x->_M_color = _S_black;
		}
		return (y);
	}

	unsigned int
	_bin_tree_black_count(const _bin_tree_node_base* node,
						const _bin_tree_node_base* root) throw ()
	{
		if (node == 0)
			return 0;
		unsigned int sum = 0;
		do
		{
			if (node->_M_color == _S_black)
				++sum;
			if (node == root)
				break;
			node = node->_M_parent;
		}
		while (1);
		return (sum);
	}

}

#endif
