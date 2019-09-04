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
 int /*<<< orphan*/  draw () ; 
 int /*<<< orphan*/  initialized ; 
 float rotate_t ; 
 float translate_t ; 

int loopmode(float dt, int real, int in_client)
{
   float actual_dt = dt;

   if (!initialized) return 0;

   rotate_t += dt;
   translate_t += dt;

//   music_sim();
   if (!real)
      return 0;

   if (dt > 0.25) dt = 0.25;
   if (dt < 0.01) dt = 0.01;

   draw();

   return 0;
}