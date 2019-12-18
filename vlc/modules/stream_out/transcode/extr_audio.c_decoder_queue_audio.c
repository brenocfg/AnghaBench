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
struct decoder_owner {TYPE_3__* id; } ;
struct TYPE_7__ {TYPE_4__** last; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ audio; } ;
struct TYPE_8__ {TYPE_1__ fifo; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_9__ {struct TYPE_9__* p_next; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decoder_queue_audio( decoder_t *p_dec, block_t *p_audio )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_id_sys_t *id = p_owner->id;

    vlc_mutex_lock(&id->fifo.lock);
    *id->fifo.audio.last = p_audio;
    id->fifo.audio.last = &p_audio->p_next;
    vlc_mutex_unlock(&id->fifo.lock);
}