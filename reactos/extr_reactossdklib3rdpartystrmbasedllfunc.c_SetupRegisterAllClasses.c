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
struct TYPE_3__ {int /*<<< orphan*/  m_Name; int /*<<< orphan*/  m_ClsID; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_1__ FactoryTemplate ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int /*<<< orphan*/  NOERROR ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteTreeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupRegisterClass (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clsid_keyname ; 
 int /*<<< orphan*/  ips32_keyname ; 
 int /*<<< orphan*/  tmodel_both ; 

__attribute__((used)) static HRESULT SetupRegisterAllClasses(const FactoryTemplate * pList, int num,
                                       LPCWSTR szFileName, BOOL bRegister)
{
    HRESULT hr = NOERROR;
    HKEY hkey;
    OLECHAR szCLSID[CHARS_IN_GUID];
    LONG i, ret = RegCreateKeyW(HKEY_CLASSES_ROOT, clsid_keyname, &hkey);
    if (ERROR_SUCCESS != ret)
        return HRESULT_FROM_WIN32(ret);

    for (i = 0; i < num; i++, pList++)
    {
        /* (un)register CLSID and InprocServer32 */
        hr = StringFromGUID2(pList->m_ClsID, szCLSID, CHARS_IN_GUID);
        if (SUCCEEDED(hr))
        {
            if (bRegister )
                hr = SetupRegisterClass(hkey, szCLSID,
                                        pList->m_Name, szFileName,
                                        ips32_keyname, tmodel_both);
            else
                hr = RegDeleteTreeW(hkey, szCLSID);
        }
    }
    RegCloseKey(hkey);
    return hr;
}