#pragma once

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/device/dma/dma_channel.h"

#else

#include "device/dma/dma_channel.h"

#endif // TARGET_OS_IPHONE

#else

#include "device/dma/dma_channel.h"

#endif // __APPLE__

namespace device::dma {
class DMA5Channel : public DMAChannel {
   public:
    DMA5Channel(Channel channel, System* sys);
};
}  // namespace device::dma
