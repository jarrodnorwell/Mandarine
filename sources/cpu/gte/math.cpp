#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/cpu/gte/math.h"

#else

#include "cpu/gte/math.h"

#endif // TARGET_OS_IPHONE

#else

#include "cpu/gte/math.h"

#endif // __APPLE__

namespace gte {
Vector<int16_t> toVector(int16_t ir[4]) { return Vector<int16_t>(ir[1], ir[2], ir[3]); }
};  // namespace gte
