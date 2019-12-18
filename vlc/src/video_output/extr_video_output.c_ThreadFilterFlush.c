#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* p; } ;
typedef  TYPE_4__ vout_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain_interactive; int /*<<< orphan*/  chain_static; } ;
struct TYPE_6__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * current; } ;
struct TYPE_8__ {TYPE_2__ filter; TYPE_1__ displayed; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_chain_VideoFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ThreadFilterFlush(vout_thread_t *vout, bool is_locked)
{
    if (vout->p->displayed.current)
    {
        picture_Release( vout->p->displayed.current );
        vout->p->displayed.current = NULL;
    }

    if (vout->p->displayed.next)
    {
        picture_Release( vout->p->displayed.next );
        vout->p->displayed.next = NULL;
    }

    if (!is_locked)
        vlc_mutex_lock(&vout->p->filter.lock);
    filter_chain_VideoFlush(vout->p->filter.chain_static);
    filter_chain_VideoFlush(vout->p->filter.chain_interactive);
    if (!is_locked)
        vlc_mutex_unlock(&vout->p->filter.lock);
}