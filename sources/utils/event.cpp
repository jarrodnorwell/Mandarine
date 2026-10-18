#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/utils/event.h"

#else

#include "utils/event.h"

#endif // TARGET_OS_IPHONE

#else

#include "utils/event.h"

#endif // __APPLE__

auto bus = std::make_shared<dexode::EventBus>();
dexode::EventBus::Listener listener{bus};

void toast(const std::string &message)
{
    bus->postpone(Event::Gui::Toast{message});
    bus->process();
}
