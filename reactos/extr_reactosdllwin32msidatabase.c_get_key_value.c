#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIQUERY ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 scalar_t__ MSI_RecordGetString (TYPE_1__*,scalar_t__) ; 
 scalar_t__ MSI_RecordGetStringW (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ MSI_ViewGetColumnInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * msi_alloc (scalar_t__) ; 
 int /*<<< orphan*/ * msi_dup_record_field (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPWSTR get_key_value(MSIQUERY *view, LPCWSTR key, MSIRECORD *rec)
{
    MSIRECORD *colnames;
    LPWSTR str, val;
    UINT r, i = 0, sz = 0;
    int cmp;

    r = MSI_ViewGetColumnInfo(view, MSICOLINFO_NAMES, &colnames);
    if (r != ERROR_SUCCESS)
        return NULL;

    do
    {
        str = msi_dup_record_field(colnames, ++i);
        cmp = strcmpW( key, str );
        msi_free(str);
    } while (cmp);

    msiobj_release(&colnames->hdr);

    r = MSI_RecordGetStringW(rec, i, NULL, &sz);
    if (r != ERROR_SUCCESS)
        return NULL;
    sz++;

    if (MSI_RecordGetString(rec, i))  /* check record field is a string */
    {
        /* quote string record fields */
        const WCHAR szQuote[] = {'\'', 0};
        sz += 2;
        val = msi_alloc(sz*sizeof(WCHAR));
        if (!val)
            return NULL;

        lstrcpyW(val, szQuote);
        r = MSI_RecordGetStringW(rec, i, val+1, &sz);
        lstrcpyW(val+1+sz, szQuote);
    }
    else
    {
        /* do not quote integer record fields */
        val = msi_alloc(sz*sizeof(WCHAR));
        if (!val)
            return NULL;

        r = MSI_RecordGetStringW(rec, i, val, &sz);
    }

    if (r != ERROR_SUCCESS)
    {
        ERR("failed to get string!\n");
        msi_free(val);
        return NULL;
    }

    return val;
}