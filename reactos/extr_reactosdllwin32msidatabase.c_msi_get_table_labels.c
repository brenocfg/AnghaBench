#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_DatabaseGetPrimaryKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT msi_get_table_labels(MSIDATABASE *db, LPCWSTR table, LPWSTR **labels, DWORD *numlabels)
{
    UINT r, i, count;
    MSIRECORD *prec = NULL;

    r = MSI_DatabaseGetPrimaryKeys(db, table, &prec);
    if (r != ERROR_SUCCESS)
        return r;

    count = MSI_RecordGetFieldCount(prec);
    *numlabels = count + 1;
    *labels = msi_alloc((*numlabels)*sizeof(LPWSTR));
    if (!*labels)
    {
        r = ERROR_OUTOFMEMORY;
        goto end;
    }

    (*labels)[0] = strdupW(table);
    for (i=1; i<=count; i++ )
    {
        (*labels)[i] = strdupW(MSI_RecordGetString(prec, i));
    }

end:
    msiobj_release( &prec->hdr );
    return r;
}