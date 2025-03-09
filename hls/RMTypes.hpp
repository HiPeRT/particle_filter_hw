#ifndef __RMDATATYPES_HPP__
#define __RMDATATYPES_HPP__

#include <stdint.h>
#include <hls_stream.h>
#include <hls_math.h>

// Compute Datatype
#ifdef USE_FLOAT_RMDATA
typedef float RMHP_t; // FP32
#else
#include <ap_fixed.h>

// High Precision Fixed-Point
#define RMHP_BITS (22)
#define RMHP_INT_BITS (7) //Breaks if is lower that 7
typedef ap_fixed<RMHP_BITS,RMHP_INT_BITS> RMHP_t;

// Low Precision Unsigned Fixed-Point (dist map)
#define RMDIST_BITS (16)
#define RMDIST_INT_BITS (5)
typedef ap_ufixed<RMDIST_BITS,RMDIST_INT_BITS> RMDist_t;

#define RMDist2HP(dist_t, hp_t) \
  do { \
	hp_t = RMHP_t(0); \
	hp_t.range(RMHP_BITS-(RMHP_INT_BITS-RMDIST_INT_BITS),RMHP_BITS-(RMHP_INT_BITS-RMDIST_INT_BITS)-RMDIST_BITS) = dist_t; \
  } while (0)

#define RMHP2Dist(hp_t, dist_t) \
  do { \
	dist_t.range() = hp_t.range(RMHP_BITS-(RMHP_INT_BITS-RMDIST_INT_BITS),RMHP_BITS-(RMHP_INT_BITS-RMDIST_INT_BITS)-RMDIST_BITS); \
  } while (0)
#endif

typedef uint16_t RMIter_t;

typedef struct
{
	RMHP_t x;
	RMHP_t y;
	RMHP_t yaw;
} RMParticle_t;

typedef struct
{
	RMIter_t map_height;
	RMIter_t map_width;
	RMIter_t n_particles;
	RMHP_t orig_x;
	RMHP_t orig_y;
	RMHP_t map_resolution;
} RMConfig_t;

#endif // __RMDATATYPES_HPP__
