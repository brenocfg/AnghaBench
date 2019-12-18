#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; scalar_t__ p_blend; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  LogoCallback ; 
 int /*<<< orphan*/  LogoListUnload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_DeleteBlend (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__* ppsz_filter_callbacks ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys = p_filter->p_sys;

    for( int i = 0; ppsz_filter_callbacks[i]; i++ )
        var_DelCallback( p_filter, ppsz_filter_callbacks[i],
                         LogoCallback, p_sys );

    if( p_sys->p_blend )
        filter_DeleteBlend( p_sys->p_blend );

    vlc_mutex_destroy( &p_sys->lock );
    LogoListUnload( &p_sys->list );
    free( p_sys );
}