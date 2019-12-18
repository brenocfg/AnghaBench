#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vlc_h2_stream {int interrupted; TYPE_1__* conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_h2_stream_wake_up ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,struct vlc_h2_stream*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_h2_stream_lock(struct vlc_h2_stream *s)
{
    s->interrupted = false;
    /* When using interrupts, there shall be only one waiter per stream.
     * Otherwise, there would be no ways to map the interrupt to a thread. */
    vlc_interrupt_register(vlc_h2_stream_wake_up, s);
    vlc_mutex_lock(&s->conn->lock);
}