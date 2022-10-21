
/**
 * Template class which implements a Java-like StringTokenizer
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

#include "StringTokenizer.h"

namespace de { namespace bswalz {

// ------------------------------------------------------------
// Specialization TStringTokenizer<std::string>
// ------------------------------------------------------------
// 2016-09-15: if not commented out, clang reports an error: "implicit instantiation first required here"
//             gcc (and possibly others) are more permissive.
//             See: https://stackoverflow.com/questions/25200678/static-member-initialization-after-instantiation-in-clang
//template <>
//TStringTokenizer<string>::TStringTokenizer(string str)
//	: TStringTokenizer<string>::TStringTokenizer(str, " ", false) {}

// ------------------------------------------------------------
template <>
TStringTokenizer<string>::TStringTokenizer(string str, string delimiters, bool delimAsToken)
	: m_tokens(), m_pos(0) {
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		// Found a token, add it to the vector.
		m_tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
		} // End while
     
	// Sets the iterator to beginning
	m_pos = 0;
}

// ------------------------------------------------------------
// Specialization TStringTokenizer<std::string>
// ------------------------------------------------------------
// See above at TStringTokenizer<string>::TStringTokenizer(string str)
//template <>
//TStringTokenizer<wstring>::TStringTokenizer(wstring str)
//	: TStringTokenizer<wstring>::TStringTokenizer(str, " ", false) {}

// ------------------------------------------------------------
template <>
TStringTokenizer<wstring>::TStringTokenizer(wstring str, wstring delimiters, bool delimAsToken)
	: m_tokens(), m_pos(0) {
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		// Found a token, add it to the vector.
		m_tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
		} // End while

	// Sets the iterator to beginning
	m_pos = 0;
}


}} // End namespaces
