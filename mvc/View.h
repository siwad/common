#ifndef _DE_BSWALZ_MVC_VIEW_H_
#define _DE_BSWALZ_MVC_VIEW_H_

/**
 * View class of MVC pattern
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

#include <vector>

namespace de { namespace bswalz { namespace mvc {

class Model;

using de::bswalz::mvc::Model;

/**
 * The View class of the Model-View-Controller pattern.
 * @see http://de.wikipedia.org/wiki/Model_View_Controller
 */
class View {
public:
	View(Model * pModel = nullptr);
	View(const View &&);
	virtual ~View();
	
	/**
	 * Registers this view at the specified model
	 * @param pModel the model to be registered at
	 * @param initialUpdate if false suppresses update at registration
	 */
	void registerAt(Model * pModel, bool initialUpdate = false);
	
	/**
	 * Unregisters this view at the specified model
	 * @param pModel the model to be unregistered at
	 */
	void unregisterAt(Model * pModel);

	/**
	 * Receives an update notification of an associated model
	 * @param pModel the source model of this notification
	 * @param pObject an associated object (may be nullptr)
	 */
	virtual void update(const Model * pModel, void * pObject) = 0;

private:
	View(const View &);
	View & operator=(const View &);
	View & operator=(const View &&);

	std::vector<Model *> m_Models;
};

}}} // End namespaces

#endif /*_DE_BSWALZ_MVC_VIEW_H_*/
