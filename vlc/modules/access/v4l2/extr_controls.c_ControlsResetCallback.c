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
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ControlsReset (int /*<<< orphan*/ *,void*) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int ControlsResetCallback (vlc_object_t *obj, const char *var,
                                  vlc_value_t old, vlc_value_t cur, void *data)
{
    ControlsReset (obj, data);
    (void) var; (void) old; (void) cur;
    return VLC_SUCCESS;
}