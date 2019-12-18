#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  condvar; } ;
typedef  TYPE_1__ vlc_static_cond_t ;
struct TYPE_9__ {scalar_t__ hev; } ;
typedef  TYPE_2__ vlc_cond_t ;

/* Variables and functions */
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 TYPE_1__* static_condvar_start ; 
 int /*<<< orphan*/  super_mutex ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cond_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_static_cond_init (vlc_cond_t *p_condvar)
{
    vlc_mutex_lock (&super_mutex);

    if (p_condvar->hev == NULLHANDLE)
    {
        vlc_cond_init (p_condvar);

        vlc_static_cond_t *new_static_condvar;

        new_static_condvar = malloc (sizeof (*new_static_condvar));
        if (unlikely (!new_static_condvar))
            abort();

        memcpy (&new_static_condvar->condvar, p_condvar, sizeof (*p_condvar));
        new_static_condvar->next = static_condvar_start;
        static_condvar_start = new_static_condvar;
    }

    vlc_mutex_unlock (&super_mutex);
}