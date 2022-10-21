#ifndef _DE_BSWALZ_MODEL_NUMLIMITS_H_
#define _DE_BSWALZ_MODEL_NUMLIMITS_H_

namespace de { namespace bswalz { namespace model {

template <typename T> class TNumParameter;

/**
 * Dynamic numeric limits which can exceed the staticly defined min. and max. limits.
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
template <typename T> class TNumLimits {
public:
	TNumLimits() {};
	virtual ~TNumLimits() {};
	
	virtual T  getMinValue(TNumParameter<T> * pSource) = 0;
	virtual T  getMaxValue(TNumParameter<T> * pSource) = 0;
};

}}} // End namespaces

#endif /*NUMLIMITS_H_*/
