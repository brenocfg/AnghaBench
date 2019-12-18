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
struct TYPE_3__ {int b_aout_busy; int /*<<< orphan*/  lock_hold; int /*<<< orphan*/  p_parent; int /*<<< orphan*/ * p_aout; } ;
typedef  TYPE_1__ input_resource_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_resource_PutAout( input_resource_t *p_resource,
                             audio_output_t *p_aout )
{
    assert( p_aout != NULL );

    vlc_mutex_lock( &p_resource->lock_hold );
    if( p_aout == p_resource->p_aout )
    {
        assert( p_resource->b_aout_busy );
        p_resource->b_aout_busy = false;
        msg_Dbg( p_resource->p_parent, "keeping audio output" );
        p_aout = NULL;
    }
    else
        msg_Dbg( p_resource->p_parent, "destroying extra audio output" );
    vlc_mutex_unlock( &p_resource->lock_hold );

    if( p_aout != NULL )
        aout_Destroy( p_aout );
}