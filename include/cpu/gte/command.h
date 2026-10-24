#pragma once

#include <cstdint>

namespace gte {

    struct command {
        enum mvmva_tv : uint32_t {
            tr = 0,
            bk = 1,
            fc = 2,
            none = 3
        };

        enum mvmva_mv : uint32_t {
            v0 = 0,
            v1 = 1,
            v2 = 2,
            ir = 3
        };

        enum mvmva_mm : uint32_t {
            rotation = 0,
            light = 1,
            color = 2,
            reserved = 3
        };

        enum shift_fraction : uint32_t {
            no_fraction = 0,
            twelve_bit_fraction = 1
        };

        uint32_t real_gte_command_number : 6;
        uint32_t zero0 : 4;
        uint32_t lm : 1;
        uint32_t zero1 : 2;
        mvmva_tv mvmva_translation_vector : 2;
        mvmva_mv mvmva_multiply_vector : 2;
        mvmva_mm mvmva_multiply_matrix : 2;
        shift_fraction sf : 1;
        uint32_t fake_gte_command_number : 5;
        uint32_t cop2 : 7;
    };

}; //namespace gte