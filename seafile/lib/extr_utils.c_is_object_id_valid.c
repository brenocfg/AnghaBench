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
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (char const*) ; 

gboolean
is_object_id_valid (const char *obj_id)
{
    if (!obj_id)
        return FALSE;

    int len = strlen(obj_id);
    int i;
    char c;

    if (len != 40)
        return FALSE;

    for (i = 0; i < len; ++i) {
        c = obj_id[i];
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
            continue;
        return FALSE;
    }

    return TRUE;
}