#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock_hold; int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_parent; int /*<<< orphan*/  rc; int /*<<< orphan*/  p_vout_dummy; } ;
typedef  TYPE_1__ input_resource_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_CreateDummy (int /*<<< orphan*/ *) ; 

input_resource_t *input_resource_New( vlc_object_t *p_parent )
{
    input_resource_t *p_resource = calloc( 1, sizeof(*p_resource) );
    if( !p_resource )
        return NULL;

    p_resource->p_vout_dummy = vout_CreateDummy(p_parent);
    if( !p_resource->p_vout_dummy )
    {
        free( p_resource );
        return NULL;
    }

    vlc_atomic_rc_init( &p_resource->rc );
    p_resource->p_parent = p_parent;
    vlc_mutex_init( &p_resource->lock );
    vlc_mutex_init( &p_resource->lock_hold );
    return p_resource;
}