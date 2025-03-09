#ifndef __RMMAPLOADER_HPP__
#define __RMMAPLOADER_HPP__

#include "RM.hpp"
#include "RMTypes.hpp"

static void RMMapLoader(volatile float* distMap,
                        RMIter_t height,
                        RMIter_t width,
                        volatile RMMemPort_t* private_map_pe0 // Private Memory Port

)
{
RMMapLoader_i:
    for (RMIter_t i = 0; i < height; i++) {
#pragma HLS LOOP_TRIPCOUNT min = max_height max = max_height
    RMMapLoader_j:
        for (RMIter_t j = 0; j < width; j++) {
#pragma HLS LOOP_TRIPCOUNT min = max_width max = max_width
#pragma HLS PIPELINE
            private_map_pe0[i * width + j] = RMDist_t(distMap[i * width + j]).range();
        }
    }
}
#endif // __RMMAPLOADER_HPP__
