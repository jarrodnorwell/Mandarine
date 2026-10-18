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


namespace gte {
union Command {
    struct {
        uint32_t cmd : 6;
        uint32_t : 4;
        uint32_t lm : 1;
        uint32_t : 2;
        uint32_t mvmvaTranslationVector : 2;  // 0 - tr, 1 - bk, 2 - fc, 3 - none
        uint32_t mvmvaMultiplyVector : 2;     // 0 - v0, 1 - v1, 2 - v2, 3 - ir
        uint32_t mvmvaMultiplyMatrix : 2;     // 0 - rotation, 1 - light, 2 - color, 3 - reserved
        uint32_t sf : 1;
        uint32_t : 5;
        uint32_t : 7;  // cop2
    };

    uint32_t _reg;
    Command(uint32_t v) : _reg(v) {}
};
};
