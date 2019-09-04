#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  TYPE_1__ DMO_PARTIAL_MEDIATYPE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GUIDToString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int MSDMO_MAJOR_VERSION ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static HRESULT write_types(HKEY hkey, LPCWSTR name, const DMO_PARTIAL_MEDIATYPE* types, DWORD count)
{
    LONG ret;

    if (MSDMO_MAJOR_VERSION > 5)
    {
        ret = RegSetValueExW(hkey, name, 0, REG_BINARY, (const BYTE*) types,
                          count* sizeof(DMO_PARTIAL_MEDIATYPE));
    }
    else
    {
        HKEY skey1,skey2,skey3;
        DWORD index = 0;
        WCHAR szGuidKey[64];

        ret = RegCreateKeyExW(hkey, name, 0, NULL, REG_OPTION_NON_VOLATILE,
                               KEY_WRITE, NULL, &skey1, NULL);
        if (ret)
            return HRESULT_FROM_WIN32(ret);

        while (index < count)
        {
            GUIDToString(szGuidKey,&types[index].type);
            ret = RegCreateKeyExW(skey1, szGuidKey, 0, NULL,
                        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &skey2, NULL);
            GUIDToString(szGuidKey,&types[index].subtype);
            ret = RegCreateKeyExW(skey2, szGuidKey, 0, NULL,
                        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &skey3, NULL);
            RegCloseKey(skey3);
            RegCloseKey(skey2);
            index ++;
        }
        RegCloseKey(skey1);
    }

    return HRESULT_FROM_WIN32(ret);
}