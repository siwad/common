
/**
 * Sync class for usage as Java-like synchronized(M)
 *
 * @copyright	2005 Siegfried Walz
 * @license     https://www.gnu.org/licenses/lgpl-3.0.txt GNU Lesser General Public License
 * @author      Siegfried Walz 
 * @link        https://software.bswalz.de/
 * @package     common/mvc
 */
/*
 * This file is part of common/sync
 *
 * common/sync is free software: you can redistribute it and/or modify
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

#include "Synchronized.h"

namespace de { namespace bswalz { namespace sync {

CMutex::CMutex() : std::recursive_mutex() {
	// Intentionally left blank
}

CMutex::~CMutex() {
	// Intentionally left blank
}

void CMutex::lock() {
	std::recursive_mutex::lock();
}


void CMutex::unlock() {
	std::recursive_mutex::unlock();
}

CLocker::CLocker(CMutex & mutex)
   : m_Mutex(mutex), m_Locked(true) {
	m_Mutex.lock();
}
   
CLocker::~CLocker() {
   m_Mutex.unlock();
}

CLocker::operator bool() const {
   return m_Locked;
}

void CLocker::setUnlock() {
   m_Locked = false;
}

}}} // End namespaces
