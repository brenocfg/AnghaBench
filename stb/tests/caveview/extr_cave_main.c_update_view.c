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
 float pending_view_x ; 
 float pending_view_z ; 

void update_view(float dx, float dy)
{
   // hard-coded mouse sensitivity, not resolution independent?
   pending_view_z -= dx*300;
   pending_view_x -= dy*700;
}