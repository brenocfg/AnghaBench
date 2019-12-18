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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * roles ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* var_GetString (int /*<<< orphan*/ *,char*) ; 

int libvlc_media_player_get_role(libvlc_media_player_t *mp)
{
    int ret = -1;
    char *str = var_GetString(mp, "role");
    if (str == NULL)
        return 0;

    for (size_t i = 0; i < ARRAY_SIZE(roles); i++)
        if (!strcmp(roles[i], str))
        {
            ret = i;
            break;
        }

    free(str);
    return ret;
}