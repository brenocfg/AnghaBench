#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  dents_i; int /*<<< orphan*/  dents; } ;
typedef  TYPE_1__ ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_hash_table_lookup_extended (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_hash_table_steal (int /*<<< orphan*/ ,char const*) ; 
 char* g_utf8_strdown (char const*,int) ; 

__attribute__((used)) static void
remove_dent_from_dir (ChangeSetDir *dir, const char *dname)
{
    char *key;

    if (g_hash_table_lookup_extended (dir->dents, dname,
                                      (gpointer*)&key, NULL)) {
        g_hash_table_steal (dir->dents, dname);
        g_free (key);
    }
#if defined WIN32 || defined __APPLE__
    char *dname_i = g_utf8_strdown (dname, -1);
    g_hash_table_remove (dir->dents_i, dname_i);
    g_free (dname_i);
#endif
}