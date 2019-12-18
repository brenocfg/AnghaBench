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
struct TYPE_4__ {int b_error; int b_ready; int /*<<< orphan*/  obj; int /*<<< orphan*/  b_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
typedef  TYPE_1__ event_thread_t ;
typedef  int /*<<< orphan*/  MSG ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32VoutCloseWindow (TYPE_1__*) ; 
 scalar_t__ Win32VoutCreateWindow (TYPE_1__*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *EventThread( void *p_this )
{
    event_thread_t *p_event = (event_thread_t *)p_this;
    MSG msg;
    int canc = vlc_savecancel ();


    vlc_mutex_lock( &p_event->lock );
    /* Create a window for the video */
    /* Creating a window under Windows also initializes the thread's event
     * message queue */
    if( Win32VoutCreateWindow( p_event ) )
        p_event->b_error = true;

    p_event->b_ready = true;
    vlc_cond_signal( &p_event->wait );

    const bool b_error = p_event->b_error;
    vlc_mutex_unlock( &p_event->lock );

    if( b_error )
    {
        vlc_restorecancel( canc );
        return NULL;
    }

    /* Main loop */
    /* GetMessage will sleep if there's no message in the queue */
    for( ;; )
    {
        if( !GetMessage( &msg, 0, 0, 0 ) || atomic_load( &p_event->b_done ) )
        {
            break;
        }

        /* Messages we don't handle directly are dispatched to the
         * window procedure */
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    } /* End Main loop */

    msg_Dbg( p_event->obj, "Win32 Vout EventThread terminating" );

    Win32VoutCloseWindow( p_event );
    vlc_restorecancel(canc);
    return NULL;
}