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
class DMA6Channel : public DMAChannel {
    void maskControl() override;
    void burstTransfer() override;

   public:
    DMA6Channel(Channel channel, System* sys);
};
}  // namespace device::dma
