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
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free_msg ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  refs ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_threadvar_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void libvlc_threads_init (void)
{
    vlc_mutex_lock (&lock);
    if (refs++ == 0)
        vlc_threadvar_create (&context, free_msg);
    vlc_mutex_unlock (&lock);
}