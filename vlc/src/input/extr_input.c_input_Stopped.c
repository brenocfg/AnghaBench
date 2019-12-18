#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_3__ {int is_stopped; int /*<<< orphan*/  lock_control; } ;
typedef  TYPE_1__ input_thread_private_t ;

/* Variables and functions */
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool input_Stopped( input_thread_t *input )
{
    input_thread_private_t *sys = input_priv(input);
    bool ret;

    vlc_mutex_lock( &sys->lock_control );
    ret = sys->is_stopped;
    vlc_mutex_unlock( &sys->lock_control );
    return ret;
}