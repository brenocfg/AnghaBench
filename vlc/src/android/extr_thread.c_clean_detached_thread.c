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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct vlc_thread {TYPE_1__ wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_thread*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clean_detached_thread(void *data)
{
    struct vlc_thread *th = data;

    /* release thread handle */
    vlc_mutex_destroy(&th->wait.lock);
    free(th);
}