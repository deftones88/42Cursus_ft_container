#ifndef	_VECTOR_HPP_
#define	_VECTOR_HPP_

#include "iterator.hpp"
#include "utils.hpp"

#include <memory>
#include <cstddef>
#include <iostream>

_START_FT_NAMESPACE

/* base class */
template<typename _Tp, typename Alloc>
struct VectorBase {

	typedef typename Alloc::template rebind<_Tp>::other Tp_alloc_type;

	struct Vector_impl : public Tp_alloc_type {
		_Tp*           _start;					// begin(address)
		_Tp*           _finish;					// end(size)
		_Tp*           _end_of_storage;			// capacity

		Vector_impl(Tp_alloc_type const& _alloc)
		: Tp_alloc_type(_alloc), _start(0), _finish(0), _end_of_storage(0)
		{ }
	};
public:
	Vector_impl _impl;

	_Tp*
	allocate(size_t _n)
	{ return  _impl.allocate(_n); }
	void
	deallocate(_Tp* _p, size_t _n)
	{ if (_p) _impl.deallocate(_p, _n);	}

public:
	Tp_alloc_type&
	get_Tp_allocator()
	{ return *static_cast<Tp_alloc_type*>(&this->_impl); }
	const Tp_alloc_type&
	get_Tp_allocator() const
	{ return *static_cast<const Tp_alloc_type*>(&this->_impl); }

	typedef Alloc allocator_type;

	allocator_type
	get_allocator() const
	{ return allocator_type( get_Tp_allocator() ); }

	VectorBase(const allocator_type& _alloc)
	: _impl(_alloc)
	{ }
	VectorBase(size_t _n, const allocator_type& _alloc)
	: _impl(_alloc)	{
		if (_n) {
			this->_impl._start = this->allocate(_n);
			this->_impl._finish = this->_impl._start;
			this->_impl._end_of_storage = this->_impl._start + _n;
		}
	}
	~VectorBase() {
		deallocate(this->_impl._start, this->_impl._end_of_storage - this->_impl._start);
	}
};

/* vector class */
template<typename _Tp, typename Alloc = std::allocator<_Tp> >
class vector : protected VectorBase<_Tp, Alloc> {

	typedef VectorBase<_Tp, Alloc>			 	Base;
	typedef vector<_Tp, Alloc>			 		vector_type;
	typedef typename Base::Tp_alloc_type		alloc_type;

public:
	typedef _Tp												value_type;
	typedef typename alloc_type::pointer           			pointer;
	typedef typename alloc_type::const_pointer     			const_pointer;
	typedef typename alloc_type::reference         			reference;
	typedef typename alloc_type::const_reference   			const_reference;
	typedef normal_iterator<pointer, vector_type> 	 		iterator;
	typedef normal_iterator<const_pointer, vector_type>		const_iterator;
	typedef reverse_iterator<const_iterator>		  		const_reverse_iterator;
	typedef reverse_iterator<iterator>				 		reverse_iterator;
	typedef size_t					 						size_type;
	typedef ptrdiff_t										difference_type;
	typedef Alloc                        					allocator_type;

protected:
	using Base::allocate;
	using Base::deallocate;
	using Base::_impl;
	using Base::get_allocator;

public:
	/* construct/copy/destroy */
	explicit
	vector(const allocator_type& _alloc = allocator_type())
	: Base(_alloc)
	{ }
	explicit
	vector(size_type _n, const value_type& _value = value_type(), const allocator_type& _alloc = allocator_type())
	: Base(_n, _alloc) {
		while (_n--)
			this->_impl.construct(this->_impl._finish++, value_type(_value));
	}
	template <class _InputIterator>
	vector (_InputIterator _first, _InputIterator _last, const allocator_type& _alloc = allocator_type())
	: Base(_alloc) {
		typedef typename utils::is_integral<_InputIterator>::_type _Integral;
		_assign_dispatch(_first, _last, _Integral());
	}
	// copy constructor
	vector(const vector& _x)
	: Base(_x.capacity(), _x.get_allocator()) {
		for (size_t i = 0; i < _x.size(); i++) {
			this->_impl.construct(this->_impl._finish++, _x[i]);
		}
	}
	// destructor
	~vector() {
		Destroy(this->_impl._start, this->_impl._finish, get_allocator());
 	}
	/** sub func : Destroy **/
	void
	Destroy(pointer _start, pointer _finish, alloc_type _alloc) {
		for (pointer it = _start; it != _finish; ++it)
			_alloc.destroy(it);
	}

	vector&
	operator=(const vector& _x) {
		if (&_x != this) {
			const size_type _n = _x.size();
			if (_n < size()) 			erase_at_end(this->_impl._start + _n);
			else						reserve(_n);
			this->_impl._finish = this->_impl._start + _n;
			uninitialized_copy(_x.begin(), _x.end(), this->_impl._start, get_allocator());
		}
		return *this;
	}
	/** sub func : uninitialized_copy **/
	template<class _InputIt, class _OutputIt>
	_OutputIt
	uninitialized_copy(_InputIt _src_start, _InputIt _src_finish, _OutputIt _des_start, alloc_type _alloc) {
		for (; _src_start != _src_finish; ++_src_start, (void) ++_des_start)
			_alloc.construct(_des_start, *_src_start);
		return _des_start;
	}

	void
	assign(size_type _n, const value_type& _val) {
		if (_n < capacity()) {
			vector _tmp(_n, _val, get_allocator());
			_tmp.swap(*this);
		} else {
			if (_n < size()) 			erase_at_end(this->_impl._start + _n);
			else						reserve(_n);
			this->_impl._finish = this->_impl._start + _n;
			for (pointer it = this->_impl._start; it != this->_impl._finish + 1; ++it)
				this->_impl.construct(it, value_type(_val));
		}
	}
	template<typename _InputIterator>
	void
	assign(_InputIterator _first, _InputIterator _last)	{
		typedef typename utils::is_integral<_InputIterator>::_type _Integral;
		_assign_dispatch(_first, _last, _Integral());
	}
	template<typename _Integer>
	void
	_assign_dispatch(_Integer _n, _Integer _val, utils::_true_type)
	{ assign(static_cast<size_type>(_n), static_cast<value_type>(_val)); }
	template<typename _InputIterator>
	void
	_assign_dispatch(_InputIterator _first, _InputIterator _last, utils::_false_type) {
		size_type _dist = ft::distance(_first, _last);
		if (_dist < size()) 	erase_at_end(this->_impl._start + _dist);
		else					reserve(_dist);
		this->_impl._finish = this->_impl._start;
		for (; _first != _last; ++_first)
			this->_impl.construct(this->_impl._finish++, value_type(*_first));
	}

	/* iterators */
	iterator
	begin()
	{ return iterator(this->_impl._start); }
	const_iterator
	begin() const
	{ return const_iterator(this->_impl._start); }

	iterator
	end()
	{ return iterator(this->_impl._finish); }
	const_iterator
	end() const
	{ return const_iterator(this->_impl._finish); }

	reverse_iterator
	rbegin()
	{ return reverse_iterator(end()); }
	const_reverse_iterator
	rbegin() const
	{ return const_reverse_iterator(end()); }

	reverse_iterator
	rend()
	{ return reverse_iterator(begin()); }
	const_reverse_iterator
	rend() const
	{ return const_reverse_iterator(begin()); }

	/* capacity */
	size_type
	size() const
	{ return size_type(this->_impl._finish - this->_impl._start); }

	size_type
	max_size() const
	{	return get_allocator().max_size(); }

	size_type
	capacity() const
	{ return size_type(this->_impl._end_of_storage - this->_impl._start); }

	bool	empty() const				{ return begin() == end(); }

	void
	reserve(size_type _n) {
		if (_n > this->max_size())
			throw std::out_of_range("vector::reserve (number too large)");
		if (this->capacity() < _n) {
			const size_type _s = size();
			pointer _tmp = allocate_and_copy(_n, this->_impl._start, this->_impl._finish);
			Destroy(this->_impl._start, this->_impl._finish, get_allocator());
			deallocate(this->_impl._start, this->_impl._end_of_storage - this->_impl._start);
			this->_impl._start = _tmp;
			this->_impl._finish = _tmp + _s;
			this->_impl._end_of_storage = this->_impl._start + _n;
		}
	}
	/** sub func : allocate_and_copy **/
	pointer
	allocate_and_copy(size_type _n, pointer _start, pointer _finish)
	{
		alloc_type _alloc = get_allocator();
		pointer _tmp = _alloc.allocate(_n);
		pointer _tmp_it = _tmp;
		for (pointer it = _start; it != _finish; ++it)
			_alloc.construct(_tmp_it++, value_type(*it));
		return _tmp;
	}

	/* element access */
protected:
	/** sub func : range_check **/
	void
	range_check(size_type _n) const {
		if (_n >= this->size())
		 throw std::out_of_range("vector::range_check");
	}
public:
	reference
	at(size_type _n) {
		range_check(_n);
		return (*this)[_n];
	}
	const_reference
	at(size_type _n) const {
		range_check(_n);
		return (*this)[_n];
	}

	reference
	operator[](size_type _n)
	{ return *(this->_impl._start + _n); }
	const_reference
	operator[](size_type _n) const { return *(this->_impl._start + _n); }

	reference		front()						{ return *begin(); }
	const_reference	front() const				{ return *begin(); }

	reference		back()						{ return *(end() - 1); }
	const_reference	back() const				{ return *(end() - 1); }

	/* data  access */
	pointer			data()			{ return pointer(this->_impl._start); }
	const_pointer	data() const	{ return const_pointer(this->_impl._start); }

	/* modifiers */

	void
	push_back(const value_type& _x)	{
		if (this->_impl._finish != this->_impl._end_of_storage) {
			this->_impl.construct(this->_impl._finish, _x);
			++this->_impl._finish;
		}
		else
			insert_aux(end(), _x);
	}
	/** sub func : insert_aux **/
	void
	insert_aux(iterator _position, const value_type& _x) {
		size_type _old_size = size();
		if (_old_size == this->max_size())
			throw std::length_error("vector::insert_aux\n");
		size_type _new_size = _old_size != 0 ? 2 * _old_size : 1;
		if (_new_size < _old_size)			_new_size = this->max_size();

		pointer _tmp = allocate(_new_size);
		pointer _new_finish = _tmp;
		pointer _oit;
		try {
			for (_oit = this->_impl._start; _oit != _position.base(); ++_oit)
				get_allocator().construct(_new_finish++, *_oit);
			this->_impl.construct(_new_finish, _x);
			++_new_finish;
			for (_oit = _position.base(); _oit != this->_impl._finish; ++_oit)
				get_allocator().construct(_new_finish++, *_oit);
		} catch (...) {
			Destroy(_tmp, _new_finish, get_allocator());
			deallocate(_tmp, _new_size);
			throw std::length_error("vector::insert_aux\n");
		}
		Destroy(this->_impl._start, this->_impl._finish, get_allocator());
		deallocate(this->_impl._start, this->_impl._end_of_storage - this->_impl._start);
		this->_impl._start = _tmp;
		this->_impl._finish = _new_finish;
		this->_impl._end_of_storage = _tmp + _new_size;
	}

	void
	pop_back() {
		--this->_impl._finish;
		this->_impl.destroy(this->_impl._finish);
	}
	/** insert : single element **/
	iterator
	insert(iterator _position, const value_type& _x) {
		const size_type _n = _position - begin();
		if (this->_impl._finish != this->_impl._end_of_storage && _position == end())
		{
			this->_impl.construct(this->_impl._finish, _x);
			++this->_impl._finish;
		}
		else
			insert_aux(_position, _x);
		return iterator(this->_impl._start + _n);
	}
	/** insert : fill **/
	void
	insert(iterator _position, size_type _n, const value_type& _x) {
		if (_n != 0)	{
			difference_type _elems = _position - begin();
			reserve(size() + _n);
			pointer _move;
			pointer _end = this->_impl._start + _elems + _n - 1;
			for (_move = this->_impl._finish + _n - 1; _move != _end; --_move)
				*_move = *(_move - _n);
			for (; _move >= this->_impl._start + _elems; --_move)
				this->_impl.construct(_move, value_type(_x));
			this->_impl._finish += _n;
		}
	}
	/** insert : range **/
	template<typename _InputIterator>
	void
	insert(iterator _position, _InputIterator _first,
		typename utils::enable_if<!(utils::are_same<typename _InputIterator::iterator_category,
		void>::_value), _InputIterator>::type _last)
	{
		for (; _first != _last; ++_first) {
			_position = insert(_position, *_first);
			++_position;
		}
	}

	void
	resize(size_type _new_size, value_type _x = value_type())	{
		if (_new_size < size())
			erase_at_end(this->_impl._start + _new_size);
		else
			insert(end(), _new_size - size(), _x);
	}

	iterator
	erase(iterator _position) {
		if (_position + 1 != end())
			utils::copy(_position + 1, end(), _position);
		--this->_impl._finish;
		this->_impl.destroy(this->_impl._finish);
		return _position;
	}
	iterator
	erase(iterator _start, iterator _finish) {
		if (_finish != end())
			utils::copy(_finish, end(), _start);
		erase_at_end(_start.base() + (end() - _finish));
		return _start;
	}

	void
	swap(vector& _x) {
		std::swap(this->_impl._start, _x._impl._start);
		std::swap(this->_impl._finish, _x._impl._finish);
		std::swap(this->_impl._end_of_storage, _x._impl._end_of_storage);
	}

	void
	clear() {
		erase_at_end(this->_impl._start);
	}
	/** sub func : erase_at_end **/
	void
	erase_at_end(pointer _pos) {
		Destroy(_pos, this->_impl._finish, get_allocator());
		this->_impl._finish = _pos;
	}
};

/* non-member functions : comparison operators */
template<typename _Tp, typename _Alloc>
inline bool
operator==(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return (_lhs.size() == _rhs.size() && utils::equal(_lhs.begin(), _lhs.end(), _rhs.begin())); }

template<typename _Tp, typename _Alloc>
inline bool
operator<(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return utils::lexicographical_compare(_lhs.begin(), _lhs.end(),	_rhs.begin(), _rhs.end()); }

/// Based on operator==
template<typename _Tp, typename _Alloc>
inline bool
operator!=(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return !(_lhs == _rhs); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return _rhs < _lhs; }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator<=(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return !(_rhs < _lhs); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>=(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs)
{ return !(_lhs < _rhs); }

_END_FT_NAMESPACE
#endif
