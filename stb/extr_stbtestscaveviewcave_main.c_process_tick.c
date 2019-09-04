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
 int /*<<< orphan*/  process_tick_raw (float) ; 

void process_tick(float dt)
{
   while (dt > 1.0f/60) {
      process_tick_raw(1.0f/60);
      dt -= 1.0f/60;
   }
   process_tick_raw(dt);
}