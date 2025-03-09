#include <cassert>

#include "RM.hpp"
#include "RMCore.hpp"
#include "RMMapLoader.hpp"
#include "RMTypes.hpp"

using namespace std;

extern "C"
{
    // RM Top Interface
    void RM(
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
      volatile float* distMap,
      volatile float* x,
      volatile float* y,
      volatile float* yaw,
      volatile float* rays,
      volatile float* rays_angle,
      RMMode rm_mode,
      int map_height,
      int map_width,
      int n_particles,
      float orig_x,
      float orig_y,
      float map_resolution)
    {
#pragma HLS INTERFACE m_axi port = distMap depth = depthDistMap offset = slave bundle = ddr_port0
#pragma HLS INTERFACE m_axi port = x depth = depthParticles offset = slave bundle = ddr_port0
#pragma HLS INTERFACE m_axi port = y depth = depthParticles offset = slave bundle = ddr_port1
#pragma HLS INTERFACE m_axi port = yaw depth = depthParticles offset = slave bundle = ddr_port2
#pragma HLS INTERFACE m_axi port = rays depth = depthRays offset = slave bundle = ddr_port0
#pragma HLS INTERFACE m_axi port = rays_angle depth = depthRaysAngle offset = slave bundle = ddr_port0

#if RM_NUM_PE >= 1
#pragma HLS INTERFACE m_axi port = private_map_pe0 depth = depthDistMap offset = slave bundle = private_port0
#endif
#if RM_NUM_PE >= 2
#pragma HLS INTERFACE m_axi port = private_map_pe1 depth = depthDistMap offset = slave bundle = private_port1
#endif
#if RM_NUM_PE >= 4
#pragma HLS INTERFACE m_axi port = private_map_pe2 depth = depthDistMap offset = slave bundle = private_port2
#pragma HLS INTERFACE m_axi port = private_map_pe3 depth = depthDistMap offset = slave bundle = private_port3
#endif
#if RM_NUM_PE >= 8
#pragma HLS INTERFACE m_axi port = private_map_pe4 depth = depthDistMap offset = slave bundle = private_port4
#pragma HLS INTERFACE m_axi port = private_map_pe5 depth = depthDistMap offset = slave bundle = private_port5
#pragma HLS INTERFACE m_axi port = private_map_pe6 depth = depthDistMap offset = slave bundle = private_port6
#pragma HLS INTERFACE m_axi port = private_map_pe7 depth = depthDistMap offset = slave bundle = private_port7
#endif
#if RM_NUM_PE >= 16
#pragma HLS INTERFACE m_axi port = private_map_pe8 depth = depthDistMap offset = slave bundle = private_port8
#pragma HLS INTERFACE m_axi port = private_map_pe9 depth = depthDistMap offset = slave bundle = private_port9
#pragma HLS INTERFACE m_axi port = private_map_pe10 depth = depthDistMap offset = slave bundle = private_port10
#pragma HLS INTERFACE m_axi port = private_map_pe11 depth = depthDistMap offset = slave bundle = private_port11
#pragma HLS INTERFACE m_axi port = private_map_pe12 depth = depthDistMap offset = slave bundle = private_port12
#pragma HLS INTERFACE m_axi port = private_map_pe13 depth = depthDistMap offset = slave bundle = private_port13
#pragma HLS INTERFACE m_axi port = private_map_pe14 depth = depthDistMap offset = slave bundle = private_port14
#pragma HLS INTERFACE m_axi port = private_map_pe15 depth = depthDistMap offset = slave bundle = private_port15
#endif
#if RM_NUM_PE >= 32
#pragma HLS INTERFACE m_axi port = private_map_pe16 depth = depthDistMap offset = slave bundle = private_port16
#pragma HLS INTERFACE m_axi port = private_map_pe17 depth = depthDistMap offset = slave bundle = private_port17
#pragma HLS INTERFACE m_axi port = private_map_pe18 depth = depthDistMap offset = slave bundle = private_port18
#pragma HLS INTERFACE m_axi port = private_map_pe19 depth = depthDistMap offset = slave bundle = private_port19
#pragma HLS INTERFACE m_axi port = private_map_pe20 depth = depthDistMap offset = slave bundle = private_port20
#pragma HLS INTERFACE m_axi port = private_map_pe21 depth = depthDistMap offset = slave bundle = private_port21
#pragma HLS INTERFACE m_axi port = private_map_pe22 depth = depthDistMap offset = slave bundle = private_port22
#pragma HLS INTERFACE m_axi port = private_map_pe23 depth = depthDistMap offset = slave bundle = private_port23
#pragma HLS INTERFACE m_axi port = private_map_pe24 depth = depthDistMap offset = slave bundle = private_port24
#pragma HLS INTERFACE m_axi port = private_map_pe25 depth = depthDistMap offset = slave bundle = private_port25
#pragma HLS INTERFACE m_axi port = private_map_pe26 depth = depthDistMap offset = slave bundle = private_port26
#pragma HLS INTERFACE m_axi port = private_map_pe27 depth = depthDistMap offset = slave bundle = private_port27
#pragma HLS INTERFACE m_axi port = private_map_pe28 depth = depthDistMap offset = slave bundle = private_port28
#pragma HLS INTERFACE m_axi port = private_map_pe29 depth = depthDistMap offset = slave bundle = private_port29
#pragma HLS INTERFACE m_axi port = private_map_pe30 depth = depthDistMap offset = slave bundle = private_port30
#pragma HLS INTERFACE m_axi port = private_map_pe31 depth = depthDistMap offset = slave bundle = private_port31
#endif

#if RM_NUM_PE >= 1
#pragma HLS INTERFACE s_axilite port = private_map_pe0 bundle = control
#endif
#if RM_NUM_PE >= 2
#pragma HLS INTERFACE s_axilite port = private_map_pe1 bundle = control
#endif
#if RM_NUM_PE >= 4
#pragma HLS INTERFACE s_axilite port = private_map_pe2 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe3 bundle = control
#endif
#if RM_NUM_PE >= 8
#pragma HLS INTERFACE s_axilite port = private_map_pe4 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe5 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe6 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe7 bundle = control
#endif
#if RM_NUM_PE >= 16
#pragma HLS INTERFACE s_axilite port = private_map_pe8 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe9 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe10 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe11 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe12 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe13 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe14 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe15 bundle = control
#endif
#if RM_NUM_PE >= 32
#pragma HLS INTERFACE s_axilite port = private_map_pe16 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe17 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe18 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe19 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe20 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe21 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe22 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe23 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe24 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe25 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe26 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe27 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe28 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe29 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe30 bundle = control
#pragma HLS INTERFACE s_axilite port = private_map_pe31 bundle = control
#endif

#pragma HLS INTERFACE s_axilite port = distMap bundle = control
#pragma HLS INTERFACE s_axilite port = x bundle = control
#pragma HLS INTERFACE s_axilite port = y bundle = control
#pragma HLS INTERFACE s_axilite port = yaw bundle = control
#pragma HLS INTERFACE s_axilite port = rays bundle = control
#pragma HLS INTERFACE s_axilite port = rays_angle bundle = control

#pragma HLS INTERFACE s_axilite port = rm_mode bundle = control
#pragma HLS INTERFACE s_axilite port = n_particles bundle = control
#pragma HLS INTERFACE s_axilite port = orig_x bundle = control
#pragma HLS INTERFACE s_axilite port = orig_y bundle = control
#pragma HLS INTERFACE s_axilite port = map_resolution bundle = control
#pragma HLS INTERFACE s_axilite port = map_height bundle = control
#pragma HLS INTERFACE s_axilite port = map_width bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

        assert(map_height <= RM_MAX_HEIGHT);
        assert(map_width <= RM_MAX_WIDTH);
        assert(n_particles <= RM_MAX_PARTICLES);
        assert(RM_N_REAL_RAYS == (RM_N_RAYS / RM_ANGLE_STEP + (RM_N_RAYS % RM_ANGLE_STEP != 0)));

        const RMConfig_t config = { (RMIter_t)map_height, (RMIter_t)map_width, (RMIter_t)n_particles, orig_x, orig_y,
                                    map_resolution };
        RMHP_t local_r_angles[RM_N_REAL_RAYS];
#pragma HLS ARRAY_PARTITION variable = local_r_angles type = complete

        if (rm_mode == RM_MAP_LOAD) {
            RMMapLoader(distMap, map_height, map_width, private_map_pe0);
        } else {
            for (RMIter_t i = 0; i < RM_N_REAL_RAYS; i++) {
#pragma HLS PIPELINE
                local_r_angles[i] = RMHP_t(rays_angle[i]);
            }

            RMCore(
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
              x,
              y,
              yaw,
              rays,
              config,
              local_r_angles);
        }
    }
}
