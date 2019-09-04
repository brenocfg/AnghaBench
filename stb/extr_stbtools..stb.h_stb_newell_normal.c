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
 double sqrt (float) ; 

void stb_newell_normal(float *normal, int num_vert, float **vert, int normalize)
{
   int i,j;
   float p;
   normal[0] = normal[1] = normal[2] = 0;
   for (i=num_vert-1,j=0; j < num_vert; i=j++) {
      float *u = vert[i];
      float *v = vert[j];
      normal[0] += (u[1] - v[1]) * (u[2] + v[2]);
      normal[1] += (u[2] - v[2]) * (u[0] + v[0]);
      normal[2] += (u[0] - v[0]) * (u[1] + v[1]);
   }
   if (normalize) {
      p = normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2];
      p = (float) (1.0 / sqrt(p));
      normal[0] *= p;
      normal[1] *= p;
      normal[2] *= p;
   }
}