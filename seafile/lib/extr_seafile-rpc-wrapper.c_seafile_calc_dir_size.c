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
typedef  int /*<<< orphan*/  SearpcClient ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int searpc_client_call__int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int,char*,char const*) ; 

int
seafile_calc_dir_size (SearpcClient *client, const char *path, GError **error)
{
    return searpc_client_call__int (client, "seafile_calc_dir_size", error,
                                    1, "string", path);
}