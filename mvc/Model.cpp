
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

#include "Model.h"
#include "View.h"
#include "../sync/Synchronized.h"

#if defined(WIN32) || defined(__WIN32__)
#include <process.h>
#else
#include <unistd.h>
#endif

namespace de { namespace bswalz { namespace mvc {

struct NotificationObject { Model * m_pModel; void * m_pObject; };


// -------------------------------------------------------
// Class mvc::Model
// -------------------------------------------------------
Model::Model(const std::string & name)
	: m_Name(name), m_Changed(false), m_SyncMode(true)
{ /* Intentionally left blank */ }

// -------------------------------------------------------
Model::~Model() {
	m_RegisteredViews.clear();
}

// -------------------------------------------------------
void Model::registerView(View * pView, bool initialUpdate /* = false */) {
	synchronized(m_Mutex) {
		m_RegisteredViews.insert(pView);
		}
	if (initialUpdate)
		pView->update(this, nullptr);
}

// -------------------------------------------------------
void Model::unregisterView(View * pView) {
	synchronized(m_Mutex) {
		for (auto pRegisteredView : m_RegisteredViews) {
			if ((pRegisteredView) == pView) {
			   m_RegisteredViews.erase(pRegisteredView);
			   break;
			   }
			}
	}
}

// -------------------------------------------------------
void Model::notifyAll(void * pObject) {
	if (m_Changed) {
		NotificationObject * pObj = new NotificationObject();
		pObj->m_pModel            = this;
		pObj->m_pObject           = pObject;
   	  
		if (!m_SyncMode) {
#if defined(WIN32) || defined(__WIN32__)
			::_beginthread(&mvc::Model::_notifyAll, 0, pArgs);
#else
			// ToDo: implement for UX/Android etc. on the base of pthread
#endif
			// delete the pObj is part of _notifyAll !!
			}
	else {
		for (auto pView : m_RegisteredViews) {
			pView->update(this, pObject);
            } // End for
		delete pObj;
		}
   	
	m_Changed = false;
	}
}

// -------------------------------------------------------
// _notifyAll(..) runs in separate thread !
void Model::_notifyAll(void * pObj) {
	NotificationObject * pNO = (NotificationObject *)pObj;
	for (auto pView : pNO->m_pModel->m_RegisteredViews) {
		pView->update(pNO->m_pModel, pNO->m_pObject);
		}
	delete pNO;
#if defined(WIN32) || defined(__WIN32__)
	::_endthread();
#else
	// ToDo: implement for UX/Android etc. on the base of pthread
#endif
}

// -------------------------------------------------------
void Model::setSyncMode(bool syncMode) {
	m_SyncMode = syncMode;
}

// -------------------------------------------------------
// Class mvc::Model::UpdateManager
// -------------------------------------------------------
std::unique_ptr<Model::UpdateManager> Model::UpdateManager::m_upInstance = std::unique_ptr<Model::UpdateManager>();
sync::CMutex                          Model::UpdateManager::m_Mutex      = sync::CMutex();

// -------------------------------------------------------
Model::UpdateManager * Model::UpdateManager::getInstance() {
	if (Model::UpdateManager::m_upInstance.get() == nullptr)
		Model::UpdateManager::m_upInstance.reset(new Model::UpdateManager());
	return Model::UpdateManager::m_upInstance.get();
}

// -------------------------------------------------------
Model::UpdateManager::UpdateManager() 
	: m_Notifications(), m_Started(false) { /* Intentionally left blank */ }

// -------------------------------------------------------
void Model::UpdateManager::addUpdateNotification(NotificationObject * pNO) {
	synchronized (m_Mutex) {
		m_Notifications.push_back(pNO);
	}; // End synchronized
	start();
} 

// -------------------------------------------------------
void Model::UpdateManager::start() {
	if (!m_Started) {
		m_Started = true;
#if defined(WIN32) || defined(__WIN32__)
		::_beginthread(&mvc::Model::UpdateManager::run, 0, nullptr);
#else
		// ToDo: implement for UX/Android etc.
#endif
	}
}

// -------------------------------------------------------
// run() runs in separate thread.
void Model::UpdateManager::run(void * pObject) {
	Model::UpdateManager * pMgr = Model::UpdateManager::getInstance();
#if defined(WIN32) || defined(__WIN32__)
	::Sleep(200);	// Suspends the current thread for 200 ms.
					// In the meantime it's possible to add update notifications.
#else
	usleep(2000000); // Suspends the current thread for 200 ms.
					 // In the meantime it's possible to add update notifications.
#endif

	synchronized (m_Mutex) {
	for (unsigned int i = 0; i < pMgr->m_Notifications.size(); i++) {
		// Notifies all registered listeners of the specified model
		NotificationObject * pNO = pMgr->m_Notifications[i];
		for (auto pView : pNO->m_pModel->m_RegisteredViews) {
			pView->update(pNO->m_pModel, pNO->m_pObject);
			} // End for
		delete pNO;
		} // End for
	pMgr->m_Notifications.clear();
	}; // End synchronized

	pMgr->m_Started = false;
#if defined(WIN32) || defined(__WIN32__)
	::_endthread();
#else
	// ToDo: implement for UX/Android etc.
#endif
}


}}} // End namespaces
