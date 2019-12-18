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
typedef  int /*<<< orphan*/  vlc_action_id_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ KEY_UNSET ; 
 scalar_t__ add_mapping (void**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ vlc_str2keycode (char*) ; 

__attribute__((used)) static void init_action (vlc_object_t *obj, void **map,
                            const char *confname, vlc_action_id_t action)
{
    char *keys = var_InheritString (obj, confname);
    if (keys == NULL)
        return;

    for (char *buf, *key = strtok_r (keys, "\t", &buf);
         key != NULL;
         key = strtok_r (NULL, "\t", &buf))
    {
        uint32_t code = vlc_str2keycode (key);
        if (code == KEY_UNSET)
        {
            msg_Warn (obj, "Key \"%s\" unrecognized", key);
            continue;
        }

        if (add_mapping (map, code, action) == EEXIST)
            msg_Warn (obj, "Key \"%s\" bound to multiple actions", key);
    }
    free (keys);
}