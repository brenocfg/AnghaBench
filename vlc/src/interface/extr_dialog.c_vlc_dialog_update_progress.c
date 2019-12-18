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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;

/* Variables and functions */
 int dialog_update_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 

int
vlc_dialog_update_progress(vlc_object_t *p_obj, vlc_dialog_id *p_id,
                           float f_value)
{
    return dialog_update_progress(p_obj, p_id, f_value, NULL);
}