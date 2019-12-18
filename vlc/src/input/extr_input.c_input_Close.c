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
struct TYPE_2__ {int /*<<< orphan*/  interrupt; int /*<<< orphan*/  thread; scalar_t__ is_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  Destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void input_Close( input_thread_t *p_input )
{
    if( input_priv(p_input)->is_running )
        vlc_join( input_priv(p_input)->thread, NULL );
    vlc_interrupt_deinit( &input_priv(p_input)->interrupt );
    Destroy(p_input);
}