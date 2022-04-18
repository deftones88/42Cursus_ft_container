#ifndef	_MAP_HPP_
#define	_MAP_HPP_

#include "iterator.hpp"
#include "utils.hpp"
#include "pair.hpp"
#include "Rb_tree.hpp"

#include <memory>

_START_FT_NAMESPACE

template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
		typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
class map {
public:
	typedef _Key                                       key_type;
	typedef _Tp                                        mapped_type;
	typedef ft::pair<const _Key, _Tp>         	       value_type;
	typedef _Compare                                   key_compare;
	typedef _Alloc                                     allocator_type;

	class value_compare
	: public std::binary_function<value_type, value_type, bool>	{
	private:
		_Compare _comp;

	public:
		value_compare(_Compare _c)
		: _comp(_c) { }

		bool
		operator()(const value_type& _lhs, const value_type& _rhs) const
		{ return _comp(_lhs.first, _rhs.first); }
	};

private:
	typedef typename _Alloc::template rebind<value_type>::other alloc_type;
	typedef Rb_tree<key_type, value_type, ft::Select1st<value_type>, key_compare, alloc_type> Tree;

	Tree _tree;

public:
	typedef typename alloc_type::pointer        		pointer;
	typedef typename alloc_type::const_pointer  		const_pointer;
	typedef typename alloc_type::reference      		reference;
	typedef typename alloc_type::const_reference		const_reference;
	typedef typename Tree::iterator              		iterator;
	typedef typename Tree::const_iterator        		const_iterator;
	typedef typename Tree::size_type             		size_type;
	typedef typename Tree::difference_type       		difference_type;
	typedef typename Tree::reverse_iterator      		reverse_iterator;
	typedef typename Tree::const_reverse_iterator		const_reverse_iterator;

	// constructor/copy/destroy
	map()
	: _tree(_Compare(), allocator_type())
	{ }

	explicit
	map(const _Compare& _comp, const allocator_type& _a = allocator_type())
	: _tree(_comp, _a)
	{ }

	/** copy **/
	map(const map& _x)
	: _tree(_x._tree)
	{ }

	/** range **/
	template <typename _InputIterator>
	map(_InputIterator _first, _InputIterator _last)
	: _tree(_Compare(), allocator_type())
	{ _tree.insert(_first, _last); }

	template <typename _InputIterator>
	map(_InputIterator _first, _InputIterator _last, const _Compare& _comp, const allocator_type& _a = allocator_type())
	: _tree(_comp, _a)
	{ _tree.insert(_first, _last); }

	map&
	operator=(const map& _x) {
		this->_tree = _x._tree;
		return *this;
	}

	/// Get a copy of the memory allocation object.
	allocator_type
	get_allocator() const
	{ return _tree.get_allocator(); }

	// iterators
	iterator				begin()				{ return _tree.begin(); }
	const_iterator			begin() const		{ return _tree.begin(); }

	iterator				end()				{ return _tree.end(); }
	const_iterator			end() const			{ return _tree.end(); }

	reverse_iterator		rbegin()			{ return _tree.rbegin(); }
	const_reverse_iterator	rbegin() const		{ return _tree.rbegin(); }

	reverse_iterator		rend()				{ return _tree.rend(); }
	const_reverse_iterator	rend() const		{ return _tree.rend(); }

	// capacity
	bool		empty() const		{ return _tree.empty(); }

	size_type	size() const		{ return _tree.size(); }

	size_type	max_size() const	{ return _tree.max_size(); }

	// element access
	mapped_type&
	operator[](const key_type& _k)	{
		return ((_tree.insert(ft::make_pair(_k, mapped_type()))).first)->second;
	}

	// modifiers
	ft::pair<iterator, bool>
	insert(const value_type& _x)
	{ return _tree.insert(_x); }

	iterator
	insert(iterator _position, const value_type& _x)
	{ return _tree.insert(_position, _x); }

	template <typename _InputIterator>
	void
	insert(_InputIterator _first, _InputIterator _last)
	{ _tree.insert(_first, _last); }

	void
	erase(iterator _position)
	{ _tree.erase(_position); }
	size_type
	erase(const key_type& _x)
	{ return _tree.erase(_x); }
	void
	erase(iterator _first, iterator _last)
	{ _tree.erase(_first, _last);}

	void		swap(map& _x)				{ _tree.swap(_x._tree); }

	void		clear()						{ _tree.clear(); }

	// observers
	key_compare
	key_comp() const
	{ return _tree.key_comp(); }

	value_compare
	value_comp() const
	{ return value_compare(_tree.key_comp()); }

	// map operations
	iterator		find(const key_type& _key)		 { return _tree.find(_key); }
	const_iterator	find(const key_type& _key) const { return _tree.find(_key); }

	size_type
	count(const key_type& _x) const
	{ return _tree.find(_x) == _tree.end() ? 0 : 1; }

	iterator
	lower_bound(const key_type& _x)
	{ return _tree.lower_bound(_x); }
	const_iterator
	lower_bound(const key_type& _x) const
	{ return _tree.lower_bound(_x); }

	iterator
	upper_bound(const key_type& _x)
	{ return _tree.upper_bound(_x); }
	const_iterator
	upper_bound(const key_type& _x) const
	{ return _tree.upper_bound(_x); }

	ft::pair<iterator, iterator>
	equal_range(const key_type& _x)
	{ return _tree.equal_range(_x); }
	ft::pair<const_iterator, const_iterator>
	equal_range(const key_type& _x) const
	{ return _tree.equal_range(_x); }

	template <typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool
	operator== (const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

	template <typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool
	operator< (const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

	void
	print()
	{ _tree.printTree(); }
};

template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator==(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return _lhs._tree == _rhs._tree; }

template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator<(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return _lhs._tree < _rhs._tree; }

/// Based on operator==
template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator!=(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return !(_lhs == _rhs); }

/// Based on operator<
template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator>(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return _rhs < _lhs; }

/// Based on operator<
template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator<=(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return !(_rhs < _lhs); }

/// Based on operator<
template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator>=(const map<_Key, _Tp, _Compare, _Alloc>& _lhs, const map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ return !(_lhs < _rhs); }

/// See std::map::swap().
template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline void
swap(map<_Key, _Tp, _Compare, _Alloc>& _lhs, map<_Key, _Tp, _Compare, _Alloc>& _rhs)
{ _lhs.swap(_rhs); }

_END_FT_NAMESPACE

#endif
