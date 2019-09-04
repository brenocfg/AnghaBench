#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  product ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int GUID_SIZE ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 int /*<<< orphan*/  INSTALLPROPERTY_LANGUAGEW ; 
 int /*<<< orphan*/  INSTALLPROPERTY_VERSIONW ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERMANAGED ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 scalar_t__ MSIREG_OpenProductKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MSIREG_OpenUpgradeCodesKey (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MSI_RecordGetInteger (TYPE_1__*,int) ; 
 scalar_t__ MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int SQUASHED_GUID_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  append_productcode (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_language (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_version_str_to_dword (scalar_t__) ; 
 scalar_t__ msidbUpgradeAttributesVersionMaxInclusive ; 
 scalar_t__ msidbUpgradeAttributesVersionMinInclusive ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsquash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ITERATE_FindRelatedProducts(MSIRECORD *rec, LPVOID param)
{
    MSIPACKAGE *package = param;
    WCHAR product[SQUASHED_GUID_SIZE];
    DWORD index = 0, attributes = 0, sz = sizeof(product)/sizeof(product[0]);
    LPCWSTR upgrade_code;
    HKEY hkey = 0;
    UINT rc = ERROR_SUCCESS;
    MSIRECORD *uirow;

    upgrade_code = MSI_RecordGetString(rec,1);

    rc = MSIREG_OpenUpgradeCodesKey(upgrade_code, &hkey, FALSE);
    if (rc != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    uirow = MSI_CreateRecord(1);
    attributes = MSI_RecordGetInteger(rec,5);

    while (rc == ERROR_SUCCESS)
    {
        rc = RegEnumValueW(hkey, index, product, &sz, NULL, NULL, NULL, NULL);
        if (rc == ERROR_SUCCESS)
        {
            WCHAR productid[GUID_SIZE];
            LPCWSTR ver, language, action_property;
            DWORD check = 0, comp_ver, sz = 0x100;
            HKEY hukey;
            INT r;

            TRACE("Looking at index %u product %s\n", index, debugstr_w(product));

            unsquash_guid(product, productid);
            if (MSIREG_OpenProductKey(productid, NULL, MSIINSTALLCONTEXT_USERMANAGED, &hukey, FALSE) &&
                MSIREG_OpenProductKey(productid, NULL, MSIINSTALLCONTEXT_USERUNMANAGED, &hukey, FALSE) &&
                MSIREG_OpenProductKey(productid, NULL, MSIINSTALLCONTEXT_MACHINE, &hukey, FALSE))
            {
                TRACE("product key not found\n");
                rc = ERROR_SUCCESS;
                index ++;
                continue;
            }

            sz = sizeof(DWORD);
            RegQueryValueExW(hukey, INSTALLPROPERTY_VERSIONW, NULL, NULL, (LPBYTE)&check, &sz);

            /* check version minimum */
            ver = MSI_RecordGetString(rec,2);
            if (ver)
            {
                comp_ver = msi_version_str_to_dword(ver);
                r = check - comp_ver;
                if (r < 0 || (r == 0 && !(attributes & msidbUpgradeAttributesVersionMinInclusive)))
                {
                    TRACE("version below minimum\n");
                    RegCloseKey(hukey);
                    index ++;
                    continue;
                }
            }

            /* check version maximum */
            ver = MSI_RecordGetString(rec,3);
            if (ver)
            {
                comp_ver = msi_version_str_to_dword(ver);
                r = check - comp_ver;
                if (r > 0 || (r == 0 && !(attributes & msidbUpgradeAttributesVersionMaxInclusive)))
                {
                    RegCloseKey(hukey);
                    index ++;
                    continue;
                }
                TRACE("version above maximum\n");
            }

            /* check language */
            sz = sizeof(DWORD);
            RegQueryValueExW(hukey, INSTALLPROPERTY_LANGUAGEW, NULL, NULL, (LPBYTE)&check, &sz);
            RegCloseKey(hukey);
            language = MSI_RecordGetString(rec,4);
            if (!check_language(check, language, attributes))
            {
                index ++;
                TRACE("language doesn't match\n");
                continue;
            }
            TRACE("found related product\n");

            action_property = MSI_RecordGetString(rec, 7);
            append_productcode(package, action_property, productid);
            MSI_RecordSetStringW(uirow, 1, productid);
            MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
        }
        index ++;
    }
    RegCloseKey(hkey);
    msiobj_release( &uirow->hdr);
    
    return ERROR_SUCCESS;
}