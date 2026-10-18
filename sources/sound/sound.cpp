//
//  sound.cpp
//  Mandarine
//
//  Created by Jarrod Norwell on 17/10/2026.
//

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/constants.h"
#include "avocado/sound/sound.h"

#else

#include "avocado/constants.h"
#include "sound/sound.h"

#endif // TARGET_OS_IPHONE

#else

#include "constants.h"
#include "sound/sound.h"

#endif // __APPLE__

namespace sound {
    std::deque<uint16_t> buffer;
    std::mutex mutex;
};


void sound::clear() {

}

void sound::close() {
    
}

void sound::init() {
    
}

void sound::play() {
    
}

void sound::stop() {
    
}