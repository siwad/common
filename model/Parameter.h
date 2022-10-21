#ifndef _DE_BSWALZ_MODEL_PARAMETER_H_
#define _DE_BSWALZ_MODEL_PARAMETER_H_

#include "../mvc/Model.h"
#include "../mvc/View.h"
#include "../sync/Synchronized.h"
#include "../VarArray.h"
#include "NumLimits.h"
#include <string>

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

using de::bswalz::mvc::IAssignRule;
using de::bswalz::mvc::TAssignRule;

namespace de { namespace bswalz { namespace model {

/**
 * The parametrized Parameter class of the Model-View-Controller pattern.<br>
 * A parameter is represents a setting, which has an assigned and a default value.
 * The parameter may be relevant or not relevant
 */
template <typename T> class TParameter : public mvc::TModel<T>,
                                         protected mvc::View {
public:
    /**
     * Constructor of template class TParameter.<br>
     * @param name the name of the parameter
     * @param initValue the initial value
     * @param sync switch for synchronous/asynchronous update mode
     */
	TParameter(const std::string & name, T initValue, bool sync = true);
    virtual ~TParameter();

    /**
     * Sets the parameter as relevant / non-relevant
     * @param relevant if true the parameter is relevant
     */
    void     setRelevance(bool relevant);

    /**
     * @return the relevance of this parameter
     */
	bool     isRelevant() const { return m_Relevance; };

    /**
     * Delegates relevance to a parameter
     */
	void     setRelevanceParameter(std::shared_ptr<TParameter<bool> >);

    /**
     * @return the default value
     */
	const T & getDefaultValue() const { return m_DefaultValue; };

    /**
     * @return true if current value is the default value
     */
	virtual bool isDefaultValue() const ;

    /**
     * Sets the current value to the default value
     */
	virtual void setDefaultValue();

    /**
     * Inherited from mvc::View
     */
	virtual void update(const mvc::Model * pModel, void * pObject);

protected:
    bool               m_Relevance;
    T                  m_DefaultValue;
	std::shared_ptr<TParameter<bool> > m_spRelevanceParameter;

protected:
	TParameter() : mvc::TModel<T>() { }
};


/**
 * The parametrized numeric Parameter class of the Model-View-Controller pattern.<br>
 * A parameter is repersents a setting, which has an assigned value, a default value,
 * a min. and a max. value
 */
template <typename T> class TNumParameter : public TParameter<T>  {
public:
    /**
     * Constructor of template class TNumParameter.<br>
     * @param name the name of the parameter
     * @param initValue the initial value
     * @param minValue the min. value of this parameter
     * @param maxValue the min. value of this parameter
     */
	TNumParameter(const std::string & name, const T initValue, T minValue, T maxValue, T step = (T)1);

    /**
     * Constructor of template class TNumParameter.<br>
     * The parameter operates in synchronous mode. The limits are:
     * MIN_VALUE and MAX_VALUE of type T.
     * @param name the name of the parameter
     * @param initValue the initial value
     */
	TNumParameter(const std::string & name, T initValue = 0);

    /**
     * Constructor of template class TNumParameter.<br>
     * The parameter operates in synchronous mode. The limits are:
     * MIN_VALUE and MAX_VALUE of type T. The parameter has no name.
     * @param initValue the initial value
     */
	TNumParameter(const T & initValue);

	TNumParameter() : de::bswalz::model::TParameter<T>(), m_pNumLimits(nullptr) { }
    virtual ~TNumParameter() {};

	/**
	 * Assigns a new value to the model. The method checks
	 * against min. and max. values of this model
	 * @param value the new value
	 * @return true if the assignment has been successfully performed
	 */
	virtual bool assignValue(const T & value, const IAssignRule* = nullptr ) override;

	/**
     * For convenience. Assigns a new value to the model.
     * @param s the stringified new value
	 */
	virtual void assignValue(const std::string & s );

    /**
     * Sets the current value to the default value
     */
	virtual void setDefaultValue() override;

	/**
     * @return the currently assigned value as string.
	 */
	virtual std::string getValueAsString() const;

    /**
     * @return min. value
     */
	T        getMinValue();

    /**
     * @return max. value
     */
	T        getMaxValue();

    /**
     * @return the value of the next step. If the current value is the max.
     * value, the max. value will be returned.
     */
	T        getNextValue();

	 /**
	 * @return the value of the next step. If the current value is the max.
	 * value, the min. value will be returned. (rotated)
	 */
	 T        getNextValueRotated();

    /**
     * @return the value of the previous step. If the current value is the min.
     * value, the min. value will be  returned.
     */
	T        getPrevValue();

	 /**
	 * @return the value of the previous step. If the current value is the min.
	 * value, the max. value will be  returned. (rotated)
	 */
	 T        getPrevValueRotated();

    /**
     * Assign an instance of TNumLimit<T> to this TNumParameter<T>.
     */
    void     setNumLimits(TNumLimits<T> *);

protected:
    T              m_MinValue;
    T              m_MaxValue;
    T              m_Step;
    sync::CMutex   m_Mutex;
    TNumLimits<T>* m_pNumLimits;
};


/**
 * The parametrized array Parameter class of the Model-View-Controller pattern.<br>
 * A parameter is repersents a var-array-type setting, which has an assigned value.
 */
template <typename T> class TVarArrayParameter : public TParameter<de::bswalz::var_array<T> >  {
public:
	TVarArrayParameter(const std::string & name, const de::bswalz::var_array<T> & initValue);
	TVarArrayParameter(const de::bswalz::var_array<T> & initValue);
    TVarArrayParameter();
    virtual ~TVarArrayParameter() {};

    /**
     * Assigns a new value to the model.
     * @param value the new value
     */
	virtual bool assignValue(const de::bswalz::var_array<T> & value, const IAssignRule* = nullptr ) override;

    /**
     * Assigns a new value to the model.
     * @param s the stringified new value
     */
	virtual void assignValue(const std::string & );

    /**
     * @return the currently assigned value as string.
     */
	virtual std::string getValueAsString() const;

    /**
     * Assigns a new value of an array element.
     * @param value the new value
     * @param idx the index of the array element
     */
    void assignElementValue( T value, unsigned int idx  );

	/**
     * @return the currently assigned element value.
	 */
	T &  getElementValue(unsigned int idx) const;

	/**
	 * @return the default value of an array's element
	 */
	T &  getElementDefaultValue(unsigned int idx) const;

	/**
	 * @return true if the array's element contains the default
	 * value
	 */
	bool isElementDefaultValue(unsigned int idx) const;

	/**
	 * @return true if the array's elements contains the default
	 * values
	 */
	virtual bool isDefaultValue() const;

	/**
	 * @return the size of T[]
	 */
	unsigned int getArraySize() const;

protected:
    unsigned int  m_Size;
    sync::CMutex  m_Mutex;
};



typedef TNumParameter<short>                 CShortParameter;
typedef TNumParameter<int>                   CIntParameter;
typedef TNumParameter<long>                  CLongParameter;
typedef TNumParameter<long long>             CLongLongParameter;
typedef TNumParameter<unsigned short>        CUShortParameter;
typedef TNumParameter<unsigned int>          CUIntParameter;
typedef TNumParameter<unsigned long>         CULongParameter;
typedef TNumParameter<unsigned long long>    CULongLongParameter;
typedef TNumParameter<float>                 CFloatParameter;
typedef TNumParameter<double>                CDoubleParameter;
typedef TParameter<bool>                     CBoolParameter;


typedef TParameter<std::string>              CAStringParameter;
typedef TParameter<std::wstring>             CWStringParameter;


typedef TVarArrayParameter<bool>             CBoolArrayParameter;
typedef TVarArrayParameter<int>              CIntArrayParameter;
typedef TVarArrayParameter<long>             CLongArrayParameter;
typedef TVarArrayParameter<long long>        CLongLongArrayParameter;
typedef TVarArrayParameter<unsigned short>   CUShortArrayParameter;
typedef TVarArrayParameter<unsigned int>     CUIntArrayParameter;
typedef TVarArrayParameter<unsigned long>    CULongArrayParameter;
typedef TVarArrayParameter<unsigned long long> CULongLongArrayParameter;
typedef TVarArrayParameter<float>            CFloatArrayParameter;
typedef TVarArrayParameter<double>           CDoubleArrayParameter;


#include "Parameter.inl"

}}} // End namespaces

#endif /*_DE_BSWALZ_MODEL_PARAMETER_H_*/
