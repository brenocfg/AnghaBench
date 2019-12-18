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
struct TYPE_5__ {char* permission; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {TYPE_2__* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ GList ;
typedef  TYPE_2__ FolderPerm ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static char *
lookup_folder_perm (GList *perms, const char *path)
{
    GList *ptr;
    FolderPerm *perm;
    char *folder;
    int len;
    char *permission = NULL;

    for (ptr = perms; ptr; ptr = ptr->next) {
        perm = ptr->data;

        if (strcmp (perm->path, "/") != 0)
            folder = g_strconcat (perm->path, "/", NULL);
        else
            folder = g_strdup(perm->path);

        len = strlen(folder);
        if (strcmp (perm->path, path) == 0 || strncmp(folder, path, len) == 0) {
            permission = perm->permission;
            g_free (folder);
            break;
        }
        g_free (folder);
    }

    return permission;
}