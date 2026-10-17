//
//  sound.h
//  Mandarine
//
//  Created by Jarrod Norwell on 17/10/2026.
//

#pragma once

#include "device/spu/spu.h"

#include <cstdint>
#include <deque>
#include <iterator>
#include <mutex>

namespace sound {
    extern std::deque<uint16_t> buffer;
    extern std::mutex mutex;

    template <typename Iterator>
    void append(const Iterator& start, const Iterator& end) {
        std::unique_lock<std::mutex> lock{sound::mutex};

        if (sound::buffer.size() > constants::sound::SIZE)
            sound::buffer.clear();

        sound::buffer.insert(sound::buffer.end(), start, end);
    }

    void clear(), close(), init(), play(), stop();
} // namespace sound