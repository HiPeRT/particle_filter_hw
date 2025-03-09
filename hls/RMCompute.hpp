#ifndef __RMCOMPUTE_HPP__
#define __RMCOMPUTE_HPP__

#include "RM.hpp"
#include "RMTypes.hpp"
#include <hls_math.h>

using namespace std;

static RMDist_t RMComputeRay(RMParticle_t particle, RMHP_t angle, const RMConfig_t config, volatile RMMemPort_t* map)
{
    if (angle > RMHP_t(1081 * RM_ANGLE_INCREMENT))
        return RMDist_t(0.0);

    angle += particle.yaw;
    RMHP_t r_cos = hls::cos(angle);
    RMHP_t r_sin = hls::sin(angle);
    RMHP_t rayPoseX = particle.x;
    RMHP_t rayPoseY = particle.y;
    RMHP_t distance = 0.0;
    RMDist_t dist_16bit;
    RMIter_t iter_cnt = 0;

    RMIter_t old_c;
    RMIter_t old_r;

RMComputeRay_rayIter_loop:
    for (RMIter_t k = 0; k < RM_MAX_ITER; ++k) {
#pragma HLS LOOP_TRIPCOUNT min = 1 max = max_iter
#pragma HLS PIPELINE
        RMHP_t d;
        RMIter_t c = (config.orig_x - rayPoseX) * 20; /*\map_resolution*/
        RMIter_t r = (config.orig_y + rayPoseY) * 20; /*\map_resolution*/

        if (c < 0 || c >= config.map_width || r < 0 || r >= config.map_height) {
            distance = RM_MAX_RANGE;
            break;
        }

        // if (k && c == old_c && r == old_r)
        //     break;

        // old_c = c;
        // old_r = r;

        RMDist2HP(map[r * config.map_width + c], d);
        if (d < config.map_resolution)
            break;

        distance += d;
        rayPoseX += d * r_cos;
        rayPoseY += d * r_sin;
        iter_cnt++;
    }

    if (iter_cnt > RM_MAX_ITER)
        distance = RM_MAX_RANGE;

    RMHP2Dist(distance, dist_16bit);

    return dist_16bit;
}

static void RMComputeEngine(
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
  hls::stream<RMParticle_t>& particle_queue,
  hls::stream<RMHP_t>& rays_queue,
  const RMConfig_t config,
  RMHP_t* rays_angle)
{
    RMDist_t ray[RM_NUM_PE];
    RMParticle_t particle[RM_NUM_PE];
#pragma HLS ARRAY_PARTITION variable = particle complete dim = 1
#pragma HLS ARRAY_PARTITION variable = ray complete dim = 1

    RMParticle_t p = particle_queue.read();

RMCompute_get_p_loop:
    for (RMIter_t pe_id = 0; pe_id < RM_NUM_PE; pe_id++) {
#if RM_NUM_PE > 1
#pragma HLS PIPELINE
#endif
        particle[pe_id] = p;
    }
RMCompute_rays_loop:
    for (RMIter_t j = 0; j < RM_N_REAL_RAYS; j += RM_NUM_PE) {
    RMCompute_compute_loop:
        for (RMIter_t pe_id = 0; pe_id < RM_NUM_PE; pe_id++) {
#if RM_NUM_PE > 1
#pragma HLS UNROLL
#endif
#if RM_NUM_PE >= 1
            if (pe_id == 0)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe0);
#endif
#if RM_NUM_PE >= 2
            else if (pe_id == 1)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe1);
#endif
#if RM_NUM_PE >= 4
            else if (pe_id == 2)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe2);
            else if (pe_id == 3)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe3);
#endif
#if RM_NUM_PE >= 8
            else if (pe_id == 4)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe4);
            else if (pe_id == 5)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe5);
            else if (pe_id == 6)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe6);
            else if (pe_id == 7)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe7);
#endif
#if RM_NUM_PE >= 16
            else if (pe_id == 8)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe8);
            else if (pe_id == 9)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe9);
            else if (pe_id == 10)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe10);
            else if (pe_id == 11)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe11);
            else if (pe_id == 12)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe12);
            else if (pe_id == 13)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe13);
            else if (pe_id == 14)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe14);
            else if (pe_id == 15)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe15);
#endif
#if RM_NUM_PE >= 32
            else if (pe_id == 16)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe16);
            else if (pe_id == 17)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe17);
            else if (pe_id == 18)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe18);
            else if (pe_id == 19)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe19);
            else if (pe_id == 20)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe20);
            else if (pe_id == 21)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe21);
            else if (pe_id == 22)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe22);
            else if (pe_id == 23)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe23);
            else if (pe_id == 24)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe24);
            else if (pe_id == 25)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe25);
            else if (pe_id == 26)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe26);
            else if (pe_id == 27)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe27);
            else if (pe_id == 28)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe28);
            else if (pe_id == 29)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe29);
            else if (pe_id == 30)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe30);
            else if (pe_id == 31)
                ray[pe_id] = RMComputeRay(particle[pe_id], rays_angle[j + pe_id], config, private_map_pe31);
#endif
        }
    RMCompute_store_loop:
        for (RMIter_t pe_id = 0; pe_id < RM_NUM_PE; pe_id++) {
#if RM_NUM_PE > 1
#pragma HLS PIPELINE
#endif
            if ((j + pe_id) < RM_N_REAL_RAYS) {
                while (rays_queue.full())
                    ;
                rays_queue << ray[pe_id];
            }
        }
    }
}
#endif // __RMCOMPUTE_HPP__
