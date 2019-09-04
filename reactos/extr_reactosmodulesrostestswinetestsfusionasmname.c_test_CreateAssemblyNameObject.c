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
typedef  int /*<<< orphan*/  arch ;
typedef  char WCHAR ;
typedef  int PEKIND ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int ASM_DISPLAYF_CULTURE ; 
 int ASM_DISPLAYF_FULL ; 
 int ASM_DISPLAYF_PROCESSORARCHITECTURE ; 
 int ASM_DISPLAYF_PUBLIC_KEY_TOKEN ; 
 int ASM_DISPLAYF_VERSION ; 
 int /*<<< orphan*/  ASM_NAME_ARCHITECTURE ; 
 int /*<<< orphan*/  CANOF_PARSE_DISPLAY_NAME ; 
 int /*<<< orphan*/  CANOF_SET_DEFAULT_VALUES ; 
 int /*<<< orphan*/  CP_ACP ; 
 int E_INVALIDARG ; 
 int E_NOT_SUFFICIENT_BUFFER ; 
 int FUSION_E_INVALID_NAME ; 
 int IAssemblyName_GetDisplayName (int /*<<< orphan*/ *,char*,int*,int) ; 
 int IAssemblyName_GetName (int /*<<< orphan*/ *,int*,char*) ; 
 int IAssemblyName_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int IAssemblyName_GetVersion (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  badvername ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  defaults ; 
 int /*<<< orphan*/  emptyname ; 
 int /*<<< orphan*/  enname ; 
 scalar_t__ lstrcmpA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  neutralname ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_aw (char*,char*) ; 
 int pCreateAssemblyNameObject (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int peAMD64 ; 
 int peI386 ; 
 int peIA64 ; 
 int peMSIL ; 
 int /*<<< orphan*/  pubkeyname ; 
 int /*<<< orphan*/  string1 ; 
 int /*<<< orphan*/  test_assembly_name_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_widechar (char*,char*) ; 
 int /*<<< orphan*/  vername ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winename ; 

__attribute__((used)) static void test_CreateAssemblyNameObject(void)
{
    IAssemblyName *name;
    WCHAR str[MAX_PATH];
    WCHAR namestr[MAX_PATH];
    DWORD size, hi, lo;
    PEKIND arch;
    HRESULT hr;

    static const WCHAR empty[] = {0};

    /* NULL ppAssemblyNameObj */
    to_widechar(namestr, "wine.dll");
    hr = pCreateAssemblyNameObject(NULL, namestr, 0, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    /* NULL szAssemblyName, CANOF_PARSE_DISPLAY_NAME */
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, NULL, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* empty szAssemblyName, CANOF_PARSE_DISPLAY_NAME */
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, empty, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* check the contents of the AssemblyName for default values */

    /* NULL szAssemblyName */
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, NULL, CANOF_SET_DEFAULT_VALUES, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == E_INVALIDARG), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);

    str[0] = 'a';
    size = MAX_PATH;
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(str[0] == 'a', "got %c\n", str[0]);
    ok(!size, "got %u\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    if (hr == S_OK)
        win_skip(".NET 1.x doesn't handle ASM_NAME_PROCESSOR_ID_ARRAY"
                 " and ASM_NAME_OSINFO_ARRAY correctly\n");
    else
        test_assembly_name_props(name, defaults);

    IAssemblyName_Release(name);

    /* empty szAssemblyName */
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, empty, CANOF_SET_DEFAULT_VALUES, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);

    size = 0;
    hr = IAssemblyName_GetName(name, &size, NULL);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(size == 1, "got %u\n", size);

    if (0) /* crash */
    {
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, NULL, str);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(!str[0], "got %c\n", str[0]);
    }

    size = 0;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(!str[0], "got %c\n", str[0]);
    ok(size == 1, "got %u\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!str[0], "Expected empty name\n");
    ok(size == 1, "Expected 1, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    if (hr == S_OK)
        win_skip(".NET 1.x doesn't handle ASM_NAME_PROCESSOR_ID_ARRAY"
                 " and ASM_NAME_OSINFO_ARRAY correctly\n");
    else
        test_assembly_name_props(name, emptyname);

    IAssemblyName_Release(name);

    /* 'wine' */
    to_widechar(namestr, "wine");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_SET_DEFAULT_VALUES, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = 0;
    hr = IAssemblyName_GetDisplayName(name, NULL, &size, 0);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(size == 5, "got %u\n", size);

    size = 3;
    hr = IAssemblyName_GetDisplayName(name, NULL, &size, 0);
    ok(hr == E_NOT_SUFFICIENT_BUFFER || broken(hr == E_INVALIDARG), "got %08x\n", hr);
    ok(size == 5 || broken(size == 3), "got %u\n", size);

    size = 3;
    str[0] = 'a';
    hr = IAssemblyName_GetDisplayName(name, str, &size, 0);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(str[0] == 'a', "got %c\n", str[0]);
    ok(size == 5, "got %u\n", size);

    size = 0;
    str[0] = 'a';
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(str[0] == 'a', "got %c\n", str[0]);
    ok(size == 5, "Wrong size %u\n", size);

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    size = 0;
    str[0] = 0;
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "got %08x\n", hr);
    ok(!str[0], "got %c\n", str[0]);
    ok(size == 5, "got %u\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    if (hr == S_OK)
        win_skip(".NET 1.x doesn't handle ASM_NAME_PROCESSOR_ID_ARRAY"
                 " and ASM_NAME_OSINFO_ARRAY correctly\n");
    else
        test_assembly_name_props(name, winename);

    IAssemblyName_Release(name);

    /* check the contents of the AssemblyName with parsing */

    /* 'wine' */
    to_widechar(namestr, "wine");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, winename);

    IAssemblyName_Release(name);

    /* 'wine, Version=1.2.3.4' */
    to_widechar(namestr, "wine, Version=1.2.3.4");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Version=1.2.3.4", str);
    ok(size == 22, "Expected 22, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(hi == 0x00010002, "Expected 0x00010002, got %08x\n", hi);
    ok(lo == 0x00030004, "Expected 0x00030004, got %08x\n", lo);

    test_assembly_name_props(name, vername);

    IAssemblyName_Release(name);

    /* Version isn't of the form 1.x.x.x */
    to_widechar(namestr, "wine, Version=1.5");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Version=1.5", str);
    ok(size == 18, "Expected 18, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0 ||
       broken(hi == 0x10005), /* .NET 1.x */
       "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, badvername);

    IAssemblyName_Release(name);

    /* 'wine, Culture=neutral' */
    to_widechar(namestr, "wine, Culture=neutral");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Culture=neutral", str);
    ok(size == 22, "Expected 22, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, neutralname);

    IAssemblyName_Release(name);

    /* 'wine, Culture=en' */
    to_widechar(namestr, "wine, Culture=en");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Culture=en", str);
    ok(size == 17, "Expected 17, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, enname);

    IAssemblyName_Release(name);

    /* 'wine, PublicKeyToken=01234567890abcde' */
    to_widechar(namestr, "wine, PublicKeyToken=01234567890abcde");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, PublicKeyToken=01234567890abcde", str);
    ok(size == 38, "Expected 38, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, pubkeyname);

    IAssemblyName_Release(name);

    /* Processor architecture tests */
    to_widechar(namestr, "wine, processorArchitecture=x86");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_PROCESSORARCHITECTURE);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    WideCharToMultiByte(CP_ACP, 0, str, -1, string1, MAX_PATH, NULL, NULL);

    if (lstrcmpA(string1, "wine") == 0)
        win_skip("processorArchitecture not supported on .NET 1.x\n");
    else
    {
        ok_aw("wine, processorArchitecture=x86", str);
        ok(size == 32, "Expected 32, got %d\n", size);

        size = sizeof(arch);
        hr = IAssemblyName_GetProperty(name, ASM_NAME_ARCHITECTURE, &arch, &size);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok(arch == peI386, "Expected peI386, got %d\n", arch);
        ok(size == sizeof(arch), "Wrong size %d\n", size);

        IAssemblyName_Release(name);

        /* amd64 */
        to_widechar(namestr, "wine, processorArchitecture=AMD64");
        name = NULL;
        hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

        size = MAX_PATH;
        hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_PROCESSORARCHITECTURE);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok_aw("wine, processorArchitecture=AMD64", str);
        ok(size == 34, "Expected 34, got %d\n", size);

        size = sizeof(arch);
        hr = IAssemblyName_GetProperty(name, ASM_NAME_ARCHITECTURE, &arch, &size);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok(arch == peAMD64, "Expected peAMD64, got %d\n", arch);
        ok(size == sizeof(arch), "Wrong size %d\n", size);

        IAssemblyName_Release(name);

        /* ia64 */
        to_widechar(namestr, "wine, processorArchitecture=IA64");
        name = NULL;
        hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

        size = MAX_PATH;
        hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_PROCESSORARCHITECTURE);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok_aw("wine, processorArchitecture=IA64", str);
        ok(size == 33, "Expected 33, got %d\n", size);

        size = sizeof(arch);
        hr = IAssemblyName_GetProperty(name, ASM_NAME_ARCHITECTURE, &arch, &size);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok(arch == peIA64, "Expected peIA64, got %d\n", arch);
        ok(size == sizeof(arch), "Wrong size %d\n", size);

        IAssemblyName_Release(name);

        /* msil */
        to_widechar(namestr, "wine, processorArchitecture=MSIL");
        name = NULL;
        hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

        size = MAX_PATH;
        hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_PROCESSORARCHITECTURE);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok_aw("wine, processorArchitecture=MSIL", str);
        ok(size == 33, "Expected 33, got %d\n", size);

        size = sizeof(arch);
        hr = IAssemblyName_GetProperty(name, ASM_NAME_ARCHITECTURE, &arch, &size);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok(arch == peMSIL, "Expected peMSIL, got %d\n", arch);
        ok(size == sizeof(arch), "Wrong size %d\n", size);

        IAssemblyName_Release(name);
    }

    /* Pulling out various different values */
    to_widechar(namestr, "wine, Version=1.2.3.4, Culture=en, PublicKeyToken=1234567890abcdef");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_VERSION | ASM_DISPLAYF_CULTURE);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Version=1.2.3.4, Culture=en", str);
    ok(size == 34, "Expected 34, got %d\n", size);

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_CULTURE | ASM_DISPLAYF_PUBLIC_KEY_TOKEN);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Culture=en, PublicKeyToken=1234567890abcdef", str);
    ok(size == 50, "Expected 50, got %d\n", size);

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine, Version=1.2.3.4, Culture=en, PublicKeyToken=1234567890abcdef", str);
    ok(size == 67, "Expected 67, got %d\n", size);

    IAssemblyName_Release(name);

    /* invalid property */
    to_widechar(namestr, "wine, BadProp=42");
    name = NULL;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetDisplayName(name, str, &size, ASM_DISPLAYF_FULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    size = MAX_PATH;
    str[0] = '\0';
    hr = IAssemblyName_GetName(name, &size, str);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_aw("wine", str);
    ok(size == 5, "Expected 5, got %d\n", size);

    hi = 0xbeefcace;
    lo = 0xcafebabe;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == FUSION_E_INVALID_NAME ||
       broken(hr == S_OK), /* .NET 1.x */
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(hi == 0, "Expected 0, got %08x\n", hi);
    ok(lo == 0, "Expected 0, got %08x\n", lo);

    test_assembly_name_props(name, winename);

    IAssemblyName_Release(name);

    /* PublicKeyToken is not 16 chars long */
    to_widechar(namestr, "wine, PublicKeyToken=567890abcdef");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    if (hr == S_OK && name != (IAssemblyName *)0xdeadbeef)
    {
        win_skip(".NET 1.x doesn't check PublicKeyToken correctly\n");
        IAssemblyName_Release(name);
        return;
    }
    ok(hr == FUSION_E_INVALID_NAME,
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* PublicKeyToken contains invalid chars */
    to_widechar(namestr, "wine, PublicKeyToken=1234567890ghijkl");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == FUSION_E_INVALID_NAME,
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* no comma separator */
    to_widechar(namestr, "wine PublicKeyToken=1234567890abcdef");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == FUSION_E_INVALID_NAME,
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);
    if(SUCCEEDED(hr)) IAssemblyName_Release(name);

    /* no '=' */
    to_widechar(namestr, "wine, PublicKeyToken");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == FUSION_E_INVALID_NAME,
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* no value */
    to_widechar(namestr, "wine, PublicKeyToken=");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == FUSION_E_INVALID_NAME,
       "Expected FUSION_E_INVALID_NAME, got %08x\n", hr);
    ok(name == (IAssemblyName *)0xdeadbeef, "Expected 0xdeadbeef, got %p\n", name);

    /* no spaces */
    to_widechar(namestr, "wine,version=1.0.0.0");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");
    hi = lo = 0xdeadbeef;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(hi == 65536, "Expected 536, got %u\n", hi);
    ok(lo == 0, "Expected 0, got %u\n", lo);
    IAssemblyName_Release(name);

    /* quoted values */
    to_widechar(namestr, "wine, version=\"1.0.0.0\",culture=\"en\"");
    name = (IAssemblyName *)0xdeadbeef;
    hr = pCreateAssemblyNameObject(&name, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(name != NULL, "Expected non-NULL name\n");
    hi = lo = 0xdeadbeef;
    hr = IAssemblyName_GetVersion(name, &hi, &lo);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(hi == 65536, "Expected 65536, got %u\n", hi);
    ok(lo == 0, "Expected 0, got %u\n", lo);
    IAssemblyName_Release(name);
}