#ifndef __RM_HPP__
#define __RM_HPP__

#include "RMTypes.hpp"

#define RM_MAX_ITER (80)
#define RM_MAX_WIDTH (485)
#define RM_MAX_HEIGHT (379)
#define RM_ANGLE_STEP (18)
//#define RM_ANGLE_INCREMENT (0.07846716156034346f)
#define RM_ANGLE_INCREMENT (4.35928675336234e-3f)
#define RM_N_RAYS (1080)
#define RM_N_REAL_RAYS (60) // -> ceil(RM_N_RAYS/RM_ANGLE_STEP)
#define RM_ANGLE_MIN (-2.35619449615f)
#define RM_MAX_RANGE (11.5f)
#define RM_MAX_PARTICLES (2000)

// Number of Processing Elements
// Supported: 1, 2, 4, 8, 16, 32
#define RM_NUM_PE (32)

const int max_iter = RM_MAX_ITER;
const int max_width = RM_MAX_WIDTH;
const int max_height = RM_MAX_HEIGHT;
const int n_rays = RM_N_RAYS;
const int angleStep = RM_ANGLE_STEP;
const int max_particles = RM_MAX_PARTICLES;
const int depthDistMap = RM_MAX_WIDTH * RM_MAX_HEIGHT;
const int depthParticles = RM_MAX_PARTICLES;
const int depthRays = RM_MAX_PARTICLES * RM_N_RAYS;
const int depthRaysAngle = RM_N_REAL_RAYS;
const int num_pe = RM_NUM_PE;

// mode type

typedef enum
{
    RM_MAP_LOAD,
    RM_COMPUTE_RAYS
} RMMode;

// Memory Port Width
#define USE_16BIT_RMPORT
#ifdef USE_16BIT_RMPORT
#include <stdint.h>
typedef uint16_t RMMemPort_t; // FP16
#else
typedef float RMMemPort_t; // Default: FP32
#endif

extern "C"
{
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
      float map_resolution);
}
#endif //__RM_HPP__
