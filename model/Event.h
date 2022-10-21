#ifndef EVENT_H_
#define EVENT_H_

#include "../mvc/Model.h"

namespace de { namespace bswalz { namespace model {

/**
 * Model based event class and template of MVC pattern
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


/**
 * The event class of the Model-View-Controller pattern.<br>
 * Intended to dipatch events through the system. By default all events
 * a synchronous events.  
 */
class CEvent : public mvc::Model {
public:
	CEvent(std::string name, bool syncMode = true);
	virtual ~CEvent() {};
    
    /**
     * Sends a signal. All registered listeners will receive
     * a notification 
     */
    void    signal(void * pObject = NULL);
};

/**
 * The typed event class of the Model-View-Controller pattern.<br>
 * Intended to dipatch events through the system. By default all events
 * a synchronous events.  
 */
template <typename T>
class TEvent : public mvc::Model {
public:
	TEvent(std::string name);
	virtual ~TEvent() {};
    
    /**
     * Sends a signal with an attached object . All registered listeners will receive
     * a notification 
     */
    void    signal(T * pObject = NULL);
};


// -------------------------------------------------------------------
template <typename T>
TEvent<T>::TEvent(std::string name) 
   : Model(name) {
   setSyncMode(true);
}

// -------------------------------------------------------------------
template <typename T>
void TEvent<T>::signal(T * pObject) {
   Model::setChanged();
   Model::notifyAll(pObject);
}


}}} // End namespaces

#endif /*EVENT_H_*/
