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
#ifndef _skTimedCallback_h_
#define _skTimedCallback_h_

#include "Threads/skCriticalSection.h"
#include "Threads/skSemaphore.h"
#include "Threads/skThread.h"
#include "Threads/skThreadUtils.h"

class skTimedCallback final : public skRunable
{
public:
    class Listener
    {
    public:
        virtual void tick() = 0;
    };

private:
    skCriticalSection m_criticalSection;
    SKint32           m_interrupt; 
    Listener*         m_listener;
    bool              m_running;

    int update() override;

public:
    skTimedCallback(Listener* listener, const SKint32& interrupt);
    ~skTimedCallback() override;

    void setInterval(const SKint32& interrupt);

    void begin();
    void end();
};

#endif  //_skTimedCallback
