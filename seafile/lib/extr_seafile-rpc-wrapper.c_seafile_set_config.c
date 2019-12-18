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

/* Variables and functions */
 int searpc_client_call__int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*,char const*,char*,char const*) ; 

int
seafile_set_config (SearpcClient *client, const char *key, const char *value)
{
    if (!key || !value)
        return -1;

    return searpc_client_call__int (
        client, "seafile_set_config", NULL,
        2, "string", key, "string", value);
}