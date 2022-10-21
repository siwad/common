
// -------------------------------------------------------
// Template class TModel<T>
// -------------------------------------------------------
template <typename T>
de::bswalz::mvc::TModel<T>::TModel(std::string name, T value)
	: Model(name), m_Value(value), m_CurrValue(value), m_spVoter()
{ /* Intentionally left blank */ }; 
	   
// -------------------------------------------------------
template <typename T>
de::bswalz::mvc::TModel<T>::~TModel() {
	m_pAssignRules.clear();
	m_spVoter.reset();
};
	   
// -------------------------------------------------------
template <typename T>
bool de::bswalz::mvc::TModel<T>::assignValue( const T & value, const IAssignRule* pRule ) {
	bool success = true;
	if (!Model::hasChanged()) {
		synchronized(m_Mutex) {
			m_CurrValue = m_Value;
			m_Value     = value;
			applyAssignRules();
			if (pRule == nullptr && !validateAssignment()) {
				revertAssignment();
				success = false;
				}
			else {
				m_CurrValue = value;
				setChanged();
				}
			} // End synchronized
		notifyAll();
		} // End if hasChanged() == false
	return success;
};

// -------------------------------------------------------
template <typename T>
void de::bswalz::mvc::TModel<T>::revertAssignment() {
	m_Value = m_CurrValue;
	for (auto pAssignRule : m_pAssignRules) {
		pAssignRule->revert();
		}
}

// -------------------------------------------------------
template <typename T>
bool de::bswalz::mvc::TModel<T>::validateAssignment() {
	if (m_spVoter.get() != nullptr && !m_spVoter->vote())
		return false;

	for (auto pAssignRule : m_pAssignRules) {
		if (!pAssignRule->validate())
			return false;
		}

	return true;
}

// -------------------------------------------------------
template <typename T>
T & de::bswalz::mvc::TModel<T>::getValue() { 
	return m_Value;
};
   
// -------------------------------------------------------
template <typename T>
void de::bswalz::mvc::TModel<T>::addAssignRule(TAssignRule<T> * pRule, bool initialAppl) {
	m_pAssignRules.push_back(pRule);
	if (initialAppl)
		pRule->apply(this);
};

// -------------------------------------------------------
template <typename T>
void de::bswalz::mvc::TModel<T>::setVoter(std::shared_ptr<TVoter<T>> spVoter) {
	m_spVoter = spVoter;
};

// -------------------------------------------------------
template <typename T>
void de::bswalz::mvc::TModel<T>::applyAssignRules() {
	for (auto pAssignRule : m_pAssignRules) {
		pAssignRule->apply(this);
		}
};

	   
