/***************************************************************************
 *   Copyright (C) 2005-2007 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

// Standard C++ library includes

// 3rd party library includes
#include <boost/scoped_array.hpp>
#include <SDL.h>
#include <SDL_image.h>

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "vfs/raw/rawdata.h"
#include "vfs/vfs.h"
#include "video/image.h"
#include "video/renderbackend.h"
#include "util/debugutils.h"
#include "util/exception.h"

#include "image_provider.h"

namespace FIFE { namespace video { namespace loaders {
	
	RenderAble* ImageProvider::createRenderable() {

	const RenderableLocation & location = getLocation();
		const std::string& filename = location.getFilename();
		RawDataPtr data = VFS::instance()->open(filename);
		size_t datalen = data->getDataLength();
		boost::scoped_array<uint8_t> darray(new uint8_t[datalen]);
		data->readInto(darray.get(), datalen);
		SDL_RWops* rwops = SDL_RWFromConstMem(darray.get(), datalen);
		SDL_Surface* surface = IMG_Load_RW(rwops, false);
		SDL_FreeRW(rwops);
		if( !surface ) {
			return 0;
		}

		RenderAble * res = RenderBackend::instance()->createStaticImageFromSDL(surface);

		if (location.hasExtension(RenderableLocation::X))
			res->setXShift(boost::lexical_cast<int>(location.getExtension(RenderableLocation::X)));
		if (location.hasExtension(RenderableLocation::Y))
			res->setYShift(boost::lexical_cast<int>(location.getExtension(RenderableLocation::Y)));

		// FIXME: If Amask != 0 we should check if the alpha channel
		//        is actually used.
		
		return res;
	};
} } }