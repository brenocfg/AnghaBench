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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  checked_objs; int /*<<< orphan*/ ** pret; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_2__ CalcFsListData ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
collect_dir_ids (int n, const char *basedir, SeafDirent *dirs[], void *vdata,
                 gboolean *recurse)
{
    SeafDirent *dir1 = dirs[0];
    SeafDirent *dir2 = dirs[1];
    CalcFsListData *data = vdata;
    GList **pret = data->pret;
    int dummy;

    if (!dir1 || strcmp (dir1->id, EMPTY_SHA1) == 0)
        return 0;

    if (g_hash_table_lookup (data->checked_objs, dir1->id))
        return 0;

    if (!dir2 || strcmp (dir1->id, dir2->id) != 0) {
        *pret = g_list_prepend (*pret, g_strdup(dir1->id));
        g_hash_table_insert (data->checked_objs, g_strdup(dir1->id), &dummy);
    }

    return 0;
}