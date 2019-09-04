#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_6__ {scalar_t__ data; struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  int /*<<< orphan*/  GPatternSpec ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_pattern_match_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_pattern_spec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_pattern_spec_new (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 int seaf_stat (char*,TYPE_1__*) ; 

gboolean
seaf_repo_check_ignore_file (GList *ignore_list, const char *fullpath)
{
    char *str;
    SeafStat st;
    GPatternSpec *ignore_spec;
    GList *p;

    str = g_strdup(fullpath);

    int rc = seaf_stat(str, &st);
    if (rc == 0 && S_ISDIR(st.st_mode)) {
        g_free (str);
        str = g_strconcat (fullpath, "/", NULL);
    }

    for (p = ignore_list; p != NULL; p = p->next) {
        char *pattern = (char *)p->data;

        ignore_spec = g_pattern_spec_new(pattern);
        if (g_pattern_match_string(ignore_spec, str)) {
            g_free (str);
            g_pattern_spec_free(ignore_spec);
            return TRUE;
        }
        g_pattern_spec_free(ignore_spec);
    }

    g_free (str);
    return FALSE;
}