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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ) ;struct TYPE_2__* next; } ;
typedef  TYPE_1__ vlc_cleanup_t ;
struct vlc_thread {int /*<<< orphan*/ * data; int /*<<< orphan*/  done_event; TYPE_1__* cleaners; scalar_t__ killed; scalar_t__ killable; int /*<<< orphan*/  cancel_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DosPostEventSem (int /*<<< orphan*/ ) ; 
 scalar_t__ DosWaitEventSem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  _endthread () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cancel_self (struct vlc_thread*) ; 
 int /*<<< orphan*/  vlc_thread_cleanup (struct vlc_thread*) ; 
 struct vlc_thread* vlc_thread_self () ; 

void vlc_testcancel (void)
{
    struct vlc_thread *th = vlc_thread_self ();
    if (th == NULL)
        return; /* Main thread - cannot be cancelled anyway */

    /* This check is needed for the case that vlc_cancel() is followed by
     * vlc_testcancel() without any cancellation point */
    if( DosWaitEventSem( th->cancel_event, 0 ) == NO_ERROR )
        vlc_cancel_self( th );

    if (th->killable && th->killed)
    {
        for (vlc_cleanup_t *p = th->cleaners; p != NULL; p = p->next)
             p->proc (p->data);

        DosPostEventSem( th->done_event );
        th->data = NULL; /* TODO: special value? */
        vlc_thread_cleanup (th);
        _endthread();
    }
}