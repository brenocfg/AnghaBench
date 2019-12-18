#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_thread_t ;
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  cancel_sock; int /*<<< orphan*/  done_event; int /*<<< orphan*/  cancel_event; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DosCloseEventSem (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INTERRUPT ; 
 int /*<<< orphan*/  SEM_INDEFINITE_WAIT ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  soclose (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

void vlc_join (vlc_thread_t th, void **result)
{
    ULONG rc;

    do
    {
        vlc_testcancel();
        rc = vlc_WaitForSingleObject( th->done_event, SEM_INDEFINITE_WAIT );
    } while( rc == ERROR_INTERRUPT );

    if (result != NULL)
        *result = th->data;

    DosCloseEventSem( th->cancel_event );
    DosCloseEventSem( th->done_event );

    soclose( th->cancel_sock );

    free( th );
}