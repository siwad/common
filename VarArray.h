#ifndef _DE_BSWALZ_VARARRAY_H
#define _DE_BSWALZ_VARARRAY_H

/**
 * Template class which implements a Java-like dynamic array
 *
 * @copyright	2005 Siegfried Walz
 * @license     https://www.gnu.org/licenses/lgpl-3.0.txt GNU Lesser General Public License
 * @author      Siegfried Walz
 * @link        https://software.bswalz.de/
 * @package     common
 */
/*
 * This file is part of common package
 *
 * common is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * common/sync is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <stdint.h>  // uint16_t
#include <stdexcept>
#include <vector>

namespace de { namespace bswalz {

/**
 * Template class var_array with dynamic size which is missing +n C++. <br>
 * The max. size is 65535 elements.<br>
 * The type T is either atomic data or is class data that has the following
 * member functions:<br>
 *   T::T ()
 *   T::T (const T&);
 *   T& T::operator= (const T&)
 *   T& T::operator= (std::initializer_list<T> il)
 */
template <class T>
class var_array {
public:
	/** Constructs an array with N elements. */
	var_array (uint16_t n = 0);
	/** Fill constructor. Constructs an array with n elements, initialized with val. */
	var_array (uint16_t n, const T & val);
	/** Fill constructor. Constructs an array with n elements.
	 *  Each element is a copied from the given array. */
	var_array (T* pArray, uint16_t n);
	/** Copy constructor */
	var_array (const var_array& r);
    /** Move constructor */
	var_array(var_array && r);
	/** Constructor with initializer list */
	var_array(std::initializer_list<T> il);
	/** Assignment operator */
	var_array&  operator= (const var_array& r);
	/** Assignment operator with initializer list */
	T& operator= (std::initializer_list<T> il);
	/** Move assignment operator */
	var_array&  operator= (var_array&& r);

    /** Destructor */
	~var_array ();

    /** @return the amount of elements of this array */
	uint16_t size () const { return m_Array.size(); }

    /** Sets new size of the array. Spare objects will be removed, missing objects will be filled with val */
    void     setSize(uint16_t, const T & val);

    /** @return true if the array is empty */
	bool     empty() const { return m_Array.empty(); }
    
    /** @return a pointer to the beginning of the array */
	const T* data ()	   { return m_Array.data(); }
    
    /** @return a pointer to the beginning of the array */
	const T* const data () const { return m_Array.data(); }

	/** Access operator. Index i must be in range.<br>
	 *  Possibly throws std::out_of_range(...) exception
	 */
    T&       operator[] (uint16_t i);

	/** Access operator. Index i must be in range.<br>
	 *  Possibly throws std::out_of_range(...) exception
	 */
	const T  operator[] (uint16_t i) const;

    /**
     * Appends new element. The array will dynamically grow if necessary<br>
     * The attempt to increase an array of 65535 elements will be ignored.<br>
	 * Possibly throws std::length_error(...) exception
     */
	var_array & push_back (const T& rtElement);
    
    /** Fill array with value */
	void     fill(const T & r);

    /**
	 * Removes the element at the specified index. The elements occurring
	 * after that one are shifted so that the array remains contiguous.<br>
     * Possibly throws std::length_error
     */
    void     remove (uint16_t i);

	/** Empties the array. The size ist 0 afterwards. */
    void     removeAll ();

    /**
	 * @return first occurance of given element. If not found, returns -1L<br>
     */
	long     indexOf(const T& element) const;
    
    /** Comparison of arrays */
	bool     operator== (const var_array& r) const;
    
    /** Comparison of arrays */
	bool     operator!= (const var_array& r) const;

private:
	std::vector<T> m_Array;
    
    void     init(const uint16_t);
	void     init(const uint16_t, const T&);
	void     init(const std::vector<T> &);
};


//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array (uint16_t n) : m_Array() {
	init(n, T());
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array (uint16_t n, const T & val)	: m_Array() {
	init(n, val);
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array (T* pArray, uint16_t quantity) : m_Array() {
	init(quantity);
	for (unsigned int i = 0; i < quantity; i++) m_Array[i] = *(pArray + i);
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array (const var_array& r) : m_Array() {
	const uint16_t size = r.size();
	init(r.m_Array);
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array (var_array&& r)	: m_Array(r.m_Array) {
	// Intentionally left blank
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::var_array(std::initializer_list<T> il) {
	init(0);
	m_Array.insert(m_Array.begin(), il.begin(), il.end());
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>& var_array<T>::operator= (const var_array& r) {
	init(r.m_Array);
	return *this;
}
//----------------------------------------------------------------------------
template <class T> inline
T& var_array<T>::operator= (std::initializer_list<T> il) {
	init(0);
	m_Array.insert(m_Array.begin(), il.begin(), il.end());
	return *this;
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>& var_array<T>::operator= (var_array&& r) {
	m_Array    = r.m_Array;
	return *this;
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>::~var_array () {
	// Intentionally left blank
}

//----------------------------------------------------------------------------
// Creates array and leaves it uninitialized
template <class T> inline
void var_array<T>::init(const uint16_t quantity) {
	m_Array = std::vector<T>(quantity);
}
//----------------------------------------------------------------------------
// Creates array and fills it
template <class T> inline
void var_array<T>::init(const uint16_t quantity, const T & value) {
	init(quantity);
	m_Array = std::vector<T>(quantity, value);
}
//----------------------------------------------------------------------------
// Creates array and fills it
template <class T> inline
void var_array<T>::init(const std::vector<T> & values) {
	m_Array = values;
}
//----------------------------------------------------------------------------
template <class T>
T& var_array<T>::operator[] (uint16_t i) {
	if (i >= m_Array.size())
		throw std::out_of_range("de::bswalz::var_array::operator[]");
	return m_Array[i];
}
//----------------------------------------------------------------------------
template <class T> inline
const T var_array<T>::operator[] (uint16_t i) const {
	if (i >= m_Array.size())
		throw std::out_of_range("de::bswalz::var_array::operator[] const");
	return m_Array[i];
}
//----------------------------------------------------------------------------
template <class T> inline
long var_array<T>::indexOf (const T& value) const {
	auto pos = std::find_if(m_Array.begin(), m_Array.end(), [value](const T& v) { return v == value; });
	return (pos != m_Array.end()) ? (pos - m_Array.begin()) : -1L;
}
//----------------------------------------------------------------------------
template <class T> inline
var_array<T>& var_array<T>::push_back (const T& value) {
	if (m_Array.size() < 0xFFFF) {
		m_Array.push_back(value);
		}
	else {
		throw std::length_error("de::bswalz::var_array::push_back");
		}

	return *this;
}
//----------------------------------------------------------------------------
template <class T> inline
void var_array<T>::setSize (uint16_t size, const T& value) {
	if (m_Array.size() == size) return;  // Does nothing
	else if (m_Array.size() > size) {    // Removes spare objects
		m_Array.resize(size);
		}
	else {                               // Increases size and initializes with val
		m_Array.resize(size, value);
		}
}
//----------------------------------------------------------------------------
template <class T> inline
void var_array<T>::fill (const T& value) {
	m_Array.assign(m_Array.size(), value);
}
//----------------------------------------------------------------------------
template <class T> inline
void var_array<T>::remove (uint16_t i) {
	if (i >= m_Array.size())
		throw std::length_error("de::bswalz::var_array::remove");

	m_Array.erase(i);
}
//----------------------------------------------------------------------------
template <class T> inline
void var_array<T>::removeAll () {
	m_Array.clear();
}
//----------------------------------------------------------------------------
template <class T> inline
bool var_array<T>::operator== (const var_array& r) const {
	return m_Array == r.m_Array;
}
//----------------------------------------------------------------------------
template <class T> inline
bool var_array<T>::operator!= (const var_array& r) const {
	return m_Array != r.m_Array;
}

}} // End namespaces

#endif /*_DE_BSWALZ_VARARRAY_H*/



