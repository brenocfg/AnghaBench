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
typedef  void* gpointer ;

/* Variables and functions */
 int KEY_MAX ; 
 int str2key (char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
ghash_to_value(gpointer key, gpointer value, gpointer user_data)
{
    const char **ppsz_values = user_data;

    const char *psz_key = key;
    int i_key = str2key(psz_key);
    if (i_key == -1 || i_key >= KEY_MAX)
        return;

    ppsz_values[i_key] = strdup((const char *)value);
}