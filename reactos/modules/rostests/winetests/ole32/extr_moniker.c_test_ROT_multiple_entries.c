#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  char const IRunningObjectTable ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CreateFileMoniker (char const*,scalar_t__) ; 
 scalar_t__ GetRunningObjectTable (char const*,scalar_t__) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IRunningObjectTable_GetObject (char const*,scalar_t__,...) ; 
 scalar_t__ IRunningObjectTable_Register (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IRunningObjectTable_Release (char const*) ; 
 scalar_t__ IRunningObjectTable_Revoke (char const*,scalar_t__) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MK_S_MONIKERALREADYREGISTERED ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,...) ; 

__attribute__((used)) static void test_ROT_multiple_entries(void)
{
    HRESULT hr;
    IMoniker *pMoniker = NULL;
    IRunningObjectTable *pROT = NULL;
    DWORD dwCookie1, dwCookie2;
    IUnknown *pObject = NULL;
    static const WCHAR moniker_path[] =
        {'\\', 'w','i','n','d','o','w','s','\\','s','y','s','t','e','m','\\','t','e','s','t','1','.','d','o','c',0};

    hr = GetRunningObjectTable(0, &pROT);
    ok_ole_success(hr, GetRunningObjectTable);

    hr = CreateFileMoniker(moniker_path, &pMoniker);
    ok_ole_success(hr, CreateFileMoniker);

    hr = IRunningObjectTable_Register(pROT, 0, (IUnknown *)&Test_ClassFactory, pMoniker, &dwCookie1);
    ok_ole_success(hr, IRunningObjectTable_Register);

    hr = IRunningObjectTable_Register(pROT, 0, (IUnknown *)&Test_ClassFactory, pMoniker, &dwCookie2);
    ok(hr == MK_S_MONIKERALREADYREGISTERED, "IRunningObjectTable_Register should have returned MK_S_MONIKERALREADYREGISTERED instead of 0x%08x\n", hr);

    ok(dwCookie1 != dwCookie2, "cookie returned for registering duplicate object shouldn't match cookie of original object (0x%x)\n", dwCookie1);

    hr = IRunningObjectTable_GetObject(pROT, pMoniker, &pObject);
    ok_ole_success(hr, IRunningObjectTable_GetObject);
    IUnknown_Release(pObject);

    hr = IRunningObjectTable_Revoke(pROT, dwCookie1);
    ok_ole_success(hr, IRunningObjectTable_Revoke);

    hr = IRunningObjectTable_GetObject(pROT, pMoniker, &pObject);
    ok_ole_success(hr, IRunningObjectTable_GetObject);
    IUnknown_Release(pObject);

    hr = IRunningObjectTable_Revoke(pROT, dwCookie2);
    ok_ole_success(hr, IRunningObjectTable_Revoke);

    IMoniker_Release(pMoniker);

    IRunningObjectTable_Release(pROT);
}