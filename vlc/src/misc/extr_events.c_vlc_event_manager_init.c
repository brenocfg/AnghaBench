#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* events; int /*<<< orphan*/  lock; void* p_obj; } ;
typedef  TYPE_1__ vlc_event_manager_t ;
struct TYPE_5__ {int /*<<< orphan*/  listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_init_recursive (int /*<<< orphan*/ *) ; 

void vlc_event_manager_init( vlc_event_manager_t * p_em, void * p_obj )
{
    p_em->p_obj = p_obj;
    /* This is an unsafe work-around for a long-standing playlist bug.
     * Do not rely on this. */
    vlc_mutex_init_recursive( &p_em->lock );

    for( size_t i = 0; i < ARRAY_SIZE(p_em->events); i++ )
       ARRAY_INIT( p_em->events[i].listeners );
}