#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  dents ;
struct TYPE_12__ {struct TYPE_12__* next; TYPE_1__* data; } ;
struct TYPE_11__ {TYPE_3__* entries; } ;
struct TYPE_10__ {char* name; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  DiffOptions ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int diff_directories (int,TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int diff_files (int,TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ dirent_same (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
diff_trees_recursive (int n, SeafDir *trees[],
                      const char *basedir, DiffOptions *opt)
{
    GList *ptrs[3];
    SeafDirent *dents[3];
    int i;
    SeafDirent *dent;
    char *first_name;
    gboolean done;
    int ret = 0;

    for (i = 0; i < n; ++i) {
        if (trees[i])
            ptrs[i] = trees[i]->entries;
        else
            ptrs[i] = NULL;
    }

    while (1) {
        first_name = NULL;
        memset (dents, 0, sizeof(dents[0])*n);
        done = TRUE;

        /* Find the "largest" name, assuming dirents are sorted. */
        for (i = 0; i < n; ++i) {
            if (ptrs[i] != NULL) {
                done = FALSE;
                dent = ptrs[i]->data;
                if (!first_name)
                    first_name = dent->name;
                else if (strcmp(dent->name, first_name) > 0)
                    first_name = dent->name;
            }
        }

        if (done)
            break;

        /*
         * Setup dir entries for all names that equal to first_name
         */
        for (i = 0; i < n; ++i) {
            if (ptrs[i] != NULL) {
                dent = ptrs[i]->data;
                if (strcmp(first_name, dent->name) == 0) {
                    dents[i] = dent;
                    ptrs[i] = ptrs[i]->next;
                }
            }
        }

        if (n == 2 && dents[0] && dents[1] && dirent_same(dents[0], dents[1]))
            continue;

        if (n == 3 && dents[0] && dents[1] && dents[2] &&
            dirent_same(dents[0], dents[1]) && dirent_same(dents[0], dents[2]))
            continue;

        /* Diff files of this level. */
        ret = diff_files (n, dents, basedir, opt);
        if (ret < 0)
            return ret;

        /* Recurse into sub level. */
        ret = diff_directories (n, dents, basedir, opt);
        if (ret < 0)
            return ret;
    }

    return ret;
}