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
#ifndef _skThreadDefinitions_h_
#define _skThreadDefinitions_h_

#include "Utils/Config/skConfig.h"

#if SK_PLATFORM == SK_PLATFORM_WIN32
typedef SKuintPtr SKthreadObject;
typedef SKuintPtr SKmutexObject;
#else
typedef SKuintPtr SKthreadObject;
typedef SKuintPtr SKmutexObject;
#endif

#define SK_THREAD_NULL ((SKuintPtr)-1)
#define SK_THREAD_NO_ERROR 0

#ifdef DO_TRACES 
#define tracef(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define tracef(fmt, ...) \
    {                    \
    }
#endif


#endif  //_skThreadDefinitions_h_