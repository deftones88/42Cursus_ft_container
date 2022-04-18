#ifndef _PAIR_HPP_
#define _PAIR_HPP_

namespace ft {

	template<class _T1, class _T2>
	struct pair {
	public:
		typedef _T1 	first_type;
		typedef _T2 	second_type;

		first_type 		first;
		second_type 	second;

		pair()
		: first(), second()
		{ }
		pair(const _T1& _a, const _T2& _b)
		: first(_a), second(_b)
		{ }
		template<class _U1, class _U2>
		pair(const pair<_U1, _U2>& _p)
		: first(_p.first), second(_p.second)
		{ }
		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	template<class _T1, class _T2>
	inline pair<_T1,_T2>
	make_pair(_T1 _x, _T2 _y)
	{ return pair<_T1, _T2>(_x, _y); }

	template<class _T1, class _T2>
	inline bool
	operator==(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return _x.first == _y.first && _x.second == _y.second; }

	template<class _T1, class _T2>
	inline bool
	operator<(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return _x.first < _y.first || (!(_y.first < _x.first) && _x.second < _y.second); }

	template<class _T1, class _T2>
	inline bool
	operator!=(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return !(_x == _y); }

	template<class _T1, class _T2>
	inline bool
	operator>(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return _y < _x; }

	template<class _T1, class _T2>
	inline bool
	operator<=(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return !(_y < _x); }

	template<class _T1, class _T2>
	inline bool
	operator>=(const pair<_T1, _T2>& _x, const pair<_T1, _T2>& _y)
	{ return !(_x < _y); }

	template<class Pair>
	struct Select1st : public std::unary_function<Pair, typename Pair::first_type> {
	public:
		typename Pair::first_type&
		operator()(Pair& _x)
		{ return _x.first; }
		const typename Pair::first_type&
		operator()(const Pair& _x) const
		{ return _x.first; }
	};
} /* namespace ft */

#endif
