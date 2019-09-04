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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  should_ignore (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
is_empty_dir (const char *path, GList *ignore_list)
{
    GDir *dir;
    const char *dname;
    gboolean ret = TRUE;

    dir = g_dir_open (path, 0, NULL);
    if (!dir) {
        return FALSE;
    }

    while ((dname = g_dir_read_name(dir)) != NULL) {
        if (!should_ignore(path, dname, ignore_list)) {
            ret = FALSE;
            break;
        }
    }
    g_dir_close (dir);

    return ret;
}