#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<typename _Tp, typename _Sequence = vector<_Tp> >
		class stack
		{
			typedef typename _Sequence::value_type _Sequence_value_type;

			template<typename _Tp1, typename _Seq1>
				friend bool
				operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

			template<typename _Tp1, typename _Seq1>
				friend bool
				operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

			public:
				typedef typename _Sequence::value_type			value_type;
				typedef typename _Sequence::reference			reference;
				typedef typename _Sequence::const_reference		const_reference;
				typedef typename _Sequence::size_type			size_type;
				typedef	_Sequence								container_type;

			protected:
				_Sequence c;

			public:
				explicit
				stack(const _Sequence& c = _Sequence())
				: c(c)
				{}

				bool
				empty (void) const
				{
					return (c.empty());
				}

				size_type
				size (void) const
				{
					return (c.size());
				}

				reference
				top (void)
				{
					return (c.back());
				}

				const_reference
				top (void) const
				{
					return (c.back());
				}

				void
				push(const value_type& x)
				{
					c.push_back(x);
				}

				void
				pop (void)
				{
					c.pop_back();
				}
		};

	template<typename _Tp, typename _Seq>
		inline bool
		operator==(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (x.c == y.c);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator<(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (x.c < y.c);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator!=(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (!(x == y));
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator>(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (y < x);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator<=(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (!(y < x));
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator>=(const stack<_Tp, _Seq>& x, const stack<_Tp, _Seq>& y)
		{
			return (!(x < y));
		}
}

#endif
