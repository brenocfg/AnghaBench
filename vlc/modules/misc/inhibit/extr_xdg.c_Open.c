#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  inhibit; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_7__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  timer; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  Inhibit ; 
 int POSIX_SPAWN_SETSIGDEF ; 
 int POSIX_SPAWN_SETSIGMASK ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  Timer ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  posix_spawnattr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_spawnattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_spawnattr_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  posix_spawnattr_setsigdefault (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_spawnattr_setsigmask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *p_sys = malloc (sizeof (*p_sys));
    if (p_sys == NULL)
        return VLC_ENOMEM;

    posix_spawnattr_init (&p_sys->attr);
    /* Reset signal handlers to default and clear mask in the child process */
    {
        sigset_t set;

        sigemptyset (&set);
        posix_spawnattr_setsigmask (&p_sys->attr, &set);
        sigaddset (&set, SIGPIPE);
        posix_spawnattr_setsigdefault (&p_sys->attr, &set);
        posix_spawnattr_setflags (&p_sys->attr, POSIX_SPAWN_SETSIGDEF
                                              | POSIX_SPAWN_SETSIGMASK);
    }

    ih->p_sys = p_sys;
    if (vlc_timer_create (&p_sys->timer, Timer, ih))
    {
        posix_spawnattr_destroy (&p_sys->attr);
        free (p_sys);
        return VLC_ENOMEM;
    }

    ih->inhibit = Inhibit;
    return VLC_SUCCESS;
}