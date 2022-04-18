#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#pragma 	once

#define _START_FT_NAMESPACE 	namespace ft {
#define _END_FT_NAMESPACE 		}

#include "utils.hpp"

#include <memory>
#include <cstddef>

_START_FT_NAMESPACE

/* iterator base types */
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t, typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator {
	typedef _Category  						iterator_category;
	typedef _Tp        						value_type;
	typedef _Distance  						difference_type;
	typedef _Pointer   						pointer;
	typedef _Reference 						reference;
};

template<class _Iterator>
struct iterator_traits {
	typedef typename _Iterator::iterator_category 	iterator_category;
	typedef typename _Iterator::value_type 			value_type;
	typedef typename _Iterator::difference_type 	difference_type;
	typedef typename _Iterator::pointer 			pointer;
	typedef typename _Iterator::reference 			reference;
};

template<typename _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag 				iterator_category;
  typedef _Tp                         				value_type;
  typedef ptrdiff_t               					difference_type;
  typedef _Tp*                        				pointer;
  typedef _Tp&                        				reference;
};

template<typename _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag 				iterator_category;
  typedef _Tp                        				value_type;
  typedef ptrdiff_t             					difference_type;
  typedef const _Tp*                        		pointer;
  typedef const _Tp&                        		reference;
};

/* ----------------- iterators */
/** normal **/
template<typename _Iterator, typename _Container>
class normal_iterator {
protected:
	_Iterator _current;
public:
	typedef typename iterator_traits<_Iterator>::iterator_category 	iterator_category;
	typedef typename iterator_traits<_Iterator>::value_type			value_type;
	typedef typename iterator_traits<_Iterator>::difference_type 	difference_type;
	typedef typename iterator_traits<_Iterator>::reference 			reference;
	typedef typename iterator_traits<_Iterator>::pointer 			pointer;

	normal_iterator() : _current(_Iterator()) { }
	explicit
	normal_iterator(const _Iterator& _i) : _current(_i) {}

	template<typename _Iter>
	normal_iterator(const normal_iterator<_Iter, typename utils::enable_if<(utils::are_same<_Iter, typename _Container::pointer>::_value), _Container>::type>& _i)
	: _current(_i.base())
	{ }

	normal_iterator&
	operator=(const normal_iterator& _x) {
		_current = _x._current;
		return *this;
	}
	/* operator overload */
	// Forward iterator requirements
	reference			operator*() const		{ return *_current; }
	pointer				operator->() const		{ return _current; }

	normal_iterator&
	operator++() 	{
		++_current;
		return *this;
	}
	normal_iterator		operator++(int)	{ return normal_iterator(_current++); }

	// Bidirectional iterator requirements
	normal_iterator&
	operator--()	{
		--_current;
		return *this;
	}
	normal_iterator		operator--(int)	{ return normal_iterator(_current--); }

	// Random access iterator requirements
	reference
	operator[](const difference_type& _n) const
	{ return _current[_n]; }

	normal_iterator
	operator+(const difference_type& _n) const
	{ return normal_iterator(_current + _n); }
	normal_iterator&
	operator+=(const difference_type& _n) {
		_current += _n;
		return *this;
	}
	normal_iterator
	operator-(const difference_type& _n) const
	{ return normal_iterator(_current - _n); }
	normal_iterator&
	operator-=(const difference_type& _n) {
		_current -= _n;
		return *this;
	}
	const _Iterator&	base() const	{ return _current; }
};
/* non-member functions : comparison operators */
template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator==(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() == _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator==(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() == _ir.base(); }

template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator!=(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() != _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator!=(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() != _ir.base(); }

// Random access iterator requirements
template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator<(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() < _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator<(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() < _ir.base(); }

template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator>(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() > _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator>(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() > _ir.base(); }

template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator<=(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() <= _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator<=(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() <= _ir.base(); }

template<typename _IterL, typename _IterR, typename _Cont>
inline bool
operator>=(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() >= _ir.base(); }
template<typename _Iter, typename _Cont>
inline bool
operator>=(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() >= _ir.base(); }

template<typename _IterL, typename _IterR, typename _Cont>
inline typename normal_iterator<_IterL, _Cont>::difference_type
operator-(const normal_iterator<_IterL, _Cont>& _il, const normal_iterator<_IterR, _Cont>& _ir)
{ return _il.base() - _ir.base(); }
template<typename _Iter, typename _Cont>
inline typename normal_iterator<_Iter, _Cont>::difference_type
operator-(const normal_iterator<_Iter, _Cont>& _il, const normal_iterator<_Iter, _Cont>& _ir)
{ return _il.base() - _ir.base(); }

template<typename _Iterator, typename _Cont>
inline normal_iterator<_Iterator, _Cont>
operator+(typename normal_iterator<_Iterator, _Cont>::difference_type _n, const normal_iterator<_Iterator, _Cont>& _i)
{ return normal_iterator<_Iterator, _Cont>(_i.base() + _n); }

/* operations */
template<typename _Iterator, typename _Distance>
inline void _advance(_Iterator& _iter, _Distance _n, bidirectional_iterator_tag) {
	// bidirectional_iterator_tag : list, set, multiset, map, multimap
	if (_n > 0)		while (_n--)	++_iter;
	else					while (_n++)	--_iter;
}
template<typename _Iterator, typename _Distance>
inline void _advance(_Iterator& _iter, _Distance _n, random_access_iterator_tag) {
	// random_access_iterator_tag : vector, deque
	_iter += _n;
}
template<typename _Iterator, typename _Distance>
inline void advance(_Iterator& _iter, _Distance _n) {
	typename iterator_traits<_Iterator>::difference_type _d = _n;
	_advance(_iter, _d, typename iterator_traits<_Iterator>::iterator_category());
}

template<typename _Iterator>
inline typename iterator_traits<_Iterator>::difference_type
_distance(_Iterator _first, _Iterator _last) {
	typename iterator_traits<_Iterator>::difference_type _n = 0;
	for (;_first != _last; ++_first) _n++;
	return _n;
}
template<typename _Iterator>
inline typename iterator_traits<_Iterator>::difference_type
distance(_Iterator _first, _Iterator _last) {
	return _distance(_first, _last);
}

/** reverse **/
template<typename _Iterator>
class reverse_iterator
: public iterator<typename iterator_traits<_Iterator>::iterator_category,
typename iterator_traits<_Iterator>::value_type,
typename iterator_traits<_Iterator>::difference_type,
typename iterator_traits<_Iterator>::pointer,
typename iterator_traits<_Iterator>::reference>
{
protected:
	_Iterator _current;

public:
	typedef _Iterator												iterator;
	typedef typename iterator_traits<_Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<_Iterator>::reference   		reference;
	typedef typename iterator_traits<_Iterator>::pointer     		pointer;

public:
	reverse_iterator() : _current() { }
	explicit
	reverse_iterator(iterator _x) : _current(_x) { }

	reverse_iterator(const reverse_iterator& _x)
	: _current(_x._current)
	{ }
	template<typename _Iter>
	reverse_iterator(const reverse_iterator<_Iter>& _x)
	: _current(_x.base())
	{ }

	~reverse_iterator() { }

	iterator	base() const			{ return _current; }

	reverse_iterator&
	operator=(const reverse_iterator& _x) {
		_current = _x._current;
		return *this;
	}

	reference
	operator*() const  {
		_Iterator _tmp = _current;
		return *--_tmp;
	}

	pointer		operator->() const 		{ return &(operator*()); }

	reverse_iterator&
	operator++()	{
		--_current;
		return *this;
	}
	reverse_iterator
	operator++(int)	{
		reverse_iterator _tmp = *this;
		--_current;
		return _tmp;
	}

	reverse_iterator&
	operator--() {
		++_current;
		return *this;
	}
	reverse_iterator
	operator--(int)	{
		reverse_iterator _tmp = *this;
		++_current;
		return _tmp;
	}

	reverse_iterator
	operator+(difference_type _n) const
	{ return reverse_iterator(_current - _n); }
	reverse_iterator&
	operator+=(difference_type _n) {
		_current -= _n;
		return *this;
	}

	reverse_iterator
	operator-(difference_type _n) const
	{ return reverse_iterator(_current + _n); }
	reverse_iterator&
	operator-=(difference_type _n) {
		_current += _n;
		return *this;
	}

	reference
	operator[](difference_type _n) const
	{ return *(*this + _n); }
};

/* non-member functions : comparison operators */
template<typename _Iter>
inline bool
operator==(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return _x.base() == _y.base(); }
template<typename _IterL, typename _IterR>
inline bool
operator==(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return _x.base() == _y.base(); }

template<typename _Iter>
inline bool
operator!=(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return !(_x == _y); }
template<typename _IterL, typename _IterR>
inline bool
operator!=(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return !(_x == _y); }

template<typename _Iter>
inline bool
operator<(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return _y.base() < _x.base(); }
template<typename _IterL, typename _IterR>
inline bool
operator<(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return _y.base() < _x.base(); }

template<typename _Iter>
inline bool
operator>(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return _y < _x; }
template<typename _IterL, typename _IterR>
inline bool
operator>(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return _y < _x; }

template<typename _Iter>
inline bool
operator<=(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return !(_x > _y); }
template<typename _IterL, typename _IterR>
inline bool
operator<=(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return !(_x > _y); }

template<typename _Iter>
inline bool
operator>=(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return !(_x < _y); }
template<typename _IterL, typename _IterR>
inline bool
operator>=(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return !(_x < _y); }

template<typename _Iter>
inline typename reverse_iterator<_Iter>::difference_type
operator-(const reverse_iterator<_Iter>& _x, const reverse_iterator<_Iter>& _y)
{ return _y.base() - _x.base(); }
template<typename _IterL, typename _IterR>
inline typename reverse_iterator<_IterL>::difference_type
operator-(const reverse_iterator<_IterL>& _x, const reverse_iterator<_IterR>& _y)
{ return _y.base() - _x.base(); }

template<typename _Iter>
inline reverse_iterator<_Iter>
operator+(typename reverse_iterator<_Iter>::difference_type _n, const reverse_iterator<_Iter>& _x)
{ return reverse_iterator<_Iter>(_x.base() - _n); }

_END_FT_NAMESPACE
#endif
