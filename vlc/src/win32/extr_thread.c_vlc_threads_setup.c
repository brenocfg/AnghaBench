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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABOVE_NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  HIGH_PRIORITY_CLASS ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectClockSource (int /*<<< orphan*/ *) ; 
 scalar_t__ SetPriorityClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mdate_default ; 
 scalar_t__ mdate_selected ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setup_lock ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 

void vlc_threads_setup(libvlc_int_t *vlc)
{
    EnterCriticalSection(&setup_lock);
    if (mdate_selected != mdate_default)
    {
        LeaveCriticalSection(&setup_lock);
        return;
    }

    if (!SelectClockSource((vlc != NULL) ? VLC_OBJECT(vlc) : NULL))
        abort();
    assert(mdate_selected != mdate_default);

#if !VLC_WINSTORE_APP
    /* Raise default priority of the current process */
#ifndef ABOVE_NORMAL_PRIORITY_CLASS
#   define ABOVE_NORMAL_PRIORITY_CLASS 0x00008000
#endif
    if (var_InheritBool(vlc, "high-priority"))
    {
        if (SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS)
         || SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
            msg_Dbg(vlc, "raised process priority");
        else
            msg_Dbg(vlc, "could not raise process priority");
    }
#endif
    LeaveCriticalSection(&setup_lock);
}