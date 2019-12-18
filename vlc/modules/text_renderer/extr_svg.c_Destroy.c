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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {struct TYPE_5__* psz_file_template; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  rsvg_term () ; 

__attribute__((used)) static void Destroy( vlc_object_t *p_this )
{
    filter_t *p_filter = ( filter_t * )p_this;
    filter_sys_t *p_sys = p_filter->p_sys;
#if (GLIB_MAJOR_VERSION < 2 || GLIB_MINOR_VERSION < 36)
    rsvg_term();
#endif
    free( p_sys->psz_file_template );
    free( p_sys );
}