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
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/ * index_name_exists (struct index_state*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_file_from_index (struct index_state*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 

void remove_empty_parent_dir_entry (struct index_state *istate, const char *path)
{
    char *parent = g_strdup(path);
    char *slash;

    /* Find and remove empty dir entry from low level to top level. */
    while (1) {
        slash = strrchr (parent, '/');
        if (!slash)
            break;

        *slash = 0;

        if (index_name_exists (istate, parent, strlen(parent), 0) != NULL) {
            remove_file_from_index (istate, parent);
            break;
        }
    }

    g_free (parent);
}