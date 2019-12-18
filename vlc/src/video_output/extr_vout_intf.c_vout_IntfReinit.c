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
typedef  int /*<<< orphan*/  vout_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 

void vout_IntfReinit( vout_thread_t *p_vout )
{
    var_TriggerCallback( p_vout, "video-on-top" );
    var_TriggerCallback( p_vout, "video-wallpaper" );

    var_TriggerCallback( p_vout, "video-filter" );
    var_TriggerCallback( p_vout, "sub-source" );
    var_TriggerCallback( p_vout, "sub-filter" );
    var_TriggerCallback( p_vout, "sub-margin" );
    var_TriggerCallback( p_vout, "secondary-sub-margin" );
}