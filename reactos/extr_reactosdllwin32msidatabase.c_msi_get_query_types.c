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
typedef  int /*<<< orphan*/  MSIQUERY ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,scalar_t__) ; 
 scalar_t__ MSI_ViewGetColumnInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * msi_alloc (scalar_t__) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT msi_get_query_types(MSIQUERY *query, LPWSTR **types, DWORD *numtypes)
{
    UINT r, i, count;
    MSIRECORD *prec = NULL;

    r = MSI_ViewGetColumnInfo(query, MSICOLINFO_TYPES, &prec);
    if (r != ERROR_SUCCESS)
        return r;

    count = MSI_RecordGetFieldCount(prec);
    *types = msi_alloc(count*sizeof(LPWSTR));
    if (!*types)
    {
        r = ERROR_OUTOFMEMORY;
        goto end;
    }

    *numtypes = count;
    for (i=1; i<=count; i++ )
    {
        (*types)[i-1] = strdupW(MSI_RecordGetString(prec, i));
    }

end:
    msiobj_release( &prec->hdr );
    return r;
}