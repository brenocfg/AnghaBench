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
typedef  int /*<<< orphan*/  vout_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vout_display_window_KeyboardEvent(vout_window_t *window,
                                              unsigned key)
{
    var_SetInteger(vlc_object_instance(window), "key-pressed", key);
}