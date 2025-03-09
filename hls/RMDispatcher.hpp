#ifndef __RMDISPATCHER_HPP__
#define __RMDISPATCHER_HPP__

#include <stdint.h>
#include <hls_stream.h>

#include "RM.hpp"
#include "RMTypes.hpp"

static void RMDispatcher(RMIter_t particle_idx, volatile float *x, volatile float *y, volatile float *yaw,
                         hls::stream<RMParticle_t> &particle_queue)
{
    RMParticle_t p = {RMHP_t(x[particle_idx]), RMHP_t(y[particle_idx]), RMHP_t(yaw[particle_idx]) + RMHP_t(RM_ANGLE_MIN)};

    while (particle_queue.full())
        ;
    particle_queue << p;
}

static void RMCollector(RMIter_t particle_idx, hls::stream<RMHP_t> &rays_queue,
                        volatile float *rays)
{
RMCollector_loop:
    for (RMIter_t j = 0; j < RM_N_REAL_RAYS; ++j)
    {
#pragma HLS PIPELINE
    	RMHP_t r = rays_queue.read();
        rays[particle_idx * RM_N_REAL_RAYS + j] = r.to_float();
    }
}
#endif // __RMDISPATCHER_HPP__
