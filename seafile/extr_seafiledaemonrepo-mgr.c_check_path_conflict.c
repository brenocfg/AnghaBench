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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  conflict_pattern ; 
 scalar_t__ g_regex_match (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_regex_replace_literal (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static gboolean
check_path_conflict (const char *path, char **orig_path)
{
    gboolean is_conflict = FALSE;
    GError *error = NULL;

    is_conflict = g_regex_match (conflict_pattern, path, 0, NULL);
    if (is_conflict) {
        *orig_path = g_regex_replace_literal (conflict_pattern, path, -1,
                                              0, "", 0, &error);
        if (!*orig_path)
            is_conflict = FALSE;
    }

    return is_conflict;
}