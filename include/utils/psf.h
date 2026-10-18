#pragma once

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/system.h"

#else

#include "system.h"

#endif // TARGET_OS_IPHONE

#else

#include "system.h"

#endif // __APPLE__

enum class PsfType { Main, MainLib, SecondaryLib };

bool loadPsf(System* sys, const std::string& file, PsfType type = PsfType::Main);
