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
typedef  struct vlc_thread* vlc_thread_t ;
struct vlc_thread {void* (* entry ) (void*) ;int detached; int killable; int killed; scalar_t__ cancel_sock; int /*<<< orphan*/  done_event; int /*<<< orphan*/  cancel_event; scalar_t__ tid; int /*<<< orphan*/ * cleaners; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  DosCloseEventSem (int /*<<< orphan*/ ) ; 
 scalar_t__ DosCreateEventSem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosSetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HIBYTE (int) ; 
 int /*<<< orphan*/  LOBYTE (int) ; 
 int /*<<< orphan*/  PRTYS_THREAD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct vlc_thread*) ; 
 int /*<<< orphan*/  free (struct vlc_thread*) ; 
 struct vlc_thread* malloc (int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soclose (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_entry ; 

__attribute__((used)) static int vlc_clone_attr (vlc_thread_t *p_handle, bool detached,
                           void *(*entry) (void *), void *data, int priority)
{
    struct vlc_thread *th = malloc (sizeof (*th));
    if (unlikely(th == NULL))
        return ENOMEM;
    th->entry = entry;
    th->data = data;
    th->detached = detached;
    th->killable = false; /* not until vlc_entry() ! */
    th->killed = false;
    th->cleaners = NULL;

    if( DosCreateEventSem (NULL, &th->cancel_event, 0, FALSE))
        goto error;
    if( DosCreateEventSem (NULL, &th->done_event, 0, FALSE))
        goto error;

    th->cancel_sock = socket (AF_LOCAL, SOCK_STREAM, 0);
    if( th->cancel_sock < 0 )
        goto error;

    th->tid = _beginthread (vlc_entry, NULL, 1024 * 1024, th);
    if((int)th->tid == -1)
        goto error;

    if (p_handle != NULL)
        *p_handle = th;

    if (priority)
        DosSetPriority(PRTYS_THREAD,
                       HIBYTE(priority),
                       LOBYTE(priority),
                       th->tid);

    return 0;

error:
    soclose (th->cancel_sock);
    DosCloseEventSem (th->cancel_event);
    DosCloseEventSem (th->done_event);
    free (th);

    return ENOMEM;
}