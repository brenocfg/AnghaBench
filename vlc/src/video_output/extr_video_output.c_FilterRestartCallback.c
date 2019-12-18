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
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_ControlChangeFilters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int FilterRestartCallback(vlc_object_t *p_this, char const *psz_var,
                                 vlc_value_t oldval, vlc_value_t newval,
                                 void *p_data)
{
    (void) p_this; (void) psz_var; (void) oldval; (void) newval;
    vout_ControlChangeFilters((vout_thread_t *)p_data, NULL);
    return 0;
}