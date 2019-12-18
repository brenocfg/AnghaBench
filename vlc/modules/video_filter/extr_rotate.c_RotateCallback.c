#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f_float; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  filter_sys_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  store_trigo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int RotateCallback( vlc_object_t *p_this, char const *psz_var,
                           vlc_value_t oldval, vlc_value_t newval, void *data )
{
    filter_sys_t *p_sys = data;

    store_trigo( p_sys, newval.f_float );
    (void) p_this; (void) psz_var; (void) oldval;
    return VLC_SUCCESS;
}