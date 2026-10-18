#pragma once

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/disc/disc.h"

#else

#include "disc/disc.h"

#endif // TARGET_OS_IPHONE

#else

#include "disc/disc.h"

#endif // __APPLE__

#include <memory>
#include <string>

namespace disc {
bool isDiscImage(const std::string& path);
std::unique_ptr<disc::Disc> load(const std::string& path);
}  // namespace disc
