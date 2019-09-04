#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_2__* data; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  GString ;
typedef  TYPE_1__ GList ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
#define  DIFF_STATUS_ADDED 134 
#define  DIFF_STATUS_DELETED 133 
#define  DIFF_STATUS_DIR_ADDED 132 
#define  DIFF_STATUS_DIR_DELETED 131 
#define  DIFF_STATUS_DIR_RENAMED 130 
#define  DIFF_STATUS_MODIFIED 129 
#define  DIFF_STATUS_RENAMED 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 char* get_basename (int /*<<< orphan*/ ) ; 

char *
diff_results_to_description (GList *results)
{
    GList *p;
    DiffEntry *de;
    char *add_mod_file = NULL, *removed_file = NULL;
    char *renamed_file = NULL, *renamed_dir = NULL;
    char *new_dir = NULL, *removed_dir = NULL;
    int n_add_mod = 0, n_removed = 0, n_renamed = 0;
    int n_new_dir = 0, n_removed_dir = 0, n_renamed_dir = 0;
    GString *desc;

    if (results == NULL)
        return NULL;

    for (p = results; p != NULL; p = p->next) {
        de = p->data;
        switch (de->status) {
        case DIFF_STATUS_ADDED:
            if (n_add_mod == 0)
                add_mod_file = get_basename(de->name);
            n_add_mod++;
            break;
        case DIFF_STATUS_DELETED:
            if (n_removed == 0)
                removed_file = get_basename(de->name);
            n_removed++;
            break;
        case DIFF_STATUS_RENAMED:
            if (n_renamed == 0)
                renamed_file = get_basename(de->name);
            n_renamed++;
            break;
        case DIFF_STATUS_DIR_RENAMED:
            if (n_renamed_dir == 0)
                renamed_dir = get_basename(de->name);
            n_renamed_dir++;
            break;
        case DIFF_STATUS_MODIFIED:
            if (n_add_mod == 0)
                add_mod_file = get_basename(de->name);
            n_add_mod++;
            break;
        case DIFF_STATUS_DIR_ADDED:
            if (n_new_dir == 0)
                new_dir = get_basename(de->name);
            n_new_dir++;
            break;
        case DIFF_STATUS_DIR_DELETED:
            if (n_removed_dir == 0)
                removed_dir = get_basename(de->name);
            n_removed_dir++;
            break;
        }
    }

    desc = g_string_new ("");

    if (n_add_mod == 1)
        g_string_append_printf (desc, "Added or modified \"%s\".\n", add_mod_file);
    else if (n_add_mod > 1)
        g_string_append_printf (desc, "Added or modified \"%s\" and %d more files.\n",
                                add_mod_file, n_add_mod - 1);

    if (n_removed == 1)
        g_string_append_printf (desc, "Deleted \"%s\".\n", removed_file);
    else if (n_removed > 1)
        g_string_append_printf (desc, "Deleted \"%s\" and %d more files.\n",
                                removed_file, n_removed - 1);

    if (n_renamed == 1)
        g_string_append_printf (desc, "Renamed \"%s\".\n", renamed_file);
    else if (n_renamed > 1)
        g_string_append_printf (desc, "Renamed \"%s\" and %d more files.\n",
                                renamed_file, n_renamed - 1);

    if (n_renamed_dir == 1)
        g_string_append_printf (desc, "Renamed directory \"%s\".\n", renamed_dir);
    else if (n_renamed_dir > 1)
        g_string_append_printf (desc, "Renamed \"%s\" and %d more directories.\n",
                                renamed_dir, n_renamed_dir - 1);

    if (n_new_dir == 1)
        g_string_append_printf (desc, "Added directory \"%s\".\n", new_dir);
    else if (n_new_dir > 1)
        g_string_append_printf (desc, "Added \"%s\" and %d more directories.\n",
                                new_dir, n_new_dir - 1);

    if (n_removed_dir == 1)
        g_string_append_printf (desc, "Removed directory \"%s\".\n", removed_dir);
    else if (n_removed_dir > 1)
        g_string_append_printf (desc, "Removed \"%s\" and %d more directories.\n",
                                removed_dir, n_removed_dir - 1);

    return g_string_free (desc, FALSE);
}