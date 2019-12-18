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
struct TYPE_5__ {scalar_t__ vr_soxr; scalar_t__ soxr; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  soxr_delete (scalar_t__) ; 

__attribute__((used)) static void
Close( vlc_object_t *p_obj )
{
    filter_t *p_filter = (filter_t *)p_obj;
    filter_sys_t *p_sys = p_filter->p_sys;

    soxr_delete( p_sys->soxr );
    if( p_sys->vr_soxr )
        soxr_delete( p_sys->vr_soxr );

    free( p_sys );
}