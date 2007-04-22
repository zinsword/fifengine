/***************************************************************************
 *   Copyright (C) 2005-2006 by the FIFE Team                              *
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

#ifndef FIFEVFSHOSTSYSTEM_H
#define FIFEVFSHOSTSYSTEM_H

#include "vfssource.h"

namespace FIFE {

	/** The most basic VFSSource for the "normal" filesystem
	 *
	 * Uses boost_filesystem to achieve Plattform independancy.
	 * This also means you have to use slashes as directory
	 * separators.
	 */
	class VFSHostSystem : public VFSSource {
		public:
			/** Constructor
			 * Creates the Hosts system VFS Source, Uses boost_filesystem to
			 * achieve Plattform independancy.
			 */
			VFSHostSystem();
			/** Destructor
			 */
			virtual ~VFSHostSystem();

			/** Tests whether a file can be opened.
			 * @param filename The file to test.
			 * @return True, if the file filename can be opened.
			 */
			virtual bool fileExists(const std::string& filename) const;
			/** Opens a file.
			 * @param filename The file to open.
			 */
			virtual RawData* open(const std::string& filename) const;

			/** List files in a directory
			 * @param path The directory to list the files in
			 * @return A string list of filenames
			 * Will return an empty list on \b any error
			 */
			VFS::type_stringlist listFiles(const std::string& path) const;

			/** List directories in a directory
			 * @param path The directory to list the directories in
			 * @return A string list of directories
			 * Will return an empty list on \b any error
			 */
			VFS::type_stringlist listDirectories(const std::string& path) const;

		private:
			VFS::type_stringlist list(const std::string& path, bool directorys) const;

	};

}

#endif
