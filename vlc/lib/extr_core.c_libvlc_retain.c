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
struct TYPE_3__ {scalar_t__ ref_count; int /*<<< orphan*/  instance_lock; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_retain( libvlc_instance_t *p_instance )
{
    assert( p_instance != NULL );
    assert( p_instance->ref_count < UINT_MAX );

    vlc_mutex_lock( &p_instance->instance_lock );
    p_instance->ref_count++;
    vlc_mutex_unlock( &p_instance->instance_lock );
}