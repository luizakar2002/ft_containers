#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <deque>

namespace ft
{
	template<typename _Tp, typename _Sequence = std::deque<_Tp> >
		class queue
		{
			typedef typename _Sequence::value_type _Sequence_value_type;

			template<typename _Tp1, typename _Seq1>
				friend bool
				operator==(const queue<_Tp1, _Seq1>&, const queue<_Tp1, _Seq1>&);

			template<typename _Tp1, typename _Seq1>
				friend bool
				operator<(const queue<_Tp1, _Seq1>&, const queue<_Tp1, _Seq1>&);

			public:
				typedef typename _Sequence::value_type			value_type;
				typedef typename _Sequence::reference			reference;
				typedef typename _Sequence::const_reference		const_reference;
				typedef typename _Sequence::size_type			size_type;
				typedef _Sequence								container_type;

			protected:
				_Sequence c;

			public:
				explicit
				queue(const _Sequence& c = _Sequence())
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
				front (void)
				{
					return (c.front());
				}

				const_reference
				front (void) const
				{
					return (c.front());
				}

				reference
				back (void)
				{
					return (c.back());
				}

				const_reference
				back (void) const
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
					c.pop_front();
				}
		};

	template<typename _Tp, typename _Seq>
		inline bool
		operator==(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (x.c == y.c);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator<(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (x.c < y.c);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator!=(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (!(x == y));
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator>(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (y < x);
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator<=(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (!(y < x));
		}

	template<typename _Tp, typename _Seq>
		inline bool
		operator>=(const queue<_Tp, _Seq>& x, const queue<_Tp, _Seq>& y)
		{
			return (!(x < y));
		}
}

#endif
