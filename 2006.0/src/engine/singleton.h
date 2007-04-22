/***************************************************************************
 *   Copyright (C) 2005-2006 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
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
#ifndef SMARTOBJECTS_SINGLETONE_H
#define SMARTOBJECTS_SINGLETONE_H

#define SINGLEFRIEND(classname) friend class FIFE::Singleton<classname>; classname(); virtual ~classname(); \
				                        classname(const classname&); classname& operator=(const classname&);

namespace FIFE {

	template <typename T> class Singleton {
		public:

			static T* instance() {
				static T* inst = new T();
				return inst;
			}

		protected:

			Singleton() {
			}

			virtual ~Singleton() {
			}

		private:

	};

}//FIFE

#endif
