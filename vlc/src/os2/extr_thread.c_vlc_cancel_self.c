#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vlc_thread {int killed; } ;
typedef  struct vlc_thread* PVOID ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_cancel_self (PVOID self)
{
    struct vlc_thread *th = self;

    if (likely(th != NULL))
        th->killed = true;
}