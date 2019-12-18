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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free_error () ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__ refs ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_threadvar_delete (int /*<<< orphan*/ *) ; 

void libvlc_threads_deinit (void)
{
    vlc_mutex_lock (&lock);
    assert (refs > 0);
    if (--refs == 0)
    {
        free_error ();
        vlc_threadvar_delete (&context);
    }
    vlc_mutex_unlock (&lock);
}