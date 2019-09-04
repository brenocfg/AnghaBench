#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  deleted_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ g_access (char*,int /*<<< orphan*/ ) ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char const*,int) ; 
 TYPE_1__* seaf ; 

__attribute__((used)) static char *
gen_deleted_store_path (const char *type, const char *repo_id)
{
    int n = 1;
    char *path = NULL;
    char *name = NULL;

    path = g_build_filename (seaf->deleted_store, type, repo_id, NULL);
    while (g_access(path, F_OK) == 0 && n < 10) {
        g_free (path);
        name = g_strdup_printf ("%s(%d)", repo_id, n);
        path = g_build_filename (seaf->deleted_store, type, name, NULL);
        g_free (name);
        ++n;
    }

    if (n == 10) {
        g_free (path);
        return NULL;
    }

    return path;
}