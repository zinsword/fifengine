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

#ifndef FIFE_RESOURCE_LOCATION_H
#define FIFE_RESOURCE_LOCATION_H

// Standard C++ library includes

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder

namespace FIFE {

	/** Contains information about the Location of a Resource
	 *
	 *  This class is used to give ResoureProvider the information
	 *  where to find the data. 
	 */
	class ResourceLocation {
	public:

		// LIFECYCLE
		/** Default constructor.
		 */
		ResourceLocation(const std::string& filename): m_filename(filename) {}

		/** Destructor.
		 */
		virtual ~ResourceLocation() {};

		/** Returns the filename.
		 * @return The filename.
		 */
		std::string getFilename() const { return m_filename; };

		/** Compares two ResourceLocations for equality.
		 */
		virtual bool operator ==(const ResourceLocation& loc) const {
			if (m_filename.length() != loc.m_filename.length()) {
				return false;
			}
			if (!std::equal(m_filename.rbegin(), m_filename.rend(), loc.m_filename.rbegin())) {
				return false;
			}
			return true;
		}

		/** Compares two ResourceLocations
		 *  This is needed as the locations should be stored in a \c std::map
		 */
		virtual bool operator <(const ResourceLocation& loc) const {
			if (m_filename < loc.m_filename) {
				return true;
			}
			if (m_filename != loc.m_filename) {
				return false;
			}
			return true;
		}

		/** Creates copy of this location
		 *  All derived classes must implement this and return their corresponding instance
		 */
		virtual ResourceLocation* clone() const {
			return new ResourceLocation(m_filename);
		}

	private:
		std::string m_filename;
	};
} //FIFE

#endif