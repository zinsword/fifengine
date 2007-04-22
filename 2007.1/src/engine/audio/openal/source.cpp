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

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "log.h"
#include "timemanager.h"

#include "manager.h"
#include "source.h"

namespace FIFE { namespace audio {
	Source::Source() : m_source(0), m_bufferp() { 
		TimeManager::instance()->registerEvent(this);
		setPeriod(-1);
		alGenSources(1, &m_source); 
	}
	
	Source::~Source() {
		setPeriod(-1);
		TimeManager::instance()->unregisterEvent(this);
	
		disable();
		
		// Release all buffers
		alSourcei(m_source, AL_BUFFER, AL_NONE);
		
		alDeleteSources(1, &m_source);
	}
	
	void Source::enable() {
		if (m_bufferp->isStreaming()) {
			Log("AudioSystem") << "Streaming is experimental for now.";

			setPeriod(5000);

			// Queuing the first buffers
			for (int i = 0; i < m_bufferp->countBuffers(); ++i) {
				ALuint buf = m_bufferp->acquireBuffer();
				alSourceQueueBuffers(m_source, 1, &buf);
			}

			if (AL_NO_ERROR != alGetError()) {
				Warn("AudioSystem") << "Couldn't queue buffers";
				return;
			}
		} else {
			alSourcei(m_source, AL_BUFFER, m_bufferp->acquireBuffer());
		}
		alSourcePlay(m_source); 
	}
	
	bool Source::loadFile(const std::string &name) {
		disable();
		m_bufferp = Manager::instance()->getBufferFromFile(name);
		return m_bufferp;	
	}
	
	void Source::updateEvent(unsigned long time) {
		ALint procs;
		alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &procs);
		if (procs > m_bufsdone) {
			ALuint buf = m_bufferp->releaseBuffer();
			ALuint buf2;
			alSourceUnqueueBuffers(m_source, 1, &buf2);
			m_bufferp->fillBuffer();
			buf = m_bufferp->acquireBuffer();
			alSourceQueueBuffers(m_source, 1, &buf);
			if (m_bufferp->isEOF()) {
				setPeriod(-1);
			}
		} else {
			m_bufsdone = procs;
		}
	}
} } //FIFE::audio
