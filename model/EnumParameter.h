#ifndef _DE_BSWALZ_MODEL_ENUMPARAMETER_H_
#define _DE_BSWALZ_MODEL_ENUMPARAMETER_H_

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
#include "../VarArray.h"

using de::bswalz::mvc::IAssignRule;

namespace de { namespace bswalz { namespace model {

class CEnumParameter;

/**
  * The translator interface of CEnumParameter. This interface is used
  * either by assign(std::string) or getValueAsString().
  */
class IEnumTranslator {
public:
   virtual ~IEnumTranslator() {};
   /**
    * Translates from string to int (enum)
    * @param p the instance of CEnumParameter which requests translation
    * @param src the string which should be translated
    * @param dest the value which will be assigned to the parameter after translation
    */
    virtual void translate(CEnumParameter * p, std::string src, int & dest) = 0;
    /**
     * Translates from int (enum) to string
     * @param p the instance of CEnumParameter which requests translation
     * @param src the current value of the instance of CEnumParameter
     * @param dest the translation which will be used by getValueAsString()
     */
    virtual void translate(CEnumParameter * ,int src, std::string & dest) = 0;
};

/**
 * The limiter interface used by CEnumParameter. This interface will
 * be used when getValidRange() is invoked.
 */
class IEnumLimiter {
   public:
      virtual ~IEnumLimiter() {};
      /**
       * Possibility to change the valid range of an instance of CEnumParameter.
       * @param p the instance of CEnumParameter which requests update of valid range.
       * @param range the reference to the valid range object.
       */
	  virtual void limitRange(CEnumParameter *, var_array<int> & validRange) = 0;
};

/**
 * The parametrized enumeration Parameter class of the Model-View-Controller pattern.<br>
 * This parameter contains discrete values of type 'int'.  
 * It repersents a setting, which has an assigned value, a default value,
 * and a range of discrete values.
 */
class CEnumParameter : public TParameter<int> {
public:
    
public:
    /**
     * Constructor of template class TEnumParameter.<br>
     * @param name the name of the parameter
     * @param initValue the initial value
     * @param range the specified range of this enum. parameter
     */
	CEnumParameter(std::string name, int initValue, var_array<int> range);
	virtual ~CEnumParameter() {};
    
    /**
     * @return the currently valid range within the range of specified values.
     * ILimiter::limitRange(CEnumParameter *, TArray<int> & validRange) will be invoked
     * in advance if a limiter object is present.
     */
	var_array<int> &      getValidRange();
    
    /**
     * @return the full range of specified values
     */
	var_array<int> &      getRange() { return m_Range; }
    
    /**
     * Assigns a value.
     */
	virtual bool		assignValue(const int &, const IAssignRule* = nullptr) override;

    /**
     * Assigns a value from string. 
     * ITranslator::translate(CEnumParameter * p, std::string src, int & dest)
     * will be invoked in advance. If no translator object is available
     * boost::lexical_cast will be used.
     */
    void               assignValue(std::string);
    
    /**
     * @return the currently assigned value as string.
     * ITranslator::translate(CEnumParameter * p, int src, std::string & dest)
     * will be invoked in advance. If no translator object is available
     * boost::lexical_cast will be used.
     */ 
    std::string        getValueAsString();
    
    /**
     * @param value
     * @return parameter 'value' as string.
     * ITranslator::translate(CEnumParameter * p, int src, std::string & dest)
     * will be invoked in advance. If no translator object is available
     * boost::lexical_cast will be used.
     */ 
    std::string        getValueAsString(int value);
    
    /**
     * @return the value of the next element within the valid range. If the
     * next value would exceed the valid range, the first value within
     * the valid range will be returned. Note: check first if valid range is
     * empty!
     */
    int                getNextValue(); 
    
    /**
     * @return the value of the previous element within the valid range. If the
     * previous value would exceed the valid range, the last value within
     * the valid range will be returned. Note: check first if valid range is
     * empty!
     */
    int                getPrevValue(); 
    
    /**
     * Convenience method.
     * @return true if valid range is empty
     */
    bool               validRangeIsEmpty();
    
    /**
     * Attaches a limiter to this instance of CEnumParameter
     */
	void               setLimiter(std::shared_ptr<IEnumLimiter> l)   { m_spLimiter = l; };
    
    /**
     * Attaches a translator to this instance of CEnumParameter
     */
	void               setTranslator(std::shared_ptr<IEnumTranslator> t) { m_spTranslator = t; };
    
protected:
	var_array<int>        m_ValidRange;
	var_array<int>        m_Range;
    
private:
	void               updateRange();
	std::shared_ptr<IEnumLimiter>    m_spLimiter;
	std::shared_ptr<IEnumTranslator> m_spTranslator;

protected:
	CEnumParameter() : TParameter<int>() { }

private:

};

}}} // End namespaces

#endif /*_DE_BSWALZ_MODEL_ENUMPARAMETER_H_*/
