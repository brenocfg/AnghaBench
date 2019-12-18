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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  int /*<<< orphan*/  ICreateDevEnum ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC ; 
 int /*<<< orphan*/  CLSID_AudioRendererCategory ; 
 int /*<<< orphan*/  CLSID_LegacyAmFilterCategory ; 
 int /*<<< orphan*/  CLSID_SystemDeviceEnum ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ ICreateDevEnum_CreateClassEnumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICreateDevEnum_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumMoniker_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ICreateDevEnum ; 
 scalar_t__ IMoniker_IsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*,...) ; 

__attribute__((used)) static void test_moniker_isequal(void)
{
    HRESULT res;
    ICreateDevEnum *create_devenum = NULL;
    IEnumMoniker *enum_moniker0 = NULL, *enum_moniker1 = NULL;
    IMoniker *moniker0 = NULL, *moniker1 = NULL;

    res = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           &IID_ICreateDevEnum, (LPVOID*)&create_devenum);
    if (FAILED(res))
    {
         skip("Cannot create SystemDeviceEnum object (%x)\n", res);
         return;
    }

    res = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_LegacyAmFilterCategory, &enum_moniker0, 0);
    ok(SUCCEEDED(res), "Cannot create enum moniker (res = %x)\n", res);
    if (SUCCEEDED(res))
    {
        if (IEnumMoniker_Next(enum_moniker0, 1, &moniker0, NULL) == S_OK &&
            IEnumMoniker_Next(enum_moniker0, 1, &moniker1, NULL) == S_OK)
        {
            res = IMoniker_IsEqual(moniker0, moniker1);
            ok(res == S_FALSE, "IMoniker_IsEqual should fail (res = %x)\n", res);

            res = IMoniker_IsEqual(moniker1, moniker0);
            ok(res == S_FALSE, "IMoniker_IsEqual should fail (res = %x)\n", res);

            IMoniker_Release(moniker0);
            IMoniker_Release(moniker1);
        }
        else
            skip("Cannot get moniker for testing.\n");
    }
    IEnumMoniker_Release(enum_moniker0);

    res = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_LegacyAmFilterCategory, &enum_moniker0, 0);
    ok(SUCCEEDED(res), "Cannot create enum moniker (res = %x)\n", res);
    res = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_AudioRendererCategory, &enum_moniker1, 0);
    ok(SUCCEEDED(res), "Cannot create enum moniker (res = %x)\n", res);
    if (SUCCEEDED(res))
    {
        if (IEnumMoniker_Next(enum_moniker0, 1, &moniker0, NULL) == S_OK &&
            IEnumMoniker_Next(enum_moniker1, 1, &moniker1, NULL) == S_OK)
        {
            res = IMoniker_IsEqual(moniker0, moniker1);
            ok(res == S_FALSE, "IMoniker_IsEqual should failed (res = %x)\n", res);

            res = IMoniker_IsEqual(moniker1, moniker0);
            ok(res == S_FALSE, "IMoniker_IsEqual should failed (res = %x)\n", res);

            IMoniker_Release(moniker0);
            IMoniker_Release(moniker1);
        }
        else
            skip("Cannot get moniker for testing.\n");
    }
    IEnumMoniker_Release(enum_moniker0);
    IEnumMoniker_Release(enum_moniker1);

    res = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_LegacyAmFilterCategory, &enum_moniker0, 0);
    ok(SUCCEEDED(res), "Cannot create enum moniker (res = %x)\n", res);
    res = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_LegacyAmFilterCategory, &enum_moniker1, 0);
    ok(SUCCEEDED(res), "Cannot create enum moniker (res = %x)\n", res);
    if (SUCCEEDED(res))
    {
        if (IEnumMoniker_Next(enum_moniker0, 1, &moniker0, NULL) == S_OK &&
            IEnumMoniker_Next(enum_moniker1, 1, &moniker1, NULL) == S_OK)
        {
            res = IMoniker_IsEqual(moniker0, moniker1);
            ok(res == S_OK, "IMoniker_IsEqual failed (res = %x)\n", res);

            res = IMoniker_IsEqual(moniker1, moniker0);
            ok(res == S_OK, "IMoniker_IsEqual failed (res = %x)\n", res);

            IMoniker_Release(moniker0);
            IMoniker_Release(moniker1);
        }
        else
            skip("Cannot get moniker for testing.\n");
    }
    IEnumMoniker_Release(enum_moniker0);
    IEnumMoniker_Release(enum_moniker1);

    ICreateDevEnum_Release(create_devenum);

    return;
}