#ifndef _UTILS_HPP_
#define _UTILS_HPP_

namespace utils {
	template<bool B, class T = void>
	struct enable_if {  };
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<typename, typename>
	struct are_same {
		enum { _value = 0 };
	};
	template<typename Tp>
	struct are_same<Tp, Tp> {
		enum { _value = 1 };
	};

	struct _true_type { };
	struct _false_type { };

	template<bool>
	struct _truth_type
	{ typedef _false_type _type; };

	template<>
	struct _truth_type<true>
	{ typedef _true_type _type; };

	/* is_integral */
	template<typename _Tp>
	struct is_integral {
		enum { _value = 0 };
		typedef _false_type _type;
	};
	template<>
	struct is_integral<bool> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<char> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<signed char> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<unsigned char> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<short> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<unsigned short> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<int> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<unsigned int> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<long> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<unsigned long> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<long long> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	template<>
	struct is_integral<unsigned long long> {
		enum { _value = 1 };
		typedef _true_type _type;
	};
	/* end of is_integral */

	template<class InputIt1, class inputIt2>
	bool
	equal(InputIt1 _first1, InputIt1 _last1, inputIt2 _first2) {
		for (; _first1 != _last1; ++_first1, ++_first2)
		if (!(*_first1 == *_first2))	return false;
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool
	lexicographical_compare(InputIt1 _first1, InputIt1 _last1, InputIt2 _first2, InputIt2 _last2)
	{
		for ( ; (_first1 != _last1) && (_first2 != _last2); ++_first1, (void) ++_first2 ) {
			if (*_first1 < *_first2) return true;
			if (*_first2 < *_first1) return false;
		}
		return (_first1 == _last1) && (_first2 != _last2);
	}

	template<class _InputIterator, class _OutputIterator>
	_OutputIterator
	copy (_InputIterator _first, _InputIterator _last, _OutputIterator _result)
	{
		for ( ; _first != _last; ++_result, ++_first)
			*_result = *_first;
		return _result;
	}
} /* namespace utils */
#endif
