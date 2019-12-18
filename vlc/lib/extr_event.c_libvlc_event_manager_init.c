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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  listeners; void* p_obj; } ;
typedef  TYPE_1__ libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init_recursive (int /*<<< orphan*/ *) ; 

void libvlc_event_manager_init(libvlc_event_manager_t *em, void *obj)
{
    em->p_obj = obj;
    vlc_array_init(&em->listeners);
    vlc_mutex_init_recursive(&em->lock);
}