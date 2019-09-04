#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ MSISIGNATURE ;
typedef  TYPE_2__ MSIRECORD ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SearchDirectory (TYPE_3__*,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetPrivateProfileStringW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MSI_NULL_INTEGER ; 
 TYPE_2__* MSI_QueryGetRecord (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int MSI_RecordGetInteger (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * app_search_file (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_ini_field (char*,int) ; 
 int /*<<< orphan*/ * msi_dup_record_field (TYPE_2__*,int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
#define  msidbLocatorTypeDirectory 130 
#define  msidbLocatorTypeFileName 129 
#define  msidbLocatorTypeRawValue 128 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ACTION_AppSearchIni(MSIPACKAGE *package, LPWSTR *appValue,
 MSISIGNATURE *sig)
{
    static const WCHAR query[] =  {
        's','e','l','e','c','t',' ','*',' ',
        'f','r','o','m',' ',
        'I','n','i','L','o','c','a','t','o','r',' ',
        'w','h','e','r','e',' ',
        'S','i','g','n','a','t','u','r','e','_',' ','=',' ','\'','%','s','\'',0};
    MSIRECORD *row;
    LPWSTR fileName, section, key;
    int field, type;
    WCHAR buf[MAX_PATH];

    TRACE("%s\n", debugstr_w(sig->Name));

    *appValue = NULL;

    row = MSI_QueryGetRecord( package->db, query, sig->Name );
    if (!row)
    {
        TRACE("failed to query IniLocator for %s\n", debugstr_w(sig->Name));
        return ERROR_SUCCESS;
    }

    fileName = msi_dup_record_field(row, 2);
    section = msi_dup_record_field(row, 3);
    key = msi_dup_record_field(row, 4);
    field = MSI_RecordGetInteger(row, 5);
    type = MSI_RecordGetInteger(row, 6);
    if (field == MSI_NULL_INTEGER)
        field = 0;
    if (type == MSI_NULL_INTEGER)
        type = 0;

    GetPrivateProfileStringW(section, key, NULL, buf, MAX_PATH, fileName);
    if (buf[0])
    {
        switch (type & 0x0f)
        {
        case msidbLocatorTypeDirectory:
            ACTION_SearchDirectory(package, sig, buf, 0, appValue);
            break;
        case msidbLocatorTypeFileName:
            *appValue = app_search_file(buf, sig);
            break;
        case msidbLocatorTypeRawValue:
            *appValue = get_ini_field(buf, field);
            break;
        }
    }

    msi_free(fileName);
    msi_free(section);
    msi_free(key);

    msiobj_release(&row->hdr);

    return ERROR_SUCCESS;
}