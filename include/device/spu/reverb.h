#pragma once

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/device/spu/spu.h"

#else

#include "device/spu/spu.h"

#endif // TARGET_OS_IPHONE

#else

#include "device/spu/spu.h"

#endif // __APPLE__

#include <tuple>

namespace spu {
std::tuple<int16_t, int16_t> doReverb(SPU* spu, std::tuple<int16_t, int16_t> input);
}  // namespace spu
