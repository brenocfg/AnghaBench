#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ yrel; scalar_t__ xrel; } ;
struct TYPE_5__ {TYPE_1__ motion; } ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
 float screen_x ; 
 float screen_y ; 
 int /*<<< orphan*/  update_view (float,float) ; 

void  process_sdl_mouse(SDL_Event *e)
{
   update_view((float) e->motion.xrel / screen_x, (float) e->motion.yrel / screen_y);
}