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
typedef  char gchar ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_key_file_get_string (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_has_key (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 

gchar* 
ccnet_key_file_get_string (GKeyFile *keyf,
                           const char *category,
                           const char *key)
{
    gchar *v;

    if (!g_key_file_has_key (keyf, category, key, NULL))
        return NULL;

    v = g_key_file_get_string (keyf, category, key, NULL);
    if (v != NULL && v[0] == '\0') {
        g_free(v);
        return NULL;
    }

    return v;
}