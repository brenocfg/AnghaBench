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
 double TICKRATE ; 
 float carried_dt ; 
 int /*<<< orphan*/  draw () ; 
 int global_hack ; 
 float global_timer ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  process_tick (float) ; 
 int tex2_alpha ; 

int loopmode(float dt, int real, int in_client)
{
   if (!initialized) return 0;

   if (!real)
      return 0;

   // don't allow more than 6 frames to update at a time
   if (dt > 0.075) dt = 0.075;

   global_timer += dt;

   carried_dt += dt;
   while (carried_dt > 1.0/TICKRATE) {
      if (global_hack) {
         tex2_alpha += global_hack / 60.0f;
         if (tex2_alpha < 0) tex2_alpha = 0;
         if (tex2_alpha > 1) tex2_alpha = 1;
      }
      //update_input();
      // if the player is dead, stop the sim
      carried_dt -= 1.0/TICKRATE;
   }

   process_tick(dt);
   draw();

   return 0;
}