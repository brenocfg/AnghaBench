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

/* Variables and functions */
 char* g_strndup (char const*,int) ; 
 char* strchr (char const*,char) ; 

char*
ccnet_object_type_from_id (const char *object_id)
{
    char *ptr;

    if ( !(ptr = strchr(object_id, '/')) )
        return NULL;

    return g_strndup(object_id, ptr - object_id);
}