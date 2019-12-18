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
typedef  int /*<<< orphan*/  vlc_mutex_t ;
struct TYPE_5__ {scalar_t__ hev; } ;
typedef  TYPE_1__ vlc_cond_t ;

/* Variables and functions */
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  SEM_INDEFINITE_WAIT ; 
 int /*<<< orphan*/  vlc_cond_wait_common (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_static_cond_init (TYPE_1__*) ; 

void vlc_cond_wait (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex)
{
    if (p_condvar->hev == NULLHANDLE)
        vlc_static_cond_init (p_condvar);

    vlc_cond_wait_common (p_condvar, p_mutex, SEM_INDEFINITE_WAIT);
}