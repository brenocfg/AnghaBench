#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_10__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  int const REGSAM ;
typedef  char OLECHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  int /*<<< orphan*/  ICreateTypeLib2 ;
typedef  int /*<<< orphan*/  ICreateTypeInfo ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_2__ GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CoGetPSClsid (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ CreateTypeLib2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ ICreateTypeInfo_AddImplType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ICreateTypeInfo_AddRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ICreateTypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeInfo_SetGuid (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ ICreateTypeInfo_SetTypeFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ICreateTypeLib2_CreateTypeInfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ICreateTypeLib2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ ICreateTypeLib2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_SaveAllChanges (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_SetGuid (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ ICreateTypeLib2_SetLcid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPSFactoryBuffer ; 
 int /*<<< orphan*/  IID_ITypeInfo ; 
 int /*<<< orphan*/  IID_ITypeLib ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IPSFactoryBuffer_CreateStub (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPSFactoryBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRpcStubBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int const KEY_READ ; 
#define  KEY_WOW64_32KEY 129 
#define  KEY_WOW64_64KEY 128 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 scalar_t__ LoadTypeLib (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 scalar_t__ RegisterTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_WIN32 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TKIND_COCLASS ; 
 int /*<<< orphan*/  TKIND_INTERFACE ; 
 int /*<<< orphan*/  TYPEFLAG_FOLEAUTOMATION ; 
 scalar_t__ TYPE_E_REGISTRYACCESS ; 
 scalar_t__ UnRegisterTypeLib (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ is_win64 ; 
 scalar_t__ myRegDeleteTreeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pIsWow64Process (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  uk ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wszStdOle2 ; 

__attribute__((used)) static void test_stub(void)
{
    BOOL is_wow64 = FALSE;
    DWORD *sam_list;
    HRESULT hr;
    ITypeLib *stdole;
    ICreateTypeLib2 *ctl;
    ICreateTypeInfo *cti;
    ITypeLib *tl;
    ITypeInfo *unk, *ti;
    HREFTYPE href;
    char filenameA[MAX_PATH];
    WCHAR filenameW[MAX_PATH];
    int i;

    static const GUID libguid = {0x3b9ff02e,0x9675,0x4861,{0xb7,0x81,0xce,0xae,0xa4,0x78,0x2a,0xcc}};
    static const GUID interfaceguid = {0x3b9ff02f,0x9675,0x4861,{0xb7,0x81,0xce,0xae,0xa4,0x78,0x2a,0xcc}};
    static const GUID coclassguid = {0x3b9ff030,0x9675,0x4861,{0xb7,0x81,0xce,0xae,0xa4,0x78,0x2a,0xcc}};
    static OLECHAR interfaceW[] = {'i','n','t','e','r','f','a','c','e',0};
    static OLECHAR classW[] = {'c','l','a','s','s',0};
    static DWORD sam_list32[] = { 0, ~0 };
    static DWORD sam_list64[] = { 0, KEY_WOW64_32KEY, KEY_WOW64_64KEY, ~0 };

    if (pIsWow64Process)
        pIsWow64Process(GetCurrentProcess(), &is_wow64);
    if (is_wow64 || is_win64)
        sam_list = sam_list64;
    else
        sam_list = sam_list32;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    hr = LoadTypeLib(wszStdOle2, &stdole);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ITypeLib_GetTypeInfoOfGuid(stdole, &IID_IUnknown, &unk);
    ok(hr == S_OK, "got %08x\n", hr);

    GetTempFileNameA(".", "tlb", 0, filenameA);
    MultiByteToWideChar(CP_ACP, 0, filenameA, -1, filenameW, MAX_PATH);

    hr = CreateTypeLib2(SYS_WIN32, filenameW, &ctl);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_SetGuid(ctl, &libguid);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_SetLcid(ctl, LOCALE_NEUTRAL);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_CreateTypeInfo(ctl, interfaceW, TKIND_INTERFACE, &cti);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_SetGuid(cti, &interfaceguid);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_SetTypeFlags(cti, TYPEFLAG_FOLEAUTOMATION);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddRefTypeInfo(cti, unk, &href);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddImplType(cti, 0, href);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_QueryInterface(cti, &IID_ITypeInfo, (void**)&ti);
    ok(hr == S_OK, "got %08x\n", hr);

    ICreateTypeInfo_Release(cti);
    ITypeInfo_Release(unk);
    ITypeLib_Release(stdole);

    hr = ICreateTypeLib2_CreateTypeInfo(ctl, classW, TKIND_COCLASS, &cti);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_SetGuid(cti, &coclassguid);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddRefTypeInfo(cti, ti, &href);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddImplType(cti, 0, href);
    ok(hr == S_OK, "got %08x\n", hr);

    ITypeInfo_Release(ti);
    ICreateTypeInfo_Release(cti);

    hr = ICreateTypeLib2_SaveAllChanges(ctl);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_QueryInterface(ctl, &IID_ITypeLib, (void**)&tl);
    ok(hr == S_OK, "got %08x\n", hr);

    for (i = 0; sam_list[i] != ~0; i++)
    {
        IPSFactoryBuffer *factory;
        IRpcStubBuffer *base_stub;
        REGSAM side = sam_list[i];
        CLSID clsid;
        HKEY hkey;
        LONG lr;

        hr = RegisterTypeLib(tl, filenameW, NULL);
        if (hr == TYPE_E_REGISTRYACCESS)
        {
            win_skip("Insufficient privileges to register typelib in the registry\n");
            break;
        }
        ok(hr == S_OK, "got %08x, side: %04x\n", hr, side);

        /* SYS_WIN32 typelibs should be registered only as 32-bit */
        lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "TypeLib\\{3b9ff02e-9675-4861-b781-ceaea4782acc}\\0.0\\0\\win64", 0, KEY_READ | side, &hkey);
        ok(lr == ERROR_FILE_NOT_FOUND, "got wrong return code: %u, side: %04x\n", lr, side);

        lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "TypeLib\\{3b9ff02e-9675-4861-b781-ceaea4782acc}\\0.0\\0\\win32", 0, KEY_READ | side, &hkey);
        ok(lr == ERROR_SUCCESS, "got wrong return code: %u, side: %04x\n", lr, side);
        RegCloseKey(hkey);

        /* Simulate pre-win7 installers that create interface key on one side */
        if (side != 0)
        {
            WCHAR guidW[40];
            REGSAM opposite = side ^ (KEY_WOW64_64KEY | KEY_WOW64_32KEY);

            StringFromGUID2(&interfaceguid, guidW, ARRAY_SIZE(guidW));

            /* Delete the opposite interface key */
            lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "Interface", 0, KEY_READ | opposite, &hkey);
            ok(lr == ERROR_SUCCESS, "got wrong return code: %u, side: %04x\n", lr, side);
            lr = myRegDeleteTreeW(hkey, guidW, opposite);
            ok(lr == ERROR_SUCCESS, "got wrong return code: %u, side: %04x\n", lr, side);
            RegCloseKey(hkey);

            /* Is our side interface key affected by above operation? */
            lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "Interface\\{3b9ff02f-9675-4861-b781-ceaea4782acc}", 0, KEY_READ | side, &hkey);
            ok(lr == ERROR_SUCCESS || broken(lr == ERROR_FILE_NOT_FOUND), "got wrong return code: %u, side: %04x\n", lr, side);
            if (lr == ERROR_FILE_NOT_FOUND)
            {
                /* win2k3, vista, 2008 */
                win_skip("Registry reflection is enabled on this platform.\n");
                goto next;
            }
            RegCloseKey(hkey);

            /* Opposite side typelib key still exists */
            lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "TypeLib\\{3b9ff02e-9675-4861-b781-ceaea4782acc}\\0.0\\0\\win32", 0, KEY_READ | opposite, &hkey);
            ok(lr == ERROR_SUCCESS, "got wrong return code: %u, side: %04x\n", lr, side);
            RegCloseKey(hkey);
        }

        hr = CoGetPSClsid(&interfaceguid, &clsid);
        ok(hr == S_OK, "got: %x, side: %04x\n", hr, side);

        hr = CoGetClassObject(&clsid, CLSCTX_INPROC_SERVER, NULL,
                              &IID_IPSFactoryBuffer, (void **)&factory);
        ok(hr == S_OK, "got: %x, side: %04x\n", hr, side);

        hr = IPSFactoryBuffer_CreateStub(factory, &interfaceguid, &uk, &base_stub);
        ok(hr == S_OK, "got: %x, side: %04x\n", hr, side);
        IRpcStubBuffer_Release(base_stub);

        IPSFactoryBuffer_Release(factory);
    next:
        hr = UnRegisterTypeLib(&libguid, 0, 0, 0, SYS_WIN32);
        ok(hr == S_OK, "got: %x, side: %04x\n", hr, side);
    }

    ITypeLib_Release(tl);
    ok(0 == ICreateTypeLib2_Release(ctl), "Typelib still has references\n");

    DeleteFileW(filenameW);

    CoUninitialize();
}