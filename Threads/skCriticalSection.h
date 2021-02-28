/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _skCriticalSection_h_
#define _skCriticalSection_h_

#include "Threads/skThreadUtils.h"

#if SK_PLATFORM == SK_PLATFORM_WIN32
# include "Windows/skWindowsCriticalSection.h"
#define skPlatformCriticalSection skWindowsCriticalSection
#else
#include "Posix/skPosixCriticalSection.h"
#define skPlatformCriticalSection skPosixCriticalSection
#endif



class skCriticalSection : protected skPlatformCriticalSection
{
public:
    skCriticalSection()
    {
    }

    ~skCriticalSection() override
    {
    }

    void lock(void)
    {
        lockImpl();
    }

    void unlock(void)
    {
        unlockImpl();
    }
};

class skCriticalSectionLock
{
private:
    skCriticalSection* m_crit;

public:
    skCriticalSectionLock(skCriticalSection* crit) :
        m_crit(crit)
    {
        if (m_crit)
            m_crit->lock();
    }

    ~skCriticalSectionLock()
    {
        if (m_crit)
            m_crit->unlock();
    }
};


#define SK_SCOPE_LOCK_CRITICAL_SECTION(crit) \
    skCriticalSectionLock ____scope__lock__(crit)

#endif  //_skCriticalSection_h_
