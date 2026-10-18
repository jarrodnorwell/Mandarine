#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/device/controller/peripherals/none.h"

#else

#include "device/controller/peripherals/none.h"

#endif // TARGET_OS_IPHONE

#else

#include "device/controller/peripherals/none.h"

#endif // __APPLE__

namespace peripherals {
None::None(int port) : AbstractDevice(Type::None, port) {}

uint8_t None::handle(uint8_t byte) {
    (void)byte;
    return 0xff;
}
};  // namespace peripherals
