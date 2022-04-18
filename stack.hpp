#ifndef	_STACK_HPP_
#define	_STACK_HPP_

#include "vector.hpp"

_START_FT_NAMESPACE

template<class _T, class _Sequence = vector<_T> >
class stack {
	typedef typename _Sequence::value_type _Sequence_value_type;
public:
	typedef typename _Sequence::value_type                value_type;
	typedef typename _Sequence::reference                 reference;
	typedef typename _Sequence::const_reference           const_reference;
	typedef typename _Sequence::size_type                 size_type;
	typedef          _Sequence                            container_type;

protected:
	_Sequence _c;

public:
	explicit
	stack(const _Sequence& _c = _Sequence())
	: _c(_c)
	{ }

	bool			empty() const	{ return _c.empty(); }

	size_type		size()	const	{ return _c.size(); }

	reference		top()			{ return _c.back(); }
	const_reference	top()	const	{ return _c.back(); }

	void			push(const value_type& _x)	{ _c.push_back(_x); }

	void			pop()			{ _c.pop_back(); }

	template<typename _Tp1, typename _Seq1>
	friend bool
	operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

	template<typename _Tp1, typename _Seq1>
	friend bool
	operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);
};

template<typename _Tp, typename _Seq>
  inline bool
  operator==(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return _lhs._c == _rhs._c; }

template<typename _Tp, typename _Seq>
  inline bool
  operator<(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return _lhs._c < _rhs._c; }

/// Based on operator==
template<typename _Tp, typename _Seq>
  inline bool
  operator!=(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return !(_lhs == _rhs); }

/// Based on operator<
template<typename _Tp, typename _Seq>
  inline bool
  operator>(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return _rhs < _lhs; }

/// Based on operator<
template<typename _Tp, typename _Seq>
  inline bool
  operator<=(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return !(_rhs < _lhs); }

/// Based on operator<
template<typename _Tp, typename _Seq>
  inline bool
  operator>=(const stack<_Tp, _Seq>& _lhs, const stack<_Tp, _Seq>& _rhs)
  { return !(_lhs < _rhs); }

_END_FT_NAMESPACE

#endif
