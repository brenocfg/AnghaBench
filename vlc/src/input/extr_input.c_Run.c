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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_2__ {int /*<<< orphan*/  thread; scalar_t__ b_out_pace_control; scalar_t__ b_can_pace_control; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ input_thread_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  End (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MainLoop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  input_SendEventDead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_set_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *Run( void *data )
{
    input_thread_private_t *priv = data;
    input_thread_t *p_input = &priv->input;

    vlc_interrupt_set(&priv->interrupt);

    if( !Init( p_input ) )
    {
        if( priv->b_can_pace_control && priv->b_out_pace_control )
        {
            /* We don't want a high input priority here or we'll
             * end-up sucking up all the CPU time */
            vlc_set_priority( priv->thread, VLC_THREAD_PRIORITY_LOW );
        }

        MainLoop( p_input, true ); /* FIXME it can be wrong (like with VLM) */

        /* Clean up */
        End( p_input );
    }

    input_SendEventDead( p_input );
    return NULL;
}