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
 int /*<<< orphan*/  seaf ; 
 char* seafile_session_config_get_string (int /*<<< orphan*/ ,char const*) ; 

char *
seafile_get_config (const char *key, GError **error)
{
    return seafile_session_config_get_string(seaf, key);
}