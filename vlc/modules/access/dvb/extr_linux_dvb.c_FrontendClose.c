#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_frontend; int /*<<< orphan*/  i_frontend_handle; } ;
typedef  TYPE_1__ dvb_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 

void FrontendClose( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    VLC_UNUSED(p_access);
    if( p_sys->p_frontend )
    {
        vlc_close( p_sys->i_frontend_handle );
        free( p_sys->p_frontend );

        p_sys->p_frontend = NULL;
    }
}