#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 float DYNAMIC_FRICTION ; 
 float EFFECTIVE_ACCEL ; 
 float STATIC_FRICTION ; 
 float* cam_vel ; 
 float* camang ; 
 int /*<<< orphan*/  camera_to_worldspace (float*,float,float,int /*<<< orphan*/ ) ; 
 float* camloc ; 
 int controls ; 
 scalar_t__ fmod (float,int) ; 
 float pending_view_x ; 
 float pending_view_z ; 
 scalar_t__ pow (double,float) ; 
 scalar_t__ sqrt (float) ; 
 float stb_clamp (float,int,int) ; 
 float view_x_vel ; 
 float view_z_vel ; 

void process_tick_raw(float dt)
{
   int i;
   float thrust[3] = { 0,0,0 };
   float world_thrust[3];

   // choose direction to apply thrust

   thrust[0] = (controls &  3)== 1 ? EFFECTIVE_ACCEL : (controls &  3)== 2 ? -EFFECTIVE_ACCEL : 0;
   thrust[1] = (controls & 12)== 4 ? EFFECTIVE_ACCEL : (controls & 12)== 8 ? -EFFECTIVE_ACCEL : 0;
   thrust[2] = (controls & 48)==16 ? EFFECTIVE_ACCEL : (controls & 48)==32 ? -EFFECTIVE_ACCEL : 0;

   // @TODO clamp thrust[0] & thrust[1] vector length to EFFECTIVE_ACCEL

   camera_to_worldspace(world_thrust, thrust[0], thrust[1], 0);
   world_thrust[2] += thrust[2];

   for (i=0; i < 3; ++i) {
      float acc = world_thrust[i];
      cam_vel[i] += acc*dt;
   }

   if (cam_vel[0] || cam_vel[1] || cam_vel[2])
   {
      float vel = (float) sqrt(cam_vel[0]*cam_vel[0] + cam_vel[1]*cam_vel[1] + cam_vel[2]*cam_vel[2]);
      float newvel = vel;
      float dec = STATIC_FRICTION + DYNAMIC_FRICTION*vel;
      newvel = vel - dec*dt;
      if (newvel < 0)
         newvel = 0;
      cam_vel[0] *= newvel/vel;
      cam_vel[1] *= newvel/vel;
      cam_vel[2] *= newvel/vel;
   }

   camloc[0] += cam_vel[0] * dt;
   camloc[1] += cam_vel[1] * dt;
   camloc[2] += cam_vel[2] * dt;

   view_x_vel *= (float) pow(0.75, dt);
   view_z_vel *= (float) pow(0.75, dt);

   view_x_vel += (pending_view_x - view_x_vel)*dt*60;
   view_z_vel += (pending_view_z - view_z_vel)*dt*60;

   pending_view_x -= view_x_vel * dt;
   pending_view_z -= view_z_vel * dt;
   camang[0] += view_x_vel * dt;
   camang[2] += view_z_vel * dt;
   camang[0] = stb_clamp(camang[0], -90, 90);
   camang[2] = (float) fmod(camang[2], 360);
}