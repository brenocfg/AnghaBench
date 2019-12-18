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
 scalar_t__ strlen (char const*) ; 
 char* vlc_obj_memdup (int /*<<< orphan*/ *,char const*,scalar_t__) ; 

char *vlc_obj_strdup(vlc_object_t *obj, const char *str)
{
    return vlc_obj_memdup(obj, str, strlen(str) + 1);
}