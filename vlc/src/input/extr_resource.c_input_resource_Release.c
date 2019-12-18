#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_vout_dummy; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_hold; int /*<<< orphan*/ * p_aout; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ input_resource_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroySout (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyVout (TYPE_1__*) ; 
 int /*<<< orphan*/  aout_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ ) ; 

void input_resource_Release( input_resource_t *p_resource )
{
    if( !vlc_atomic_rc_dec( &p_resource->rc ) )
        return;

    DestroySout( p_resource );
    DestroyVout( p_resource );
    if( p_resource->p_aout != NULL )
        aout_Destroy( p_resource->p_aout );

    vlc_mutex_destroy( &p_resource->lock_hold );
    vlc_mutex_destroy( &p_resource->lock );
    vout_Release( p_resource->p_vout_dummy );
    free( p_resource );
}