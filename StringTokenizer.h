#ifndef _DE_BSWALZ_STRINGTOKENIZER_H_
#define _DE_BSWALZ_STRINGTOKENIZER_H_

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
#include <string>
#include <vector>

using namespace std;


namespace de { namespace bswalz {

/**
 * Template Class for instances of std::string, std::wstring, ...<br>
 * which meet the following conditions resp. definitions: <br>
 * T::T(), T::size_type, T::npos,
 * <p>
 * This template class is affected by Java's java.util.StringTokenizer class.
 * <p>
 * The StringTokenizer class allows an application to break a string into tokens.
 * The StringTokenizer methods do not distinguish among identifiers, numbers, and quoted strings, nor do they recognize and skip comments.
 * The set of delimiters (the characters that separate tokens) may be specified at creation time.
 * <p>
 * An instance of StringTokenizer behaves in one of two ways, depending on whether it was created with the returnDelims flag having the value true or false:
 * <ul>
 * If the flag is false, delimiter characters serve to separate tokens. A token is a maximal sequence of consecutive characters that are not delimiters.
 * <ul>
 * If the flag is true, delimiter characters are themselves considered to be tokens. A token is thus either one delimiter character, or a maximal sequence of consecutive characters that are not delimiters.
 * <p>
 * A token is returned by taking a substring of the string that was used to create the StringTokenizer object.
 */

template <typename T> class TStringTokenizer {
public:
    /**
     * Constructs a string tokenizer for the specified string. 
     * The tokenizer uses the default delimiter set, which is " ": the space character. 
     * Delimiter characters themselves will not be treated as tokens.
     * @param str a string to be parsed.
     */
    TStringTokenizer(T str);

    /**
     * Constructs a string tokenizer for the specified string. 
     * All characters in the delim argument are the delimiters for separating tokens.
     * <p>
     * If the delimAsToken flag is true, then the delimiter characters are also 
     * returned as tokens. Each delimiter is returned as a string of length one. 
     * If the flag is false, the delimiter characters are skipped and only serve 
     * as separators between tokens.
     * @param str a string to be parsed.
     * @param delimiters the delimiters
     * @param delimAsToken flag indicating whether to return the delimiters as tokens.
     * (delimAsToken = true: not impl. yet)
     */
    TStringTokenizer(T str, T delimiters, bool delimAsToken = false);
    
    virtual ~TStringTokenizer() { m_tokens.clear(); };
    
    /**
     * Calculates the number of times that this tokenizer's nextToken 
     * method can be called before it generates an exception. 
     * The current position is not advanced.
     * @return the number of tokens remaining in the string using the current 
     * delimiter set.
     */
    unsigned int countTokens() { return m_tokens.size(); };

    /**
     * Tests if there are more tokens available from this tokenizer's string. 
     * If this method returns true, then a subsequent call to nextToken 
     * with no argument will successfully return a token.
     * @return true if and only if there is at least one token in the string 
     * after the current position; false otherwise
     */
	bool     hasMoreTokens()   { return m_pos < m_tokens.size(); };
 
    /**
     * Same as hasMoreTokens()
     * @return true if and only if there is at least one token in the string 
     * after the current position; false otherwise
     */
    bool     hasMoreElements() { return hasMoreTokens(); };

    /**
     * @return the next token from this string tokenizer.
     */
	T &      nextElement()     { return nextToken(); };
    /**
     * @return the next token from this string tokenizer.
     */
	T &      nextToken()       { return m_tokens[m_pos++]; };

private:
	std::vector<T>           m_tokens;
	unsigned int             m_pos;
};

typedef TStringTokenizer<std::string>        StringTokenizer;
typedef TStringTokenizer<std::wstring>       WStringTokenizer;


// ------------------------------------------------------------------------------
// Inline implementations
// ------------------------------------------------------------------------------
template <typename T> inline
TStringTokenizer<T>::TStringTokenizer(T str)
   : TStringTokenizer<string>::TStringTokenizer(str, " ", false) {}

// ------------------------------------------------------------------------------
template <typename T> inline
TStringTokenizer<T>::TStringTokenizer(T str, T delimiters, bool )
   : m_tokens(), m_pos(0) {
   // Skip delimiters at beginning.
   typename T::size_type lastPos = str.find_first_not_of(delimiters, 0);
   // Find first "non-delimiter".
   typename T::size_type pos     = str.find_first_of(delimiters, lastPos);

   while (T::npos != pos || T::npos != lastPos) {
     // Found a token, add it to the vector.
     m_tokens.push_back(str.substr(lastPos, pos - lastPos));
     // Skip delimiters.  Note the "not_of"
     lastPos = str.find_first_not_of(delimiters, pos);
     // Find next "non-delimiter"
     pos = str.find_first_of(delimiters, lastPos);
     }

   // Sets the iterator to begin()
   m_pos = 0;
}

}} // End namespaces

#endif /*_DE_BSWALZ_STRINGTOKENIZER_H_*/
