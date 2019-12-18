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
struct vlc_thread {int killable; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_thread* vlc_thread_self () ; 

void vlc_restorecancel (int state)
{
    struct vlc_thread *th = vlc_thread_self ();
    assert (state == false || state == true);

    if (th == NULL)
        return; /* Main thread - cannot be cancelled anyway */

    assert (!th->killable);
    th->killable = state != 0;
}