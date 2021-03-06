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
     claim that you wrote the original software. If you use this softrdware
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _skPosixThread_h_
#define _skPosixThread_h_

#include "Threads/skMutex.h"
#include "Utils/Config/skConfig.h"

class skPosixThread
{
private:
    SKsize    m_id;
    pthread_t m_thread;
    
protected:
    skPosixThread();

    virtual ~skPosixThread();

    void waitImpl() const;

    void waitImpl(SKsize milliseconds)  const;

    void startImpl();

    void joinImpl();

public:

    virtual int update()
    {
        joinImpl();
        return 0;
    }
};

#endif  //_skPosixThread_h_
