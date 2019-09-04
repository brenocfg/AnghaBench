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
 double* camang ; 
 scalar_t__ cos (double) ; 
 scalar_t__ sin (double) ; 

void camera_to_worldspace(float world[3], float cam_x, float cam_y, float cam_z)
{
   float vec[3] = { cam_x, cam_y, cam_z };
   float t[3];
   float s,c;
   s = (float) sin(camang[0]*3.141592/180);
   c = (float) cos(camang[0]*3.141592/180);

   t[0] = vec[0];
   t[1] = c*vec[1] - s*vec[2];
   t[2] = s*vec[1] + c*vec[2];

   s = (float) sin(camang[2]*3.141592/180);
   c = (float) cos(camang[2]*3.141592/180);
   world[0] = c*t[0] - s*t[1];
   world[1] = s*t[0] + c*t[1];
   world[2] = t[2];
}