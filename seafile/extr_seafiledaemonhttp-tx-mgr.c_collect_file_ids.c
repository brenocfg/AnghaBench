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
collect_file_ids (int n, const char *basedir, SeafDirent *files[], void *vdata)
{
    SeafDirent *file1 = files[0];
    SeafDirent *file2 = files[1];
    CalcFsListData *data = vdata;
    GList **pret = data->pret;
    int dummy;

    if (!file1 || strcmp (file1->id, EMPTY_SHA1) == 0)
        return 0;

    if (g_hash_table_lookup (data->checked_objs, file1->id))
        return 0;

    if (!file2 || strcmp (file1->id, file2->id) != 0) {
        *pret = g_list_prepend (*pret, g_strdup(file1->id));
        g_hash_table_insert (data->checked_objs, g_strdup(file1->id), &dummy);
    }

    return 0;
}