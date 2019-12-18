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
typedef  int gboolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ is_empty_string (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

gboolean
is_permission_valid (const char *perm)
{
    if (is_empty_string (perm)) {
        return FALSE;
    }

    return strcmp (perm, "r") == 0 || strcmp (perm, "rw") == 0;
}