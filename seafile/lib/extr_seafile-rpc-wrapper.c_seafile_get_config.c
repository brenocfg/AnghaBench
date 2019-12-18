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
 char* searpc_client_call__string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*,char const*) ; 

char *
seafile_get_config (SearpcClient *client, const char *key)
{
    if (!key)
        return NULL;

    return searpc_client_call__string (
        client, "seafile_get_config", NULL, 
        1, "string", key);
}