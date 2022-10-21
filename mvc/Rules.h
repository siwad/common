#ifndef _DE_BSWALZ_MVC_RULES_H_
#define _DE_BSWALZ_MVC_RULES_H_

/**
 * Rules classes of MVC pattern
 *
 * @copyright	2005 Siegfried Walz
 * @license     https://www.gnu.org/licenses/lgpl-3.0.txt GNU Lesser General Public License
 * @author      Siegfried Walz
 * @link        https://software.bswalz.de/
 * @package     common/mvc
 */
/*
 * This file is part of common/mvc
 *
 * common/mvc is free software: you can redistribute it and/or modify
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

/* APPLICATION NOTE of TAssignRule and TVoter
 * -------------------------------------------------------------------------
 *	// Application of AssignRule
 *	// Here: Value of m_pUShortParameter -> m_pUIntParameter
 *	class MyAssignRule : public TAssignRule<unsigned short> {
 *	public:
 *		MyAssignRule(CUIntParameter * pDestParameter)
 *			: TAssignRule<unsigned short>(), m_pDestParameter(pDestParameter) {}
 *		virtual ~MyAssignRule() {}
 *		virtual void apply(TModel<unsigned short> * pSource) override {
 *							unsigned short v = dynamic_cast<CUShortParameter*>(pSource)->getValue();
 *							m_pDestParameter->assignValue(v, this);
 *							};
 *		virtual void revert() override {
 *							m_pDestParameter->revertAssignment();
 *							};
 *		virtual bool validate() override {
 *							return m_pDestParameter->getVoter()->vote();
 *							};
 *	private:
 *		CUIntParameter * m_pDestParameter;
 *	}; // End class MyAssignRule
 *	m_pUShortAssignRule.reset( new MyAssignRule(m_pUIntParameter.get()) );
 *	m_pUShortParameter->addAssignRule(m_pUShortAssignRule.get());
 *
 *	// Application of Voter
 *	// Here: Voter does not accept values < 1000
 *	class MyVoter : public TVoter<unsigned int> {
 *	public:
 *		MyVoter(CUIntParameter * pParameter)
 *			: TVoter<unsigned int>(), m_pDestParameter(pParameter) {}
 *		virtual ~MyVoter() {}
 *		virtual bool vote() override {
 *							unsigned int v = m_pDestParameter->getValue();
 *							return v >= 1000;
 *							};
 *	private:
 *		CUIntParameter * m_pDestParameter;
 *	}; // End class MyVoter
 *	m_pUIntVoter.reset( new MyVoter(m_pUIntParameter.get()) );
 *	m_pUIntParameter->setVoter(m_pUIntVoter);
 */

namespace de { namespace bswalz { namespace mvc {

template <typename T> class TModel;

/**
 * Marker interface of AssignRule
 */
class IAssignRule {
public:
	virtual ~IAssignRule() = 0;
};
inline IAssignRule::~IAssignRule() {}

/**
 * TAssignRule::apply is applied during assignment of a parameter's value.<br>
 * The intension behind an AssignRule is to modify a secondary model dependent on
 * the just modified source model.<p>
 * Additionally the assignment could be reverted and voted.
 */
template <typename T> class TAssignRule : public IAssignRule {
public:
	TAssignRule() {};
	virtual ~TAssignRule() {};
	
	virtual void apply(TModel<T> * pSource) = 0;
	virtual void revert() = 0;
	virtual bool validate() { return true; }
};

/**
 * TVoter::vote is applied during commitment of a parameter's value.<br>
 * The intentions behind the TVoter is verifying the consistency of an entire set of models.
 */
template <typename T> class TVoter {
public:
	TVoter() {};
	virtual ~TVoter() {};
	virtual bool vote() = 0;
};

}}} // End namespaces

#endif /*_DE_BSWALZ_MVC_RULES_H_*/
