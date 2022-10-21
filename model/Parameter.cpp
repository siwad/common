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


#include "Parameter.h"
#include "../StringTokenizer.h"
#include <limits.h>
#include <float.h>

#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX	9223372036854775807LL
#endif

#ifndef LONG_LONG_MIN
#define LONG_LONG_MIN	(-LONG_LONG_MAX-1)
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX	(2ULL * LONG_LONG_MAX + 1)
#endif

namespace de { namespace bswalz { namespace model {

// -----------------------------------------------------------
// TNumParameter<T>
// -----------------------------------------------------------
template <>
TNumParameter<short>::TNumParameter(const std::string & name, short value)
   : TParameter<short>(name, value), 
     m_MinValue(SHRT_MIN), m_MaxValue(SHRT_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<short>::assignValue(const std::string & s) {
	try { short v = ::stoi(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<short>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<int>::TNumParameter(const std::string & name, int value)
   : TParameter<int>(name, value), 
     m_MinValue(INT_MIN), m_MaxValue(INT_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<int>::assignValue(const std::string & s) {
	try { int v = ::stoi(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<int>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<long>::TNumParameter(const std::string & name, long value)
   : TParameter<long>(name, value), 
     m_MinValue(LONG_MIN), m_MaxValue(LONG_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<long>::assignValue(const std::string & s) {
	try { long v = ::stol(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<long>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<long long>::TNumParameter(const std::string & name, long long value)
   : TParameter<long long>(name, value), 
     m_MinValue(LONG_LONG_MIN), m_MaxValue(LONG_LONG_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<long long>::assignValue(const std::string & s) {
	try { long long v = ::stoll(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<long long>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<unsigned short>::TNumParameter(const std::string & name, unsigned short value)
   : TParameter<unsigned short>(name, value), 
     m_MinValue(0), m_MaxValue(USHRT_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<unsigned short>::assignValue(const std::string & s) {
	try { unsigned short v = ::stoul(s); assignValue(v); } // C++11
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<unsigned short>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<unsigned int>::TNumParameter(const std::string & name, unsigned int value)
   : TParameter<unsigned int>(name, value), 
     m_MinValue(0), m_MaxValue(UINT_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<unsigned int>::assignValue(const std::string & s) {
	try { unsigned int v = ::stoul(s); assignValue(v); } // C++11
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<unsigned int>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<unsigned long>::TNumParameter(const std::string & name, unsigned long value)
   : TParameter<unsigned long>(name, value), 
     m_MinValue(0L), m_MaxValue(ULONG_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<unsigned long>::assignValue(const std::string & s) {
	try { unsigned long v = ::stoul(s); assignValue(v); } // C++11
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<unsigned long>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<unsigned long long>::TNumParameter(const std::string & name, unsigned long long value)
   : TParameter<unsigned long long>(name, value), 
     m_MinValue(0L), m_MaxValue(ULONG_LONG_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<unsigned long long>::assignValue(const std::string & s) {
	try { unsigned long long v = ::stoull(s); assignValue(v); } // C++11
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<unsigned long long>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<float>::TNumParameter(const std::string & name, float value)
   : TParameter<float>(name, value), 
     m_MinValue(-FLT_MAX), m_MaxValue(FLT_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<float>::assignValue(const std::string & s) {
	try { float v = ::stof(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<float>::getValueAsString() const {
	return std::to_string(m_Value);
}

// -----------------------------------------------------------
template <>
TNumParameter<double>::TNumParameter(const std::string & name, double value)
   : TParameter<double>(name, value), 
     m_MinValue(-DBL_MAX), m_MaxValue(DBL_MAX), m_pNumLimits(NULL) {
}

// -----------------------------------------------------------
template <>
void TNumParameter<double>::assignValue(const std::string & s) {
	try { double v = ::stod(s); assignValue(v); }
	catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TNumParameter<double>::getValueAsString() const {
	return std::to_string(m_Value);
}



// -----------------------------------------------------------
// TVarArrayParameter<T>
// -----------------------------------------------------------
template <>
void TVarArrayParameter<bool>::assignValue(const std::string & s ) {
   de::bswalz::var_array<bool> value(m_Value);
   StringTokenizer st(s, ",");
   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken();
		 bool   v = ( ::stoi(token) != 0) ? true : false;
         };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<int>::assignValue(const std::string & s ) {
   de::bswalz::var_array<int> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 int    v = ::stoi(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<long>::assignValue(const std::string & s ) {
   de::bswalz::var_array<long> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 long   v = ::stol(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<long long>::assignValue(const std::string & s ) {
   de::bswalz::var_array<long long> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 long long v = ::stoll(token);
		 value[i]    = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<unsigned short>::assignValue(const std::string & s ) {
   de::bswalz::var_array<unsigned short> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 unsigned short v = ::stoul(token);
		 value[i]         = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<unsigned int>::assignValue(const std::string & s ) {
   de::bswalz::var_array<unsigned int> value(m_Value);
   StringTokenizer st(s, ",");
   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 unsigned int    v = ::stoul(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<unsigned long>::assignValue(const std::string & s ) {
   de::bswalz::var_array<unsigned long> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 unsigned long   v = ::stoul(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<unsigned long long>::assignValue(const std::string & s ) {
   de::bswalz::var_array<unsigned long long> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 unsigned long long v = ::stoull(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<float>::assignValue(const std::string & s ) {
   de::bswalz::var_array<float> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 float           v = ::stof(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
void TVarArrayParameter<double>::assignValue(const std::string & s ) {
   de::bswalz::var_array<double> value(m_Value);
   StringTokenizer st(s, ",");
	   
   try {
	  for (int i = 0; i < m_Value.size() && st.hasMoreTokens(); i++) {
         std::string token = st.nextToken(); 
		 double          v = ::stod(token);
		 value[i] = v;
		 };
      assignValue(value);
      }
   catch (...) {}
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<bool>::getValueAsString() const {
   std::string s;
   const unsigned int arraySize = m_Value.size();
   for (int i = 0; i < arraySize; i++) {
	  const bool & v = m_Value[i];
	  s += to_string( (v) ? 1 : 0 );
	  if (i < (arraySize-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<int>::getValueAsString() const {
   std::string s;
   const int * pData = m_Value.data();
   int           end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<long>::getValueAsString() const {
   std::string s;
   const long * pData = m_Value.data();
   int            end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<long long>::getValueAsString() const {
   std::string s;
   const long long * pData = m_Value.data();
   int                 end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<unsigned short>::getValueAsString() const {
   std::string s;
   const unsigned short * pData = m_Value.data();
   int                      end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<unsigned int>::getValueAsString() const {
   std::string s;
   const unsigned int * pData = m_Value.data();
   int                    end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<unsigned long>::getValueAsString() const {
   std::string s;
   const unsigned long * pData = m_Value.data();
   int                     end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<unsigned long long>::getValueAsString() const {
   std::string s;
   const unsigned long long * pData = m_Value.data();
   int                          end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<float>::getValueAsString() const {
   std::string s;
   const float * pData = m_Value.data();
   int             end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

// -----------------------------------------------------------
template <>
std::string TVarArrayParameter<double>::getValueAsString() const {
   std::string s;
   const double * pData = m_Value.data();
   int              end = m_Value.size();
   
   for (int i = 0; i < end; i++) {
	  s += to_string( *(pData + i) );
      if (i < (end-1)) s += ",";
      }
   
   return s;
}

}}} // End namespaces
