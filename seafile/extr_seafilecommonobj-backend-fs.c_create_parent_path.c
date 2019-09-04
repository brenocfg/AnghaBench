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
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_mkdir_with_parents (char*,int) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
create_parent_path (const char *path)
{
    char *dir = g_path_get_dirname (path);
    if (!dir)
        return -1;

    if (g_file_test (dir, G_FILE_TEST_EXISTS)) {
        g_free (dir);
        return 0;
    }

    if (g_mkdir_with_parents (dir, 0777) < 0) {
        seaf_warning ("Failed to create object parent path %s: %s.\n",
                      dir, strerror(errno));
        g_free (dir);
        return -1;
    }

    g_free (dir);
    return 0;
}