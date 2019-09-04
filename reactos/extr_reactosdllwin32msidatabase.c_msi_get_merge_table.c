#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {scalar_t__ numconflicts; int /*<<< orphan*/  name; int /*<<< orphan*/  rows; int /*<<< orphan*/  numtypes; int /*<<< orphan*/  types; int /*<<< orphan*/  numcolumns; int /*<<< orphan*/  columns; int /*<<< orphan*/  numlabels; int /*<<< orphan*/  labels; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  TYPE_2__ MERGETABLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ *,TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_merge_table (TYPE_2__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 scalar_t__ msi_get_query_columns (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ msi_get_query_types (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ msi_get_table_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT msi_get_merge_table (MSIDATABASE *db, LPCWSTR name, MERGETABLE **ptable)
{
    UINT r;
    MERGETABLE *table;
    MSIQUERY *mergeview = NULL;

    static const WCHAR query[] = {'S','E','L','E','C','T',' ','*',' ',
        'F','R','O','M',' ','`','%','s','`',0};

    table = msi_alloc_zero(sizeof(MERGETABLE));
    if (!table)
    {
       *ptable = NULL;
       return ERROR_OUTOFMEMORY;
    }

    r = msi_get_table_labels(db, name, &table->labels, &table->numlabels);
    if (r != ERROR_SUCCESS)
        goto err;

    r = MSI_OpenQuery(db, &mergeview, query, name);
    if (r != ERROR_SUCCESS)
        goto err;

    r = msi_get_query_columns(mergeview, &table->columns, &table->numcolumns);
    if (r != ERROR_SUCCESS)
        goto err;

    r = msi_get_query_types(mergeview, &table->types, &table->numtypes);
    if (r != ERROR_SUCCESS)
        goto err;

    list_init(&table->rows);

    table->name = strdupW(name);
    table->numconflicts = 0;

    msiobj_release(&mergeview->hdr);
    *ptable = table;
    return ERROR_SUCCESS;

err:
    msiobj_release(&mergeview->hdr);
    free_merge_table(table);
    *ptable = NULL;
    return r;
}