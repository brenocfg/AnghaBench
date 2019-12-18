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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {int is_running; int /*<<< orphan*/  thread; scalar_t__ b_preparsing; } ;
typedef  TYPE_1__ input_thread_private_t ;

/* Variables and functions */
 void* Preparse (void*) ; 
 void* Run (void*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_clone (int /*<<< orphan*/ *,void* (*) (void*),TYPE_1__*,int /*<<< orphan*/ ) ; 

int input_Start( input_thread_t *p_input )
{
    input_thread_private_t *priv = input_priv(p_input);
    void *(*func)(void *) = Run;

    if( priv->b_preparsing )
        func = Preparse;

    assert( !priv->is_running );
    /* Create thread and wait for its readiness. */
    priv->is_running = !vlc_clone( &priv->thread, func, priv,
                                   VLC_THREAD_PRIORITY_INPUT );
    if( !priv->is_running )
    {
        msg_Err( p_input, "cannot create input thread" );
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}