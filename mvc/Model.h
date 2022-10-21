#ifndef _DE_BSWALZ_MVC_MODEL_H_
#define _DE_BSWALZ_MVC_MODEL_H_

/**
 * Model class of MVC pattern
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

#include "Rules.h"
#include "../sync/Synchronized.h"
#include <string>
#include <vector>
#include <memory>
#include <set>

namespace de { namespace bswalz { namespace mvc {

class  View;
struct NotificationObject;

/**
 * The general Model class of the Model-View-Controller pattern.
 * @see http://de.wikipedia.org/wiki/Model_View_Controller
 */
class Model {

friend class View;

public:
	Model(const std::string & name);
	Model(const std::string & name, bool syncMode);
	virtual ~Model();
	 
	/**
	 * @return the model's name
	 */
	const std::string & getName() const { return m_Name; };
	
	/**
	 * Sets the 'synchronized mode' for notifications.<br>
	 * If non-synchronized mode is set, all update notifications will run in an extra thread.<br>
	 * The default value is 'true'.
	 */
	void setSyncMode(bool syncMode);
	
	/**
	 * @return the model's mutex
	 */
	sync::CMutex & getMutex() { return m_Mutex; }

protected:
    /**
	 * Registers a subsequent view to the list of already existing views.
	 * @param pView the subsequent view
	 * @param initialUpdate if false suppresses update notification at registration
     */
	void registerView(mvc::View * pView, bool initialUpdate = false);
    
    /**
	 * Unregisters a view from the list of registered views
     * @param pView the view to be unregistered
     */
    void unregisterView(mvc::View * pView);

protected:
	Model() {}	

    /**
	 * Indicates the model as 'changed'
     */
    void setChanged() { m_Changed = true; };

    /**
	 * @return true if model has changed.
     */
    bool hasChanged() { return m_Changed; };
    
    /**
	 * Notifies all registered views.
	 * @see setSyncMode(bool)
	 * @param pObject an associated object
     */
	void notifyAll(void * pObject = nullptr);

    sync::CMutex           m_Mutex;
	
private:
    std::string            m_Name;
    bool                   m_Changed;
    bool                   m_SyncMode;
    std::set<mvc::View *>  m_RegisteredViews;
#if defined(WIN32) || defined(__WIN32__)
	static  void __cdecl   _notifyAll(void *);
#else
	static  void           _notifyAll(void *);
#endif

private:
    /* 
	 * Nested class UpdateManager which handles update notifications in non-synchronized mode
     */
    class UpdateManager {
    public:
       static UpdateManager * getInstance();
	   void        addUpdateNotification(NotificationObject *);
       virtual     ~UpdateManager() {};
    private:
       UpdateManager();
       void        start();
       static void run(void *);
	   static std::unique_ptr<Model::UpdateManager> m_upInstance;
	   std::vector<NotificationObject *>  m_Notifications;
       bool                             m_Started;
       static sync::CMutex              m_Mutex;
    }; // End of nested class Model::UpdateManager    
    
}; // End of class Model


/**
 * The parametrized Model class of the Model-View-Controller pattern.
 */
template <typename T> class TModel : public Model {
public:
	TModel(std::string name, T value);
	virtual ~TModel();
	
	/**
	 * Assigns a value to the model
	 * @param value the new value
	 * @param pRule the instance of assign rule
	 * @return true if the assignment has been successfully performed
	 */
	virtual bool assignValue(const T & value, const IAssignRule* pRule = nullptr);

	/**
	 * Reverts a previous assignment of a value
	 */
	virtual void revertAssignment();

	/**
	 * Validates the assignment using the Voters and AssignRules
	 */
	virtual bool validateAssignment();

	/**
	 * @return the currently assigned value to this model
	 */
	virtual T &  getValue();
    
	/**
	 * Adds an AssignRule to the list of rules of this model
	 * @param pRule the new rule
	 * @param initialAppl if true applies the assign rule initially
	 */
	void addAssignRule(TAssignRule<T> * pRule, bool initialAppl = false);

	/**
	 * Sets a voter for this model
	 * @param pVoter the new voter
	 */
	void setVoter(std::shared_ptr<TVoter<T>> spVoter);
	/** Access to voter */
	std::shared_ptr<TVoter<T>> getVoter() const { return m_spVoter; }

protected:	
	TModel() : Model() {}

	virtual void applyAssignRules();
	
    T                             m_Value;
	T							  m_CurrValue;
    std::vector<TAssignRule<T> *> m_pAssignRules;
	std::shared_ptr<TVoter<T>>	  m_spVoter;
}; // End of template <class T> Model
   
}}} // End of namespaces

#include "Model.inl"

#endif /*_DE_BSWALZ_MVC_MODEL_H_*/
