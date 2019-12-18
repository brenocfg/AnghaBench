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
struct vlc_thread {int killable; int /*<<< orphan*/  done_event; int /*<<< orphan*/  data; int /*<<< orphan*/  (* entry ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DosPostEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_key ; 
 int /*<<< orphan*/  vlc_thread_cleanup (struct vlc_thread*) ; 
 int /*<<< orphan*/  vlc_threadvar_set (int /*<<< orphan*/ ,struct vlc_thread*) ; 

__attribute__((used)) static void vlc_entry( void *p )
{
    struct vlc_thread *th = p;

    vlc_threadvar_set (thread_key, th);
    th->killable = true;
    th->data = th->entry (th->data);
    DosPostEventSem( th->done_event );
    vlc_thread_cleanup (th);
}