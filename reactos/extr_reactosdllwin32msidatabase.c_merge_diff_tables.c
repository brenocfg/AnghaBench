#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  tabledata; TYPE_1__* curview; TYPE_2__* curtable; int /*<<< orphan*/  merge; int /*<<< orphan*/  db; } ;
struct TYPE_14__ {int /*<<< orphan*/  entry; } ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIQUERY ;
typedef  TYPE_2__ MERGETABLE ;
typedef  TYPE_3__ MERGEDATA ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_IterateRecords (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TABLE_Exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_merge_table (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_diff_row ; 
 scalar_t__ merge_verify_colnames (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ merge_verify_primary_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_get_merge_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT merge_diff_tables(MSIRECORD *rec, LPVOID param)
{
    MERGEDATA *data = param;
    MERGETABLE *table;
    MSIQUERY *dbview = NULL;
    MSIQUERY *mergeview = NULL;
    LPCWSTR name;
    UINT r;

    static const WCHAR query[] = {'S','E','L','E','C','T',' ','*',' ',
        'F','R','O','M',' ','`','%','s','`',0};

    name = MSI_RecordGetString(rec, 1);

    r = MSI_OpenQuery(data->merge, &mergeview, query, name);
    if (r != ERROR_SUCCESS)
        goto done;

    if (TABLE_Exists(data->db, name))
    {
        r = MSI_OpenQuery(data->db, &dbview, query, name);
        if (r != ERROR_SUCCESS)
            goto done;

        r = merge_verify_colnames(dbview, mergeview);
        if (r != ERROR_SUCCESS)
            goto done;

        r = merge_verify_primary_keys(data->db, data->merge, name);
        if (r != ERROR_SUCCESS)
            goto done;
    }

    r = msi_get_merge_table(data->merge, name, &table);
    if (r != ERROR_SUCCESS)
        goto done;

    data->curtable = table;
    data->curview = mergeview;
    r = MSI_IterateRecords(mergeview, NULL, merge_diff_row, data);
    if (r != ERROR_SUCCESS)
    {
        free_merge_table(table);
        goto done;
    }

    list_add_tail(data->tabledata, &table->entry);

done:
    msiobj_release(&dbview->hdr);
    msiobj_release(&mergeview->hdr);
    return r;
}