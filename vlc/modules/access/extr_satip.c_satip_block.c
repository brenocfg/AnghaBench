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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int woken; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_fifo_DequeueUnlocked (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_fifo_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t* satip_block(stream_t *access, bool *restrict eof) {
    access_sys_t *sys = access->p_sys;
    block_t *block;

    vlc_fifo_Lock(sys->fifo);

    while (vlc_fifo_IsEmpty(sys->fifo)) {
        if (sys->woken)
            break;
        vlc_fifo_Wait(sys->fifo);
    }

    if ((block = vlc_fifo_DequeueUnlocked(sys->fifo)) == NULL)
        *eof = true;
    sys->woken = false;
    vlc_fifo_Unlock(sys->fifo);

    return block;
}