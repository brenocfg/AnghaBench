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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_5__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  timer; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  posix_spawnattr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *p_sys = ih->p_sys;

    vlc_timer_destroy (p_sys->timer);
    posix_spawnattr_destroy (&p_sys->attr);
    free (p_sys);
}