#pragma once

#if __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#include "avocado/device/gpu/gpu.h"

#else

#include "device/gpu/gpu.h"

#endif // TARGET_OS_IPHONE

#else

#include "device/gpu/gpu.h"

#endif // __APPLE__

class Render {
   public:
    static void drawLine(gpu::GPU* gpu, const primitive::Line& line);
    static void drawTriangle(gpu::GPU* gpu, const primitive::Triangle& triangle);
    static void drawRectangle(gpu::GPU* gpu, const primitive::Rect& rect);
};
