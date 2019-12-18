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
struct TYPE_3__ {int /*<<< orphan*/  lock_hold; int /*<<< orphan*/ * p_aout; } ;
typedef  TYPE_1__ input_resource_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

audio_output_t *input_resource_HoldAout( input_resource_t *p_resource )
{
    audio_output_t *p_aout;

    vlc_mutex_lock( &p_resource->lock_hold );
    p_aout = p_resource->p_aout;
    if( p_aout != NULL )
        aout_Hold(p_aout);
    vlc_mutex_unlock( &p_resource->lock_hold );

    return p_aout;
}