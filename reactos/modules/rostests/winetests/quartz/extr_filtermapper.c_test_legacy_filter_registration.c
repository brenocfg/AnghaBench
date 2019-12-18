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
typedef  int /*<<< orphan*/  testfilterW ;
typedef  int /*<<< orphan*/  clsidstring ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Clsid; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ REGFILTER ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  IFilterMapper2 ;
typedef  int /*<<< orphan*/  IFilterMapper ;
typedef  int /*<<< orphan*/  IEnumRegFilters ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IEnumMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumRegFilters_Next (int /*<<< orphan*/ *,int,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumRegFilters_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper2_EnumMatchingFilters (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFilterMapper2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper_EnumMatchingFilters (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IFilterMapper_RegisterFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ IFilterMapper_RegisterPin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper_RegisterPinType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFilterMapper_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper_UnregisterFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IFilterMapper ; 
 int /*<<< orphan*/  IID_IFilterMapper2 ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  MERIT_UNLIKELY ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteKeyW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  enum_find_filter (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_legacy_filter_registration(void)
{
    static const WCHAR testfilterW[] = {'T','e','s','t','f','i','l','t','e','r',0};
    static const WCHAR clsidW[] = {'C','L','S','I','D','\\',0};
    static const WCHAR pinW[] = {'P','i','n','1',0};
    IEnumRegFilters *enum_reg;
    IEnumMoniker *enum_mon;
    IFilterMapper2 *mapper2;
    IFilterMapper *mapper;
    REGFILTER *regfilter;
    WCHAR clsidstring[40];
    WCHAR key_name[50];
    ULONG count;
    CLSID clsid;
    LRESULT ret;
    HRESULT hr;
    BOOL found;
    HKEY hkey;

    /* Register* functions need a filter class key to write pin and pin media
     * type data to. Create a bogus class key for it. */
    CoCreateGuid(&clsid);
    StringFromGUID2(&clsid, clsidstring, sizeof(clsidstring));
    lstrcpyW(key_name, clsidW);
    lstrcatW(key_name, clsidstring);
    ret = RegCreateKeyExW(HKEY_CLASSES_ROOT, key_name, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL);
    if (ret == ERROR_ACCESS_DENIED)
    {
        skip("Not authorized to register filters\n");
        return;
    }

    /* Test if legacy filter registration scheme works (filter is added to HKCR\Filter). IFilterMapper_RegisterFilter
     * registers in this way. Filters so registered must then be accessible through both IFilterMapper_EnumMatchingFilters
     * and IFilterMapper2_EnumMatchingFilters. */
    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER, &IID_IFilterMapper2, (void **)&mapper2);
    ok(hr == S_OK, "CoCreateInstance failed with %x\n", hr);

    hr = IFilterMapper2_QueryInterface(mapper2, &IID_IFilterMapper, (void **)&mapper);
    ok(hr == S_OK, "IFilterMapper2_QueryInterface failed with %x\n", hr);

    /* Set default value - this is interpreted as "friendly name" later. */
    RegSetValueExW(hkey, NULL, 0, REG_SZ, (BYTE *)testfilterW, sizeof(testfilterW));
    RegCloseKey(hkey);

    hr = IFilterMapper_RegisterFilter(mapper, clsid, testfilterW, MERIT_UNLIKELY);
    ok(hr == S_OK, "RegisterFilter failed: %#x\n", hr);

    hr = IFilterMapper_RegisterPin(mapper, clsid, pinW, TRUE, FALSE, FALSE, FALSE, GUID_NULL, NULL);
    ok(hr == S_OK, "RegisterPin failed: %#x\n", hr);

    hr = IFilterMapper_RegisterPinType(mapper, clsid, pinW, GUID_NULL, GUID_NULL);
    ok(hr == S_OK, "RegisterPinType failed: %#x\n", hr);

    hr = IFilterMapper2_EnumMatchingFilters(mapper2, &enum_mon, 0, TRUE, MERIT_UNLIKELY, TRUE,
            0, NULL, NULL, &GUID_NULL, FALSE, FALSE, 0, NULL, NULL, &GUID_NULL);
    ok(hr == S_OK, "IFilterMapper2_EnumMatchingFilters failed: %x\n", hr);
    ok(enum_find_filter(testfilterW, enum_mon), "IFilterMapper2 didn't find filter\n");
    IEnumMoniker_Release(enum_mon);

    found = FALSE;
    hr = IFilterMapper_EnumMatchingFilters(mapper, &enum_reg, MERIT_UNLIKELY, TRUE, GUID_NULL, GUID_NULL,
        FALSE, FALSE, GUID_NULL, GUID_NULL);
    ok(hr == S_OK, "IFilterMapper_EnumMatchingFilters failed with %x\n", hr);
    while(!found && IEnumRegFilters_Next(enum_reg, 1, &regfilter, &count) == S_OK)
    {
        if (!lstrcmpW(regfilter->Name, testfilterW) && IsEqualGUID(&clsid, &regfilter->Clsid))
            found = TRUE;
    }
    IEnumRegFilters_Release(enum_reg);
    ok(found, "IFilterMapper didn't find filter\n");

    hr = IFilterMapper_UnregisterFilter(mapper, clsid);
    ok(hr == S_OK, "FilterMapper_UnregisterFilter failed with %x\n", hr);

    hr = IFilterMapper2_EnumMatchingFilters(mapper2, &enum_mon, 0, TRUE, MERIT_UNLIKELY, TRUE,
            0, NULL, NULL, &GUID_NULL, FALSE, FALSE, 0, NULL, NULL, &GUID_NULL);
    ok(hr == S_OK, "IFilterMapper2_EnumMatchingFilters failed: %x\n", hr);
    ok(!enum_find_filter(testfilterW, enum_mon), "IFilterMapper2 shouldn't find filter\n");
    IEnumMoniker_Release(enum_mon);

    found = FALSE;
    hr = IFilterMapper_EnumMatchingFilters(mapper, &enum_reg, MERIT_UNLIKELY, TRUE, GUID_NULL, GUID_NULL,
        FALSE, FALSE, GUID_NULL, GUID_NULL);
    ok(hr == S_OK, "IFilterMapper_EnumMatchingFilters failed with %x\n", hr);
    while(!found && IEnumRegFilters_Next(enum_reg, 1, &regfilter, &count) == S_OK)
    {
        if (!lstrcmpW(regfilter->Name, testfilterW) && IsEqualGUID(&clsid, &regfilter->Clsid))
            found = TRUE;
    }
    IEnumRegFilters_Release(enum_reg);
    ok(!found, "IFilterMapper shouldn't find filter\n");

    ret = RegDeleteKeyW(HKEY_CLASSES_ROOT, key_name);
    ok(!ret, "RegDeleteKeyA failed: %lu\n", ret);

    hr = IFilterMapper_RegisterFilter(mapper, clsid, testfilterW, MERIT_UNLIKELY);
    ok(hr == S_OK, "RegisterFilter failed: %#x\n", hr);

    hr = IFilterMapper_UnregisterFilter(mapper, clsid);
    ok(hr == S_OK, "FilterMapper_UnregisterFilter failed with %x\n", hr);

    IFilterMapper_Release(mapper);
    IFilterMapper2_Release(mapper2);
}