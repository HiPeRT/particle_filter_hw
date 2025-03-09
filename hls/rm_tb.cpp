#include <cmath>
#include <stdio.h>

#include "RM.hpp"

#include "data.hpp"
#include "rays_gold.hpp"

volatile float rays[N_PARTICLES * N_RAYS];

RMMemPort_t private_map_pe0[HEIGHT * WIDTH];
RMMemPort_t* private_map_pe1 = private_map_pe0;
RMMemPort_t* private_map_pe2 = private_map_pe0;
RMMemPort_t* private_map_pe3 = private_map_pe0;
RMMemPort_t* private_map_pe4 = private_map_pe0;
RMMemPort_t* private_map_pe5 = private_map_pe0;
RMMemPort_t* private_map_pe6 = private_map_pe0;
RMMemPort_t* private_map_pe7 = private_map_pe0;

// These work in C simulation
// RMMemPort_t *private_map_pe1 = private_map_pe0;
// RMMemPort_t *private_map_pe2 = private_map_pe0;
// RMMemPort_t *private_map_pe3 = private_map_pe0;
// RMMemPort_t *private_map_pe4 = private_map_pe0;
// RMMemPort_t *private_map_pe5 = private_map_pe0;
// RMMemPort_t *private_map_pe6 = private_map_pe0;
// RMMemPort_t *private_map_pe7 = private_map_pe0;

int main()
{
    RMDS(distanceMap,
         x,
         y,
         yaw,
         rays,
         ray_index,
         RM_MAP_LOAD,
         map_height,
         map_width,
         N_PARTICLES,
         orig_x,
         orig_y,
         map_resolution,
         private_map_pe0,
         private_map_pe1,
         private_map_pe2,
         private_map_pe3,
         private_map_pe4,
         private_map_pe5,
         private_map_pe6,
         private_map_pe7);

    float mean;

    mean = 0;

    RMDS(distanceMap,
         x,
         y,
         yaw,
         rays,
         ray_index,
         RM_COMPUTE_RAYS,
         map_height,
         map_width,
         N_PARTICLES,
         orig_x,
         orig_y,
         map_resolution,
         private_map_pe0,
         private_map_pe1,
         private_map_pe2,
         private_map_pe3,
         private_map_pe4,
         private_map_pe5,
         private_map_pe6,
         private_map_pe7);

    for (int i = 0; i < 60; i++) {
        printf("iter i = %d rays_g = %f, rays= %f\n", i, rays_g[i * 18], rays[i]);
        mean += (std::pow(rays_g[i * 18] - rays[i], 2)) * 1 / 100;
    }

    printf("rmse = %f\n", std::sqrt(mean));

    //	RMParticle_t particle;
    //	particle.x = RMHP_t(xg);
    //	particle.y = RMHP_t(yg);
    //	particle.yaw = RMHP_t(yawg);
    //
    //
    //	RMConfig_t config;
    //	config.map_height = RMIter_t(HEIGHT);
    //	config.map_width = RMIter_t(WIDTH);
    //	config.map_resolution= RMHP_t(map_resolution);
    //	config.n_particles= 1000;
    //	config.orig_x= RMHP_t(orig_x);
    //	config.orig_y= RMHP_t(orig_y);
    //
    //	float tmp;
    //	for(int i=0; i<60; i++){
    //		RMDist2HP(tmp, RMComputeRay( particle, ray_index[i], config, distanceMap));
    //		printf("d = %f\n", tmp);
    //	}

    return 0;
}
