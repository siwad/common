#ifndef _DE_BSWALZ_SYNC_SYNCHRONIZED_H_
#define _DE_BSWALZ_SYNC_SYNCHRONIZED_H_

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

#include <mutex>

namespace de { namespace bswalz { namespace sync {

   /**
    * The CMutex class presents a mutex with lock/unlock semantics
    * (common in many libraries).
    */
class CMutex : public std::recursive_mutex {
public:
	CMutex();
	virtual ~CMutex();
	void    lock();
	void    unlock();

    CMutex & operator=(const CMutex &);
};

    /**
     * Synchronisation controller
     */
class CLock {
public:
    CLock( CMutex & mutex);
    virtual  ~CLock();
    operator bool () const;
    void     setUnlock();
private:
    CMutex & m_Mutex;
    bool     m_Locked;
};

}}} // End namespaces

#define synchronized(M)  for(sync::CLock M##_Lock = M; M##_Lock; M##_Lock.setUnlock()) 


#endif /*_DE_BSWALZ_SYNC_SYNCHRONIZED_H_*/
