#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vlc_thread_t ;
typedef  int /*<<< orphan*/  atomic_int ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {TYPE_1__ wait; int /*<<< orphan*/  killed; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_or_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  vlc_addr_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_cancel (vlc_thread_t thread_id)
{
    atomic_int *addr;

    atomic_store(&thread_id->killed, true);

    vlc_mutex_lock(&thread_id->wait.lock);
    addr = thread_id->wait.addr;
    if (addr != NULL)
    {
        atomic_fetch_or_explicit(addr, 1, memory_order_relaxed);
        vlc_addr_broadcast(addr);
    }
    vlc_mutex_unlock(&thread_id->wait.lock);
}