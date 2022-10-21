// -----------------------------------------------------------
// Template class TParameter<T>
// -----------------------------------------------------------
template <typename T>
TParameter<T>::TParameter(const std::string & name, T initValue, bool syncMode)
	: mvc::TModel<T>(name, initValue), mvc::View(),
		m_Relevance(true), m_DefaultValue(initValue),
		m_spRelevanceParameter() {
	mvc::Model::setSyncMode(syncMode) ;
};

// -----------------------------------------------------------
template <typename T>
TParameter<T>::~TParameter() {
	if (m_spRelevanceParameter.get())
		mvc::View::unregisterAt(m_spRelevanceParameter.get());
};

// -----------------------------------------------------------
template <typename T>
void TParameter<T>::setRelevance(bool relevant) {
	if (m_spRelevanceParameter.get())
		{ m_spRelevanceParameter->assignValue(relevant); }
	else {
		m_Relevance = relevant;
		mvc::Model::setChanged();
		mvc::Model::notifyAll();
		}
};

// -----------------------------------------------------------
template <typename T>
void TParameter<T>::setRelevanceParameter(std::shared_ptr<TParameter<bool> > spParameter) {
	m_spRelevanceParameter = spParameter;
	mvc::View::registerAt(m_spRelevanceParameter.get());
};

// -----------------------------------------------------------
template <typename T>
bool TParameter<T>::isDefaultValue() const {
	return m_DefaultValue == TParameter<T>::m_Value;
};

// -----------------------------------------------------------
template <typename T>
void TParameter<T>::setDefaultValue() {
	TParameter<T>::m_Value = m_DefaultValue;
	mvc::Model::setChanged();
	mvc::Model::notifyAll();
};

// -----------------------------------------------------------
template <typename T>
void TParameter<T>::update(const mvc::Model * pModel, void *) {
	if (pModel == m_spRelevanceParameter.get())
		m_Relevance = m_spRelevanceParameter->getValue();
	mvc::Model::setChanged();
	mvc::Model::notifyAll();
}



// -----------------------------------------------------------
// Template class TNumParameter<T>
// -----------------------------------------------------------
template <typename T>
TNumParameter<T>::TNumParameter(const std::string & name, T initValue, T minValue, T maxValue, T step)
	: TParameter<T>(name, initValue),
		m_MinValue(minValue), m_MaxValue(maxValue),
		m_Step(step), m_pNumLimits(nullptr) {
	// Intentionally left blank
};

// -----------------------------------------------------------
template <typename T>
TNumParameter<T>::TNumParameter(const T & initValue)
	: TParameter<T>(std::string(__FILE__) + std::string(":") + std::to_string(__LINE__), initValue) {
	// Intentionally left blank
};

// -----------------------------------------------------------
template <typename T>
bool TNumParameter<T>::assignValue(const T & value, const IAssignRule* pRule) {
	bool success = true;
	if (!mvc::Model::hasChanged()) {
		synchronized(m_Mutex) {
			T m_CurrValue = mvc::TModel<T>::m_Value;
			if      (value < getMinValue()) mvc::TModel<T>::m_Value = getMinValue();
			else if (value > getMaxValue()) mvc::TModel<T>::m_Value = getMaxValue();
			else                            mvc::TModel<T>::m_Value = value;

			mvc::TModel<T>::applyAssignRules();

			if (pRule == nullptr && !mvc::TModel<T>::validateAssignment()) {
				// Validation only on originally assigned parameter, not on assignment caused by AssignRule
				mvc::TModel<T>::revertAssignment();
				success = false;
				}
			if (m_CurrValue != value) { // Notifies also if value has been limited
				m_CurrValue = mvc::TModel<T>::m_Value;
				mvc::Model::setChanged();
				}
			} // End synchronized
      
		if (mvc::Model::hasChanged()) {
			mvc::Model::notifyAll();
			}
		} // End if hasChanged() == false
	return success;
};

// -----------------------------------------------------------
template <typename T>
void TNumParameter<T>::setDefaultValue() {
	const T & defaultValue = TParameter<T>::getDefaultValue();
	assignValue( defaultValue );
}

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getMinValue() {
	T minVal = m_MinValue;
	synchronized(m_Mutex) {
		if (m_pNumLimits != NULL)
			minVal = m_pNumLimits->getMinValue(this);
		} // End synchronized
	return minVal;
};

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getMaxValue() {
	T maxVal = m_MaxValue;
	synchronized(m_Mutex) {
		if (m_pNumLimits != NULL)
			maxVal = m_pNumLimits->getMaxValue(this);
		} // End synchronized
	return maxVal;
};

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getNextValue() {
	T nextVal;
	synchronized(m_Mutex) {
		nextVal = (mvc::TModel<T>::m_Value <= (getMaxValue() - m_Step))
				? (mvc::TModel<T>::m_Value + m_Step) : getMaxValue();
		} // End synchronized
	return nextVal;
};

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getNextValueRotated() {
	T nextVal;
	synchronized(m_Mutex) {
		nextVal = (mvc::TModel<T>::m_Value <= (getMaxValue() - m_Step))
				? (mvc::TModel<T>::m_Value + m_Step) : getMinValue();
		} // End synchronized
	return nextVal;
};

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getPrevValue() {
	T prevVal;
	synchronized(m_Mutex) {
		prevVal = (mvc::TModel<T>::m_Value >= (getMinValue() + m_Step))
				? (mvc::TModel<T>::m_Value - m_Step) : getMinValue();
		} // End synchronized
	return prevVal;
};

// -----------------------------------------------------------
template <typename T>
T TNumParameter<T>::getPrevValueRotated() {
	T prevVal;
	synchronized(m_Mutex) {
		prevVal = (mvc::TModel<T>::m_Value >= (getMinValue() + m_Step))
				? (mvc::TModel<T>::m_Value - m_Step) : getMaxValue();
		} // End synchronized
	return prevVal;
};

// -----------------------------------------------------------
template <typename T>
void TNumParameter<T>::setNumLimits(TNumLimits<T> * pNumLimits) {
	m_pNumLimits = pNumLimits;
}


// -----------------------------------------------------------
// Template class TVarArrayParameter<T>
// -----------------------------------------------------------
template <typename T>
TVarArrayParameter<T>::TVarArrayParameter(const std::string & name, const de::bswalz::var_array<T> & initValue)
	: TParameter<de::bswalz::var_array<T> >(name, initValue) {
	// Intentionally left blank
};

// -----------------------------------------------------------
template <typename T>
TVarArrayParameter<T>::TVarArrayParameter(const de::bswalz::var_array<T> & initValue)
	: TParameter<de::bswalz::var_array<T> >(std::string(__FILE__) + ":" + std::to_string(__LINE__), initValue) {
	// Intentionally left blank
};

// -----------------------------------------------------------
template <typename T>
TVarArrayParameter<T>::TVarArrayParameter()
	: TParameter<de::bswalz::var_array<T> >(std::string(__FILE__) + ":" + std::to_string(__LINE__), de::bswalz::var_array<T>()) { /* Intentionally left blank */ };

// -----------------------------------------------------------
template <typename T>
bool TVarArrayParameter<T>::assignValue(const de::bswalz::var_array<T> & value, const IAssignRule* pRule ) {
	bool success = true;
	if (!mvc::Model::hasChanged()) {
		synchronized(m_Mutex) {
			mvc::TModel<de::bswalz::var_array<T>>::m_CurrValue = mvc::TModel<de::bswalz::var_array<T>>::m_Value;
			mvc::TModel<de::bswalz::var_array<T>>::m_Value     = value;
			mvc::TModel<de::bswalz::var_array<T>>::applyAssignRules();
			if (pRule == nullptr && !mvc::TModel<var_array<T>>::validateAssignment()) {
				// Validation only on originally assigned parameter, not on assignment caused by AssignRule
				mvc::TModel<de::bswalz::var_array<T>>::revertAssignment();
				success = false;
				}
			if (mvc::TModel<de::bswalz::var_array<T>>::m_CurrValue != value) { // Notifies also if value has been limited
				mvc::TModel<de::bswalz::var_array<T>>::m_CurrValue = mvc::TModel<de::bswalz::var_array<T>>::m_Value;
				mvc::Model::setChanged();
				}
			} // End synchronized
		mvc::Model::notifyAll();
		} // End if hasChanged() == false
	return success;
};

// -----------------------------------------------------------
template <typename T>
void TVarArrayParameter<T>::assignElementValue(T value, unsigned int i) {
	mvc::TModel<de::bswalz::var_array<T> >::m_Value[i] = value;
};

// -----------------------------------------------------------
template <typename T>
T & TVarArrayParameter<T>::getElementValue(unsigned int i) const {
	return mvc::TModel<de::bswalz::var_array<T> >::m_Value[i];
};

// -----------------------------------------------------------
template <typename T>
T & TVarArrayParameter<T>::getElementDefaultValue(unsigned int i) const {
	return mvc::TModel<de::bswalz::var_array<T> >::m_DefaultValue[i];
};

// -----------------------------------------------------------
template <typename T>
bool TVarArrayParameter<T>::isElementDefaultValue(unsigned int i) const {
	return TParameter<de::bswalz::var_array<T> >::m_DefaultValue[i]
			 == mvc::TModel<de::bswalz::var_array<T> >::m_Value[i];
};

// -----------------------------------------------------------
template <typename T>
bool TVarArrayParameter<T>::isDefaultValue() const {
	return TParameter<de::bswalz::var_array<T> >::m_DefaultValue
			 == mvc::TModel<de::bswalz::var_array<T> >::m_Value;
};

// -----------------------------------------------------------
template <typename T>
unsigned int TVarArrayParameter<T>::getArraySize() const {
	return mvc::TModel<de::bswalz::var_array<T> >::m_Value.size();
};
