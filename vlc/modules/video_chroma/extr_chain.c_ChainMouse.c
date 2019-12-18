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
typedef  int /*<<< orphan*/  vlc_mouse_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_chain; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int filter_chain_MouseFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ChainMouse( filter_t *p_filter, vlc_mouse_t *p_mouse,
                       const vlc_mouse_t *p_old, const vlc_mouse_t *p_new )
{
    (void) p_old;
    filter_sys_t *p_sys = p_filter->p_sys;
    return filter_chain_MouseFilter( p_sys->p_chain, p_mouse, p_new );
}