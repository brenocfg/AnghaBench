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
struct TYPE_2__ {int /*<<< orphan*/  killed; int /*<<< orphan*/  killable; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* thread ; 

void vlc_testcancel (void)
{
    if (!thread) /* not created by VLC, can't be cancelled */
        return;
    if (!thread->killable)
        return;
    if (!atomic_load(&thread->killed))
        return;

    pthread_exit(NULL);
}