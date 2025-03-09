#ifndef __RMCORE_HPP__
#define __RMCORE_HPP__

#include "RM.hpp"
#include "RMCompute.hpp"
#include "RMDispatcher.hpp"
#include "RMTypes.hpp"

using namespace std;

static void RMCore(
#if RM_NUM_PE >= 1
  volatile RMMemPort_t* private_map_pe0, // Private Memory Port
#endif
#if RM_NUM_PE >= 2
  volatile RMMemPort_t* private_map_pe1, // Private Memory Port
#endif
#if RM_NUM_PE >= 4
  volatile RMMemPort_t* private_map_pe2, // Private Memory Port
  volatile RMMemPort_t* private_map_pe3, // Private Memory Port
#endif
#if RM_NUM_PE >= 8
  volatile RMMemPort_t* private_map_pe4, // Private Memory Port
  volatile RMMemPort_t* private_map_pe5, // Private Memory Port
  volatile RMMemPort_t* private_map_pe6, // Private Memory Port
  volatile RMMemPort_t* private_map_pe7, // Private Memory Port
#endif
#if RM_NUM_PE >= 16
  volatile RMMemPort_t* private_map_pe8,  // Private Memory Port
  volatile RMMemPort_t* private_map_pe9,  // Private Memory Port
  volatile RMMemPort_t* private_map_pe10, // Private Memory Port
  volatile RMMemPort_t* private_map_pe11, // Private Memory Port
  volatile RMMemPort_t* private_map_pe12, // Private Memory Port
  volatile RMMemPort_t* private_map_pe13, // Private Memory Port
  volatile RMMemPort_t* private_map_pe14, // Private Memory Port
  volatile RMMemPort_t* private_map_pe15, // Private Memory Port
#endif
#if RM_NUM_PE >= 32
  volatile RMMemPort_t* private_map_pe16, // Private Memory Port
  volatile RMMemPort_t* private_map_pe17, // Private Memory Port
  volatile RMMemPort_t* private_map_pe18, // Private Memory Port
  volatile RMMemPort_t* private_map_pe19, // Private Memory Port
  volatile RMMemPort_t* private_map_pe20, // Private Memory Port
  volatile RMMemPort_t* private_map_pe21, // Private Memory Port
  volatile RMMemPort_t* private_map_pe22, // Private Memory Port
  volatile RMMemPort_t* private_map_pe23, // Private Memory Port
  volatile RMMemPort_t* private_map_pe24, // Private Memory Port
  volatile RMMemPort_t* private_map_pe25, // Private Memory Port
  volatile RMMemPort_t* private_map_pe26, // Private Memory Port
  volatile RMMemPort_t* private_map_pe27, // Private Memory Port
  volatile RMMemPort_t* private_map_pe28, // Private Memory Port
  volatile RMMemPort_t* private_map_pe29, // Private Memory Port
  volatile RMMemPort_t* private_map_pe30, // Private Memory Port
  volatile RMMemPort_t* private_map_pe31, // Private Memory Port
#endif
  volatile float* x,
  volatile float* y,
  volatile float* yaw,
  volatile float* rays,
  const RMConfig_t config,
  RMHP_t* rays_angle)
{

    static hls::stream<RMParticle_t, 8> particle_queue;
    static hls::stream<RMHP_t, 64> rays_queue;

RMCore_particles_loop:
    for (RMIter_t p_idx = 0; p_idx < config.n_particles; ++p_idx) {
#pragma HLS DATAFLOW
#pragma HLS LOOP_TRIPCOUNT min = max_particles max = max_particles
        RMDispatcher(p_idx, x, y, yaw, particle_queue);

        RMComputeEngine(
#if RM_NUM_PE >= 1
          private_map_pe0,
#endif
#if RM_NUM_PE >= 2
          private_map_pe1,
#endif
#if RM_NUM_PE >= 4
          private_map_pe2,
          private_map_pe3,
#endif
#if RM_NUM_PE >= 8
          private_map_pe4,
          private_map_pe5,
          private_map_pe6,
          private_map_pe7,
#endif
#if RM_NUM_PE >= 16
          private_map_pe8,
          private_map_pe9,
          private_map_pe10,
          private_map_pe11,
          private_map_pe12,
          private_map_pe13,
          private_map_pe14,
          private_map_pe15,
#endif
#if RM_NUM_PE >= 32
          private_map_pe16,
          private_map_pe17,
          private_map_pe18,
          private_map_pe19,
          private_map_pe20,
          private_map_pe21,
          private_map_pe22,
          private_map_pe23,
          private_map_pe24,
          private_map_pe25,
          private_map_pe26,
          private_map_pe27,
          private_map_pe28,
          private_map_pe29,
          private_map_pe30,
          private_map_pe31,
#endif
          particle_queue,
          rays_queue,
          config,
          rays_angle);

        RMCollector(p_idx, rays_queue, rays);
    }
}
#endif // __RMCORE_HPP__
