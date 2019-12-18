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

/* Variables and functions */
 int /*<<< orphan*/  VLC_CONFIG_DIR ; 
 int config_CreateDir (int /*<<< orphan*/ *,char*) ; 
 char* config_GetUserDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int config_PrepareDir (vlc_object_t *obj)
{
    char *psz_configdir = config_GetUserDir (VLC_CONFIG_DIR);
    if (psz_configdir == NULL)
        return -1;

    int ret = config_CreateDir (obj, psz_configdir);
    free (psz_configdir);
    return ret;
}