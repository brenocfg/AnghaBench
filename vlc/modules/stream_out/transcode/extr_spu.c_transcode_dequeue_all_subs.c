#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_5__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ spu; } ;
struct TYPE_7__ {TYPE_2__ fifo; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *transcode_dequeue_all_subs( sout_stream_id_sys_t *id )
{
    vlc_mutex_lock(&id->fifo.lock);
    subpicture_t *p_subpics = id->fifo.spu.first;
    id->fifo.spu.first = NULL;
    id->fifo.spu.last = &id->fifo.spu.first;
    vlc_mutex_unlock(&id->fifo.lock);

    return p_subpics;
}