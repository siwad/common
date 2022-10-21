/**
 * Model class of MVC pattern
 *
 * @copyright	2005 Siegfried Walz
 * @license     https://www.gnu.org/licenses/lgpl-3.0.txt GNU Lesser General Public License
 * @author      Siegfried Walz
 * @link        https://software.bswalz.de/
 * @package     common/model
 */
/*
 * This file is part of common/model
 *
 * common/model is free software: you can redistribute it and/or modify
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


#include "EnumParameter.h"

namespace de { namespace bswalz { namespace model {

// -------------------------------------------------------------------
// Class CEnumParameter
// -------------------------------------------------------------------
CEnumParameter::CEnumParameter(std::string name, int initValue, var_array<int> range)
	: TParameter<int>(name, initValue), m_ValidRange(range), m_Range(range) {
	// Intentionally left blank
}

// -------------------------------------------------------------------
bool CEnumParameter::assignValue(const int & value, const IAssignRule*) {
	updateRange();
   for (int i = 0; i < m_ValidRange.size(); i++) {
	  if (value == m_ValidRange[i]) {
		 if (value != m_Value)
			TParameter<int>::assignValue(value);
		 break;
		 } // End if value in valid range
	  } // End for
   return true;
}

// -------------------------------------------------------------------
void CEnumParameter::assignValue(std::string s) {
   int value = m_Value;
   if (m_spTranslator.get() != NULL)
      m_spTranslator->translate(this, s, value);
   else {
	  try { value = std::stoi(s); }
	  catch (...) {}
      } 
       
   CEnumParameter::assignValue(value);
}

// -------------------------------------------------------------------
int CEnumParameter::getNextValue() {
   updateRange();
   int size = m_ValidRange.size();
   for (int i = 0; i < size; i++) {
	  if (m_Value == m_ValidRange[i]) {
		 return (i < (size-1)) ? m_ValidRange[i+1] : m_ValidRange[0]; 
	     }
      }
   return -1; // Should never occur !!
}

// -------------------------------------------------------------------
int CEnumParameter::getPrevValue() {
   updateRange();
   int size = m_ValidRange.size();
   for (int i = 0; i < size; i++) {
	  if (m_Value == m_ValidRange[i]) {
		 return (i > 0) ? m_ValidRange[i-1] : m_ValidRange[size-1]; 
	     }
      }
   return -1; // Should never occur !!
}

// -------------------------------------------------------------------
std::string CEnumParameter::getValueAsString() {
   std::string s("");
   if (m_spTranslator.get() != NULL)
      m_spTranslator->translate(this, m_Value, s);
   else
	  s = std::to_string(m_Value);
      
   return s;
}

// -------------------------------------------------------------------
std::string CEnumParameter::getValueAsString(int value) {
   std::string s("");
   if (m_spTranslator.get() != NULL)
      m_spTranslator->translate(this, value, s);
   else
	  s = std::to_string(value);
      
   return s;
}

// -------------------------------------------------------------------
var_array<int> & CEnumParameter::getValidRange() {
   updateRange();
   return m_ValidRange;
}

// -------------------------------------------------------------------
bool CEnumParameter::validRangeIsEmpty() {
   return m_ValidRange.empty();
}

// -------------------------------------------------------------------
void CEnumParameter::updateRange() {
   if (m_spLimiter) {
      m_spLimiter->limitRange(this, m_ValidRange);
	  if (m_ValidRange.indexOf(m_Value) == -1 && m_ValidRange.size() > 0)
    	 TParameter<int>::assignValue(m_ValidRange[0]); // Do not use this->assignValue() !!
      }
}

}}} // End namespaces

