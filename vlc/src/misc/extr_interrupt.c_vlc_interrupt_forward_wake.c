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
struct TYPE_5__ {int /*<<< orphan*/  killed; } ;
typedef  TYPE_1__ vlc_interrupt_t ;

/* Variables and functions */
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_interrupt_kill (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_interrupt_raise (TYPE_1__*) ; 

__attribute__((used)) static void vlc_interrupt_forward_wake(void *opaque)
{
    void **data = opaque;
    vlc_interrupt_t *to = data[0];
    vlc_interrupt_t *from = data[1];

    (atomic_load(&from->killed) ? vlc_interrupt_kill
                                : vlc_interrupt_raise)(to);
}