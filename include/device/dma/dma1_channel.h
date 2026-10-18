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

namespace mdec {
class MDEC;
};

namespace device::dma {
class DMA1Channel : public DMAChannel {
    mdec::MDEC* mdec;

    uint32_t readDevice() override;

   protected:
    bool dataRequest() override;
    bool hack_supportChoppedTransfer() const override;

   public:
    DMA1Channel(Channel channel, System* sys, mdec::MDEC* mdec);
};
}  // namespace device::dma
