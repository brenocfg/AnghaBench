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
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_error_id_to_str (int) ; 

char*
seafile_sync_error_id_to_str (int error_id, GError **error)
{
    return g_strdup(sync_error_id_to_str (error_id));
}