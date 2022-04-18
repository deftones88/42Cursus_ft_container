#ifndef	_RB_TREE_HPP_
#define	_RB_TREE_HPP_

#include "vector.hpp"
#include "pair.hpp"
#include "iterator.hpp"

#include <iostream>
#include <memory>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;

_START_FT_NAMESPACE

enum Rb_tree_color { _RED = false, _BLACK = true };

/* base node */
template <typename _Val>
struct Rb_tree_node {
	typedef Rb_tree_node<_Val>*						Rb_node_ptr;

	_Val*				_value;
	Rb_tree_color 		_color;
	Rb_node_ptr			_parent;
	Rb_node_ptr			_child[2];

	Rb_tree_node()
	: _value(0), _color(_RED), _parent(0)
	{
		this->_child[0] = NULL;
		this->_child[1] = NULL;
	}
	~Rb_tree_node() {}
};

#define LEFT 			0
#define RIGHT	 		1
#define _leftChild		_child[LEFT]
#define _rightChild		_child[RIGHT]

/* iterators */
/** normal_iterator **/
template<typename _Tp>
struct Rb_tree_iterator {
public:
	typedef _Tp  										value_type;
	typedef _Tp& 										reference;
	typedef _Tp* 										pointer;

	typedef bidirectional_iterator_tag 					iterator_category;
	typedef ptrdiff_t                  					difference_type;

	typedef Rb_tree_iterator<_Tp>        				iterator;
	typedef typename Rb_tree_node<_Tp>::Rb_node_ptr		Rb_node_ptr;
	typedef Rb_tree_node<_Tp>*           				Link_type;

private:
	Rb_node_ptr	_node;
	Rb_node_ptr _nil;
	Rb_node_ptr _root;

public:
	Rb_tree_iterator()
	: _node(0), _nil(0), _root(0) { }
	explicit
	Rb_tree_iterator(const Link_type _node, const Link_type _nil, const Link_type _root)
	: _node(_node), _nil(_nil), _root(_root) { }

	Rb_tree_iterator(const iterator& _x)
	: _node(_x._node), _nil(_x._nil), _root(_x._root) { }

	~Rb_tree_iterator() { }

	Rb_node_ptr			node() 	const { return this->_node;}
	Rb_node_ptr			nil()  	const { return this->_nil;}
	Rb_node_ptr			root() 	const { return this->_root;}

	Rb_node_ptr
	Rb_tree_increment(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _min = this->_root;
			while (_min->_leftChild != _nil) _min = _min->_leftChild;
			return _min;
		}
		if (_current->_rightChild != this->_nil) {
			_current = _current->_rightChild;
			while (_current->_leftChild != this->_nil)	_current = _current->_leftChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_rightChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	Rb_node_ptr
	Rb_tree_decrement(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _max = this->_root;
			while (_max->_rightChild != _nil) _max = _max->_rightChild;
			return _max;
		}
		if (_current->_leftChild != _nil) {
			_current = _current->_leftChild;
			while (_current->_rightChild != _nil)	_current = _current->_rightChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_leftChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	reference
	operator*() const
	{ return *static_cast<Link_type>(this->_node)->_value; }

	pointer
	operator->() const
	{ return static_cast<Link_type>(this->_node)->_value; }

	iterator&
	operator++()	{
		this->_node = Rb_tree_increment(this->_node);
		return *this;
	}
	iterator
	operator++(int)	{
		iterator _tmp = *this;
		this->_node = Rb_tree_increment(this->_node);
		return _tmp;
	}

	iterator&
	operator--()	{
		this->_node = Rb_tree_decrement(this->_node);
		return *this;
	}
	iterator
	operator--(int)	{
		iterator _tmp = *this;
		this->_node = Rb_tree_decrement(this->_node);
		return _tmp;
	}

	bool
	operator==(const iterator& _x) const
	{ return this->_node == _x._node; }

	bool
	operator!=(const iterator& _x) const
	{ return this->_node != _x._node; }
};

/** const_iterator **/
template<typename _Tp>
struct Rb_tree_const_iterator {
public:
	typedef _Tp  																			value_type;
	typedef const _Tp& 									reference;
	typedef const _Tp* 									pointer;

	typedef bidirectional_iterator_tag 					iterator_category;
	typedef ptrdiff_t                  					difference_type;

	typedef Rb_tree_iterator<_Tp>        				iterator;
	typedef Rb_tree_const_iterator<_Tp>        			const_iterator;
	typedef typename Rb_tree_node<_Tp>::Rb_node_ptr		Rb_node_ptr;
	typedef Rb_tree_node<_Tp>*           				Link_type;

private:
	Rb_node_ptr	_node;
	Rb_node_ptr _nil;
	Rb_node_ptr _root;

public:
	Rb_tree_const_iterator()
	: _node(0), _nil(0), _root(0) { }
	explicit
	Rb_tree_const_iterator(const Link_type _node, const Link_type _nil, const Link_type _root)
	: _node(_node), _nil(_nil), _root(_root) { }

	Rb_tree_const_iterator(const const_iterator& _x)
	: _node(_x._node), _nil(_x._nil), _root(_x._root) { }
	Rb_tree_const_iterator(const iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root()) { }

	~Rb_tree_const_iterator() { }

	Rb_node_ptr			node() 	const { return this->_node;}
	Rb_node_ptr			nil()  	const { return this->_nil;}
	Rb_node_ptr			root() 	const { return this->_root;}

	Rb_node_ptr
	Rb_tree_increment(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _min = this->_root;
			while (_min->_leftChild != _nil) _min = _min->_leftChild;
			return _min;
		}
		if (_current->_rightChild != this->_nil) {
			_current = _current->_rightChild;
			while (_current->_leftChild != this->_nil)	_current = _current->_leftChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_rightChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	Rb_node_ptr
	Rb_tree_decrement(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _max = this->_root;
			while (_max->_rightChild != _nil) _max = _max->_rightChild;
			return _max;
		}
		if (_current->_leftChild != _nil) {
			_current = _current->_leftChild;
			while (_current->_rightChild != _nil)	_current = _current->_rightChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_leftChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	reference
	operator*() const
	{ return *static_cast<Link_type>(this->_node)->_value; }

	pointer
	operator->() const
	{ return static_cast<Link_type>(this->_node)->_value; }

	const_iterator&
	operator++()	{
		this->_node = Rb_tree_increment(this->_node);
		return *this;
	}
	const_iterator
	operator++(int)	{
		const_iterator _tmp = *this;
		this->_node = Rb_tree_increment(this->_node);
		return _tmp;
	}

	const_iterator&
	operator--()	{
		this->_node = Rb_tree_decrement(this->_node);
		return *this;
	}
	const_iterator
	operator--(int)	{
		const_iterator _tmp = *this;
		this->_node = Rb_tree_decrement(this->_node);
		return _tmp;
	}

	bool
	operator==(const const_iterator& _x) const
	{ return this->_node == _x._node; }

	bool
	operator!=(const const_iterator& _x) const
	{ return this->_node != _x._node; }
};

/** reverse_iterator **/
template<typename _Tp>
struct Rb_tree_reverse_iterator {
public:
	typedef typename _Tp::value_type				value_type;
	typedef typename _Tp::reference					reference;
	typedef typename _Tp::pointer 					pointer;

	typedef bidirectional_iterator_tag 				iterator_category;
	typedef ptrdiff_t                  				difference_type;

	typedef typename _Tp::iterator					iterator;
	typedef Rb_tree_reverse_iterator<_Tp>    		reverse_iterator;
	typedef Rb_tree_const_iterator<_Tp>    			const_iterator;
	typedef typename _Tp::Rb_node_ptr				Rb_node_ptr;
	typedef typename _Tp::Link_type		    		Link_type;

private:
	Rb_node_ptr	_node;
	Rb_node_ptr _nil;
	Rb_node_ptr _root;

public:
	Rb_tree_reverse_iterator()
	: _node(0), _nil(0), _root(0)
	{ }
	Rb_tree_reverse_iterator(const Link_type _node, const Link_type _nil, const Link_type _root)
	: _node(_node), _nil(_nil), _root(_root)
	{ }
	Rb_tree_reverse_iterator(const reverse_iterator& _x)
	: _node(_x._node), _nil(_x._nil), _root(_x._root)
	{ }

	Rb_tree_reverse_iterator(const iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root())
	{ _node = Rb_tree_decrement(_node); }
	Rb_tree_reverse_iterator(const const_iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root())
	{ _node = Rb_tree_decrement(_node); }

	~Rb_tree_reverse_iterator() { }

	Rb_node_ptr		node() 	const { return this->_node;}
	Rb_node_ptr		nil()  	const { return this->_nil;}
	Rb_node_ptr		root() 	const { return this->_root;}

	iterator
	base() const
	{ return iterator(Rb_tree_increment(_node), _nil, _root);	}

	Rb_node_ptr
	Rb_tree_increment(Rb_node_ptr _current) const {
		if (_current == this->_nil) {
			Rb_node_ptr _min = this->_root;
			while (_min->_leftChild != _nil) _min = _min->_leftChild;
			return _min;
		}
		if (_current->_rightChild != this->_nil) {
			_current = _current->_rightChild;
			while (_current->_leftChild != this->_nil)	_current = _current->_leftChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_rightChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	Rb_node_ptr
	Rb_tree_decrement(Rb_node_ptr _current) const {
		if (_current == this->_nil) {
			Rb_node_ptr _max = this->_root;
			while (_max->_rightChild != _nil) _max = _max->_rightChild;
			return _max;
		}
		if (_current->_leftChild != _nil) {
			_current = _current->_leftChild;
			while (_current->_rightChild != _nil)	_current = _current->_rightChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_leftChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	reference
	operator*() const
	{ return *static_cast<Link_type>(this->_node)->_value; }

	pointer
	operator->() const
	{ return static_cast<Link_type>(this->_node)->_value; }

	reverse_iterator&
	operator++()	{
		this->_node = Rb_tree_decrement(this->_node);
		return *this;
	}
	reverse_iterator
	operator++(int)	{
		reverse_iterator _tmp = *this;
		this->_node = Rb_tree_decrement(this->_node);
		return _tmp;
	}

	reverse_iterator&
	operator--()	{
		this->_node = Rb_tree_increment(this->_node);
		return *this;
	}
	reverse_iterator
	operator--(int)	{
		reverse_iterator _tmp = *this;
		this->_node = Rb_tree_increment(this->_node);
		return _tmp;
	}

	bool
	operator==(const reverse_iterator& _x) const
	{ return this->_node == _x._node; }

	bool
	operator!=(const reverse_iterator& _x) const
	{ return this->_node != _x._node; }
};

/** const_reverse_iterator **/
template<typename _Tp> //_tp = const_iterator
struct Rb_tree_const_reverse_iterator {
public:
	typedef typename _Tp::value_type				value_type;
	typedef typename _Tp::reference					reference;
	typedef typename _Tp::pointer 					pointer;

	typedef bidirectional_iterator_tag 				iterator_category;
	typedef ptrdiff_t                  				difference_type;

	typedef typename _Tp::iterator					iterator;
	typedef typename _Tp::const_iterator    		const_iterator;
	typedef Rb_tree_reverse_iterator<iterator> 		reverse_iterator;
	typedef Rb_tree_const_reverse_iterator<_Tp>		const_reverse_iterator;
	typedef typename _Tp::Rb_node_ptr				Rb_node_ptr;
	typedef typename _Tp::Link_type		    		Link_type;

private:
	Rb_node_ptr	_node;
	Rb_node_ptr _nil;
	Rb_node_ptr _root;

public:
	Rb_tree_const_reverse_iterator()
	: _node(0), _nil(0), _root(0)
	{ }
	Rb_tree_const_reverse_iterator(const Link_type _node, const Link_type _nil, const Link_type _root)
	: _node(_node), _nil(_nil), _root(_root)
	{ }
	Rb_tree_const_reverse_iterator(const const_reverse_iterator& _x)
	: _node(_x._node), _nil(_x._nil), _root(_x._root)
	{ }

	Rb_tree_const_reverse_iterator(const reverse_iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root())
	{  }
	Rb_tree_const_reverse_iterator(const iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root())
	{ _node = Rb_tree_decrement(_node); }
	Rb_tree_const_reverse_iterator(const const_iterator& _x)
	: _node(_x.node()), _nil(_x.nil()), _root(_x.root())
	{  _node = Rb_tree_decrement(_node); }

	~Rb_tree_const_reverse_iterator() { }

	const_reverse_iterator
	base() const
	{ return const_reverse_iterator(_node, _nil, _root); }

	Rb_node_ptr
	Rb_tree_increment(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _min = this->_root;
			while (_min->_leftChild != _nil) _min = _min->_leftChild;
			return _min;
		}
		if (_current->_rightChild != this->_nil) {
			_current = _current->_rightChild;
			while (_current->_leftChild != this->_nil)	_current = _current->_leftChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_rightChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	Rb_node_ptr
	Rb_tree_decrement(Rb_node_ptr _current) {
		if (_current == this->_nil) {
			Rb_node_ptr _max = this->_root;
			while (_max->_rightChild != _nil) _max = _max->_rightChild;
			return _max;
		}
		if (_current->_leftChild != _nil) {
			_current = _current->_leftChild;
			while (_current->_rightChild != _nil)	_current = _current->_rightChild;
		} else {
			Rb_node_ptr _parent = _current->_parent;
			while (_current == _parent->_leftChild) {
				_current = _parent;
				_parent = _parent->_parent;
			}
			_current = _parent;
		}
		return _current;
	}

	reference
	operator*() const
	{ return *static_cast<Link_type>(this->_node)->_value; }

	pointer
	operator->() const
	{ return static_cast<Link_type>(this->_node)->_value; }

	const_reverse_iterator&
	operator++()	{
		this->_node = Rb_tree_decrement(this->_node);
		return *this;
	}
	const_reverse_iterator
	operator++(int)	{
		const_reverse_iterator _tmp = *this;
		this->_node = Rb_tree_decrement(this->_node);
		return _tmp;
	}

	const_reverse_iterator&
	operator--()	{
		this->_node = Rb_tree_increment(this->_node);
		return *this;
	}
	const_reverse_iterator
	operator--(int)	{
		const_reverse_iterator _tmp = *this;
		this->_node = Rb_tree_increment(this->_node);
		return _tmp;
	}

	bool
	operator==(const const_reverse_iterator& _x) const
	{ return this->_node == _x._node; }

	bool
	operator!=(const const_reverse_iterator& _x) const
	{ return this->_node != _x._node; }
};

/* rb tree */
template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<_Val> >
class Rb_tree {
	typedef typename _Alloc::template rebind<Rb_tree_node<_Val> >::other	_node_allocator;

public:
	typedef _Key 										key_type;
	typedef _Val 										value_type;
	typedef value_type*									pointer;
	typedef const value_type*							const_pointer;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef size_t 										size_type;
	typedef ptrdiff_t 									difference_type;
	typedef _Alloc 										allocator_type;
	typedef struct Rb_tree_node<value_type>				Rb_tree_node;
	typedef Rb_tree_node*								Rb_node_ptr;
	typedef const Rb_tree_node*							const_Rb_node_ptr;

	typedef Rb_tree_iterator<value_type>      			iterator;
	typedef Rb_tree_const_iterator<value_type> 			const_iterator;

	typedef Rb_tree_const_reverse_iterator<const_iterator> 	const_reverse_iterator;
	typedef Rb_tree_reverse_iterator<iterator>       	reverse_iterator;

private:
	Rb_node_ptr							_root;
	Rb_node_ptr							_nil;
	_Compare							_comp;
	allocator_type						_alloc;
	size_type							_size;
	_node_allocator						_node_alloc;

public:
	// constructor/copy/destruct
	Rb_tree(const _Compare& _comp = _Compare(), const allocator_type& _alloc = allocator_type())
	: _comp(_comp), _alloc(_alloc), _size(0) {
		_node_alloc = _node_allocator();
		_nil = new_node(value_type());
		_nil->_parent = _nil->_leftChild = _nil->_rightChild = _nil;
		_nil->_color = _BLACK;
		_root = _nil;
	}
	Rb_tree(const Rb_tree& _x)
	: _root(_x._root), _comp(_x._comp), _alloc(_x._alloc), _size(0) {
		_node_alloc = _node_allocator();
		_nil = new_node(value_type());
		_nil->_parent = _nil->_leftChild = _nil->_rightChild = _nil;
		_nil->_color = _BLACK;
		_root = _nil;
		for (const_iterator cit = _x.begin(); cit != _x.end(); ++cit)
			insert(*cit);
	}
	~Rb_tree() {
		clear();
		_alloc.destroy(_nil->_value);
		_alloc.deallocate(_nil->_value, 1);
		_node_alloc.destroy(_nil);
		_node_alloc.deallocate(_nil, 1);
	}

	Rb_tree&
	operator=(const Rb_tree& _x) {
		if (this != &_x) {
			clear();
			this->_comp = _x._comp;
			if (_x._root != _x._nil) {
				for (const_iterator cit = _x.begin(); cit != _x.end(); ++cit)
					insert(*cit);
				this->_size = _x._size;
				// this->_alloc = _x._alloc;
				// this->_node_alloc = _x._node_alloc;
			}
		}
		return *this;
	}

	allocator_type
	get_allocator() const
	{ return static_cast<allocator_type>(_alloc); }

	/* traverse */
	Rb_node_ptr
	minimum(Rb_node_ptr _current) {
		while (_current->_leftChild != _nil) _current = _current->_leftChild;
		return _current;
	}
	Rb_node_ptr
	maximum(Rb_node_ptr _current) {
		while (_current->_rightChild != _nil) _current = _current->_rightChild;
		return _current;
	}

	iterator
	begin() {
		Rb_node_ptr _min = minimum(_root);
		return iterator(_min, _nil, _root);
	}
	const_iterator
	begin() const {
		Rb_node_ptr _min = _root;
		while (_min->_leftChild != _nil) _min = _min->_leftChild;
		return const_iterator(_min, _nil, _root);
	}
	iterator 		end() 		{ return iterator(_nil, _nil, _root);  }
	const_iterator	end() const { return const_iterator(_nil, _nil, _root);  }

	reverse_iterator
	rbegin() {
		Rb_node_ptr _max = maximum(_root);
		return reverse_iterator(_max, this->_nil, this->_root);
	}
	const_reverse_iterator
	rbegin() const	{
		Rb_node_ptr _max = _root;
		while (_max->_rightChild != _nil) _max = _max->_rightChild;
		return const_reverse_iterator(_max, _nil, _root);
	}

	reverse_iterator
	rend()
	{ return reverse_iterator(_nil, _nil, _root); }
	const_reverse_iterator
	rend() const
	{ return const_reverse_iterator(_nil, _nil, _root); }


	iterator
	find( const key_type& _key) {
		Rb_node_ptr _current = this->_root;
		while (_current != _nil) {
			if (_key == _KeyOfValue()(*_current->_value)) break ;
			if (_comp(_key, _KeyOfValue()(*_current->_value)))
				_current = _current->_leftChild;
			else	_current = _current->_rightChild;
		}
		return iterator(_current, _nil, _root);
	}
	const_iterator
	find( const key_type& _key) const {
		Rb_node_ptr _current = this->_root;
		while (_current != _nil) {
			if (_key == _KeyOfValue()(*_current->_value)) break ;
			if (_comp(_key, _KeyOfValue()(*_current->_value)))
				_current = _current->_leftChild;
			else	_current = _current->_rightChild;
		}
		return const_iterator(_current, _nil, _root);
	}

	bool		empty() const		{ return this->_size == 0; }

	size_type	size() const		{ return this->_size; }

	size_type	max_size() const	{ return _node_alloc.max_size(); }

	/* insert */

	Rb_node_ptr
	new_node(const value_type& _value) {
		Rb_node_ptr _child = _node_alloc.allocate(1);
		_node_alloc.construct(_child, Rb_tree_node());
		_child->_value = _alloc.allocate(1);
		_alloc.construct(_child->_value, _value);
		_child->_leftChild = _child->_rightChild = _child->_parent = _nil;
		return _child;
	}
	void
	delete_node(Rb_node_ptr _node) {
		if (_node->_value) {
			_alloc.destroy(_node->_value);
			_alloc.deallocate(_node->_value, 1);
		}
		_node_alloc.destroy(_node);
		_node_alloc.deallocate(_node, 1);
	}
	bool
	is_left(Rb_node_ptr _current) {
		return _current->_parent->_leftChild == _current;
	}
	Rb_node_ptr&
	get_sibling(Rb_node_ptr _current) {
		if (is_left(_current))	return _current->_parent->_rightChild;
		else 					return _current->_parent->_leftChild;
	}

	Rb_node_ptr
	rebuild_after_insert(Rb_node_ptr _child) {
		Rb_node_ptr _ret = _child;
		Rb_node_ptr _parent = _child->_parent;
		do {
			if (_parent->_color == _RED && _child->_color == _RED) {
				Rb_node_ptr _sibling = get_sibling(_parent);
				if (_sibling == _nil || _sibling->_color == _BLACK) {
					/* rotation */
					int dir = !(is_left(_child));
					if (dir == !(is_left(_parent))) {
						value_type* _tmp = _parent->_parent->_value;
						_parent->_parent->_value = _parent->_value;
						_parent->_value = _child->_value;
						if (_ret == _child) _ret = _parent;
						_child->_value = _tmp;
						_parent->_child[dir] = _child->_child[dir];
						_child->_child[dir] = _parent->_child[1-dir];
						_parent->_child[1-dir] = _child->_child[1-dir];
						_child->_child[1-dir] = _parent->_parent->_child[1-dir];
						_parent->_parent->_child[1-dir] = _child;
						_child->_parent = _parent->_parent;
						_child->_child[dir]->_parent = _child->_child[1-dir]->_parent = _child;
						_parent->_child[dir]->_parent = _parent->_child[1-dir]->_parent = _parent;
					} else {
						value_type* _tmp = _parent->_parent->_value;
						_parent->_parent->_value = _child->_value;
						if (_ret == _child) _ret = _parent->_parent;
						_child->_value = _tmp;
						_parent->_child[dir] = _child->_child[1-dir];
						_child->_child[1-dir] = _child->_child[dir];
						_child->_child[dir] = _parent->_parent->_child[dir];
						_parent->_parent->_child[dir] = _child;
						_child->_parent = _parent->_parent;
						_child->_child[dir]->_parent = _child->_child[1-dir]->_parent = _child;
						_parent->_child[dir]->_parent = _parent->_child[1-dir]->_parent = _parent;
					}
				} else if (_sibling->_color == _RED) {
					_parent->_color = _BLACK;
					_sibling->_color = _BLACK;
					_child->_color = _RED;
					if (_parent->_parent != _root && _parent->_parent->_color == _BLACK)
					_parent->_parent->_color = _RED;
				}
			}
			_child = _parent;
		} while ((_parent = _child->_parent) != _nil);
		this->_size++;
		return _ret;
	}
	Rb_node_ptr
	_BST_insert(Rb_node_ptr _current, Rb_node_ptr _child) {
		if (_KeyOfValue()(*_child->_value) == _KeyOfValue()(*_current->_value))
			return _current;
		if (_comp(_KeyOfValue()(*_child->_value), _KeyOfValue()(*_current->_value))) {
			// std::cout<<"insert left"<<std::endl;
			if (_current->_leftChild == _nil) {
				_child->_parent = _current;
				_current->_leftChild = _child;
				return _child;
			}
			else	return _BST_insert(_current->_leftChild, _child);
		} else {
			// std::cout<<"insert right"<<std::endl;
			if (_current->_rightChild == _nil) {
				_child->_parent = _current;
				_current->_rightChild = _child;
				return _child;
			}
			else 	return _BST_insert(_current->_rightChild, _child);
		}
	}
	ft::pair<iterator, bool>
	BST_insert(Rb_node_ptr* _root, Rb_node_ptr _child) {
		Rb_node_ptr _ret = _child;
		bool b = true;
		if (*_root == _nil) {
			*_root = _child;
			(*_root)->_color = _BLACK;
			_size++;
		} else {
			_ret = _BST_insert(*_root, _child);
			if (_ret != _child) {
				b = false;
				delete_node(_child);
			} else
			_ret = rebuild_after_insert(_ret);
		}
		return ft::pair<iterator, bool>(iterator(_ret, _nil, *_root), b);
	}

	ft::pair<iterator, bool>
	insert(const value_type& _value) {
		Rb_node_ptr _child = new_node(_value);
		ft::pair<iterator, bool> _ret = BST_insert(&_root, _child);
		return _ret;
	}
	iterator
	insert(iterator _it, const value_type& _value) {
		Rb_node_ptr _child = new_node(_value);
		Rb_node_ptr _ret = _child;
		if (_it == end()) {
			if (size() > 0 && _comp(_KeyOfValue()(*(--_it)), _KeyOfValue()(_value))) {
				_ret = _BST_insert(_it.node(), _child);
			} else {
				delete_node(_child);
				return insert(_value).first;
			}
		} else if (_comp(_KeyOfValue()(*_it), _KeyOfValue()(_value))) {
			iterator _before = _it;
			if (_it == begin()) {
				_ret = _BST_insert(_root, _child);
			} else if (_comp(_KeyOfValue()(*(--_before)), _KeyOfValue()(_value))) {
				_ret = _BST_insert(_before.node(), _child);
			} else
				return insert(_value).first;
		} else if (_comp(_KeyOfValue()(_value), _KeyOfValue()(*_it))) {
			iterator _after = _it;
			iterator _end = end();
			if (_it == --_end) {
				_ret = _BST_insert(_end.node(), _child);
			} else if (_comp(_KeyOfValue()(*(++_after)), _KeyOfValue()(_value))) {
				_ret = _BST_insert(_after.node(), _child);
			} else {
				delete_node(_child);
				return insert(_value).first;
			}
		} else {
			delete_node(_child);
			return _it;
		}
		_ret = rebuild_after_insert(_child);
		return iterator(_ret, _nil, _root);
	}
	template<class _InputIterator>
	void
	insert(_InputIterator _first, _InputIterator _last) {
		for (; _first != _last; ++_first)
			insert(*_first);
	}

	void
	rotate(Rb_node_ptr _current, int dir) {
		if (_current == _nil) return ;
		Rb_node_ptr _tmp = _current->_child[1-dir];
		_current->_child[1-dir] = _tmp->_child[dir];
		if (_tmp->_child[dir] != _nil) _tmp->_child[dir]->_parent = _current;
		_tmp->_parent = _current->_parent;
		if (_current->_parent == _nil)	_root = _tmp;
		else if (_current == _current->_parent->_child[dir])
			_current->_parent->_child[dir] = _tmp;
		else	_current->_parent->_child[1-dir] = _tmp;
		_tmp->_child[dir] = _current;
		_current->_parent = _tmp;
	}

	/* delete */
	void
	replace(Rb_node_ptr _selected, Rb_node_ptr _child) {
		if (_selected->_parent == _nil)	_root = _child;
		else if (is_left(_selected))	_selected->_parent->_leftChild = _child;
		else							_selected->_parent->_rightChild = _child;
		_child->_parent = _selected->_parent;
	}
	void
	rebuild_after_erase(Rb_node_ptr _current) {
		while (_current != _root && _current->_color == _BLACK) {
			int dir = !is_left(_current);
			Rb_node_ptr _sibling = get_sibling(_current);
			// 1. sib red
			if (_sibling->_color == _RED) {
				_sibling->_color = _BLACK;
				_current->_parent->_color = _RED;
				rotate(_current->_parent, dir);
				_sibling = get_sibling(_current);
			}
			// 2. sib black & children black
			if (_sibling->_child[dir]->_color == _BLACK
				&& _sibling->_child[1-dir]->_color == _BLACK) {
				_sibling->_color = _RED;
				_current = _current->_parent;
			} else {
			// 3. sib black & one child red
				if (_sibling->_child[1-dir]->_color == _BLACK) {
					_sibling->_child[dir]->_color = _BLACK;
					_sibling->_color = _RED;
					rotate(_sibling, !dir);
					_sibling = get_sibling(_current);
				}
				_sibling->_color = _current->_parent->_color;
				_current->_parent->_color = _BLACK;
				_sibling->_child[1-dir]->_color = _BLACK;
				rotate(_current->_parent, dir);
				_current = _root;
			}
		}
		_current->_color = _BLACK;
	}
	void
	_erase(Rb_node_ptr _selected) {
		if (_selected == _nil)			return ;
		Rb_node_ptr _tmp = _selected, _tmpChild;
		Rb_tree_color _orig_color = _tmp->_color;
		int dir = _selected->_child[LEFT] == _nil ? RIGHT
				: _selected->_child[RIGHT] == _nil ? LEFT
				: -1;
		if (dir > -1) { // when a child branch is empty
			_tmpChild = _selected->_child[dir];
			replace(_selected, _selected->_child[dir]);
		} else {
			_tmp = minimum(_selected->_rightChild);
			_orig_color = _tmp->_color;
			_tmpChild = _tmp->_rightChild;
			if (_tmp->_parent == _selected)		_tmpChild->_parent = _tmp;
			else {
				replace(_tmp, _tmp->_rightChild);
				_tmp->_rightChild = _selected->_rightChild;
				_tmp->_rightChild->_parent = _tmp;
			}
			replace(_selected, _tmp);
			_tmp->_leftChild = _selected->_leftChild;
			_tmp->_leftChild->_parent = _tmp;
			_tmp->_color = _selected->_color;
		}
		if (_selected->_value) {
			_alloc.destroy(_selected->_value);
			_alloc.deallocate(_selected->_value, 1);
		}
		_node_alloc.destroy(_selected);
		_node_alloc.deallocate(_selected, 1);
		--_size;
		if (_orig_color == _BLACK)			rebuild_after_erase(_tmpChild);
		_nil->_leftChild = _nil->_rightChild = _nil->_parent = _nil;
		_nil->_color = _BLACK;
	}
	void
	erase(iterator _position) {
		Rb_node_ptr _selected = _position.node();
		return _erase(_selected);
	}
	size_type
	erase(const key_type& _key) {
		Rb_node_ptr _selected = (find(_key)).node();
		_erase(_selected);
		return _selected != _nil;
	}
	void
	erase(iterator _first, iterator _last)	{
		if (_first == begin() && _last == end()) clear();
		else {
			ft::vector<Rb_node_ptr> _tmp;
			typename ft::vector<Rb_node_ptr>::iterator _it;
			for (; _first != _last; ++_first)	_tmp.push_back(_first.node());
			for (_it = _tmp.begin(); _it != _tmp.end(); ++_it) 	_erase(*_it);
		}
	}

	// observers
	_Compare		key_comp() const					{ return _Compare(); }

	iterator
	lower_bound(const key_type& _k)	{
		Rb_node_ptr _current = _root;
		Rb_node_ptr _tmp = end().node();

		while (_current != _nil) {
			if (!(_comp(_KeyOfValue()(*_current->_value), _k))) {
				_tmp = _current;
				_current = _current->_leftChild;
			}
			else			_current = _current->_rightChild;
		}
		return iterator(_tmp, _nil, _root);
	}
	const_iterator
	lower_bound(const key_type& _k) const {
		Rb_node_ptr _current = _root;
		Rb_node_ptr _tmp = end().node();

		while (_current != _nil) {
			if (!(_comp(_KeyOfValue()(*_current->_value), _k))) {
				_tmp = _current;
				_current = _current->_leftChild;
			}
			else			_current = _current->_rightChild;
		}
		return const_iterator(_tmp, _nil, _root);
	}

	iterator
	upper_bound(const key_type& _k)	{
		Rb_node_ptr _current = _root;
		Rb_node_ptr _tmp = end().node();

		while (_current != _nil) {
			if (_comp(_k, _KeyOfValue()(*_current->_value))) {
				_tmp = _current;
				_current = _current->_leftChild;
			}
			else			_current = _current->_rightChild;
		}
		return iterator(_tmp, _nil, _root);
	}
	const_iterator
	upper_bound(const key_type& _k) const {
		Rb_node_ptr _current = _root;
		Rb_node_ptr _tmp = end().node();

		while (_current != _nil) {
			if (_comp(_k, _KeyOfValue()(*_current->_value))) {
				_tmp = _current;
				_current = _current->_leftChild;
			}
			else			_current = _current->_rightChild;
		}
		return const_iterator(_tmp, _nil, _root);
	}

	ft::pair<iterator, iterator>
	equal_range(const key_type& _x)
	{ return ft::pair<iterator, iterator>(lower_bound(_x), upper_bound(_x)); }
	ft::pair<const_iterator, const_iterator>
	equal_range(const key_type& _x) const
	{ return ft::pair<const_iterator, const_iterator>(lower_bound(_x), upper_bound(_x)); }

	void
	swap(Rb_tree& _x)	{
		std::swap(_root, _x._root);
		std::swap(_comp, _x._comp);
		std::swap(_nil, _x._nil);
		std::swap(_size, _x._size);
		std::swap(_alloc, _x._alloc);
		std::swap(_node_alloc, _x._node_alloc);
	}

	void
	_clear(Rb_node_ptr _current) {
		if (_current == _nil)	return ;
		_clear(_current->_leftChild);
		_clear(_current->_rightChild);
		if (_current->_value) {
			_alloc.destroy(_current->_value);
			_alloc.deallocate(_current->_value, 1);
		}
		_node_alloc.destroy(_current);
		_node_alloc.deallocate(_current, 1);
	}
	void
	clear() {
		_clear(this->_root);
		_size = 0;
		_root = _nil;
	}

	/* print */
	void	printTree() { LevelOrder(this->_root); }
	typedef struct	s_node	{
		Rb_tree_node 	*tree_node;
		int				level;
		struct	s_node	*prev;
		struct	s_node	*next;
	}						t_node;
	typedef struct	s_list	{
		t_node	*head;
		t_node	*tail;
		int		total;
	}						t_list;
	t_list
	*initList( ) {
		t_list	*tmp = new t_list;
		if (!tmp)		return (NULL);
		tmp->total = 0;
		return (tmp);
	}
	t_node
	*newNode(Rb_tree_node* tree_node, int level) {
		t_node	*_new = new t_node;
		if (!_new)		return (NULL);
		_new->tree_node = tree_node;
		_new->level = level;
		return (_new);
	}
	void
	insertRear(t_list *list, t_node *_new) {
		if (!list->total)	{
			list->head = _new;
			list->tail = _new;
		}
		_new->prev = list->tail;
		list->tail->next = _new;
		_new->next = list->head;
		list->tail = _new;
		list->total++;
	}
	Rb_tree_node
	*deleteFront(t_list *list) {
		if (!list->total)	return (NULL);
		t_node	*del = list->head;
		Rb_tree_node *ret = del->tree_node;
		if (list->head->next)	  {
			list->head = list->head->next;
			list->head->prev = list->tail;
			list->tail->next = list->head;
		} else {
			list->head = 0;
			list->tail = 0;
		}
		delete del;
		(list->total)--;
		return (ret);
	}
	size_t	getLevel(t_list *list) { return list->head->level; }
	void
	deleteAll(t_list *list) {
		t_node	*tmp = list->head;
		for (int i = 0; i < list->total; i++) {
			t_node	*del;
			del = tmp;
			tmp = tmp->next;
			delete del;
		}
		list->head = 0;
		list->tail = 0;
		list->total = 0;
		delete list;
	}
	size_t
	findHeight(Rb_tree_node *_root) {
		if (_root == _nil) return 0;
		return 1 + std::max(findHeight(_root->_leftChild), findHeight(_root->_rightChild));
	}
	void
	LevelOrder(Rb_node_ptr _root) {
		t_list *list = initList();
		Rb_node_ptr tmp = _root;
		size_t level = 1;
		insertRear(list, newNode(tmp, level));
		size_t total = this->_size;
		size_t height = findHeight(_root);
		size_t space = 1 << (height);
		size_t count = 0;

		std::cout<<"\n\e[42;44m TREE ("<<total<<") \e[0m"<<std::endl;
		while (total > 0) {
			if (height/ 2 > level)
				for (size_t i = 0; i < space - std::log2(space); i++)
					std::cout<<"  ";
			else
				for (size_t i = 0; i < space; i++)			std::cout<<"  ";
			tmp = deleteFront(list);
			if (tmp != NULL) {
				if (_KeyOfValue()(*tmp->_value)) 	{
					if (tmp->_color == _RED) std::cout << "\e[1;31m";
					std::cout << _KeyOfValue()(*tmp->_value) <<"\e[0m";
					--total;
				}
				else 					std::cout << "*";
				++count;
				size_t half = 1 << (level - 1);
				if (level != height && count == half/2)
					for (size_t i = 0; i < std::log2(level); i++)
						std::cout << " ";
				insertRear(list, newNode(tmp->_leftChild, level + 1));
				insertRear(list, newNode(tmp->_rightChild, level + 1));
			}
			else 					break ;
			if (total && getLevel(list) != level) {
				level = getLevel(list);
				space = space/2 + space%2;
				count = 0;
				std::cout<<std::endl;
			}
		}
		deleteAll(list);
		std::cout<<std::endl<<std::endl;
	}

};

template<typename _Key, typename _Val, typename _KeyOfValue,
typename _Compare, typename _Alloc>
inline bool
operator==(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return _x.size() == _y.size() && utils::equal(_x.begin(), _x.end(), _y.begin());	}

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
inline bool
operator<(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return utils::lexicographical_compare(_x.begin(), _x.end(), _y.begin(), _y.end()); }

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
inline bool
operator!=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return !(_x == _y); }

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
inline bool
operator>(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return _y < _x; }

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
inline bool
operator<=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return !(_y < _x); }

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
inline bool
operator>=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
{ return !(_x < _y); }

// template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
// inline void
// swap(Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _x, Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& _y)
// { _x.swap(_y); }

_END_FT_NAMESPACE

#endif
