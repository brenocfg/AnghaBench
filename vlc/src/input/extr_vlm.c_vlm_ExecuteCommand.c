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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlm_t ;
typedef  int /*<<< orphan*/  vlm_message_t ;

/* Variables and functions */
 int ExecuteCommand (TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int vlm_ExecuteCommand( vlm_t *p_vlm, const char *psz_command,
                        vlm_message_t **pp_message)
{
    int i_result;

    vlc_mutex_lock( &p_vlm->lock );
    i_result = ExecuteCommand( p_vlm, psz_command, pp_message );
    vlc_mutex_unlock( &p_vlm->lock );

    return i_result;
}