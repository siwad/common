
/**
 * Model based event class of MVC pattern
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

#include "Event.h"

namespace de { namespace bswalz { namespace model {

// -------------------------------------------------------------------
CEvent::CEvent(std::string name, bool syncMode) 
   : Model(name) {
   setSyncMode(syncMode);
}

// -------------------------------------------------------------------
void CEvent::signal(void * pObject) {
   Model::setChanged();
   
   if (pObject)
	  // Forces sync mode
      Model::setSyncMode(true);
   
   Model::notifyAll(pObject);
}

}}} // End namespaces
