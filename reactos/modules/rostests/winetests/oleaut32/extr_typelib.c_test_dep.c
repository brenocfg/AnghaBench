#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_8__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  ICreateTypeLib2 ;
typedef  int /*<<< orphan*/  ICreateTypeInfo ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  TYPE_2__ GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CreateTypeLib2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ICreateTypeInfo_AddImplType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ICreateTypeInfo_AddRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICreateTypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeInfo_SetGuid (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ ICreateTypeInfo_SetTypeFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ICreateTypeLib2_CreateTypeInfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ICreateTypeLib2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_SaveAllChanges (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_SetGuid (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ ICreateTypeLib2_SetLcid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ const IID_ISimpleIface ; 
 scalar_t__ ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 scalar_t__ LoadTypeLibEx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 
 int /*<<< orphan*/  REGKIND_NONE ; 
 int /*<<< orphan*/  SYS_WIN32 ; 
 int /*<<< orphan*/  SYS_WIN64 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TKIND_INTERFACE ; 
 int /*<<< orphan*/  TYPEFLAG_FOLEAUTOMATION ; 
 scalar_t__ TYPE_E_CANTLOADLIBRARY ; 
 scalar_t__ broken (int) ; 
 char* create_test_typelib (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_dep(void) {
    HRESULT          hr;
    const char      *refFilename;
    WCHAR            refFilenameW[MAX_PATH];
    ITypeLib        *preftLib;
    ITypeInfo       *preftInfo;
    char             filename[MAX_PATH];
    WCHAR            filenameW[MAX_PATH];
    ICreateTypeLib2 *pctLib;
    ICreateTypeInfo *pctInfo;
    ITypeLib        *ptLib;
    ITypeInfo       *ptInfo;
    ITypeInfo       *ptInfoExt = NULL;
    HREFTYPE         refType;

    static WCHAR ifacenameW[] = {'I','T','e','s','t','D','e','p',0};

    static const GUID libguid = {0xe0228f26,0x2946,0x478c,{0xb6,0x4a,0x93,0xfe,0xef,0xa5,0x05,0x32}};
    static const GUID ifaceguid = {0x394376dd,0x3bb8,0x4804,{0x8c,0xcc,0x95,0x59,0x43,0x40,0x04,0xf3}};

    trace("Starting typelib dependency tests\n");

    refFilename = create_test_typelib(2);
    MultiByteToWideChar(CP_ACP, 0, refFilename, -1, refFilenameW, MAX_PATH);

    hr = LoadTypeLibEx(refFilenameW, REGKIND_NONE, &preftLib);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ITypeLib_GetTypeInfoOfGuid(preftLib, &IID_ISimpleIface, &preftInfo);
    ok(hr == S_OK, "got %08x\n", hr);

    GetTempFileNameA(".", "tlb", 0, filename);
    MultiByteToWideChar(CP_ACP, 0, filename, -1, filenameW, MAX_PATH);

    if(sizeof(void*) == 8) {
        hr = CreateTypeLib2(SYS_WIN64, filenameW, &pctLib);
        ok(hr == S_OK, "got %08x\n", hr);
    } else {
        hr = CreateTypeLib2(SYS_WIN32, filenameW, &pctLib);
        ok(hr == S_OK, "got %08x\n", hr);
    }

    hr = ICreateTypeLib2_SetGuid(pctLib, &libguid);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_SetLcid(pctLib, LOCALE_NEUTRAL);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_CreateTypeInfo(pctLib, ifacenameW, TKIND_INTERFACE, &pctInfo);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_SetGuid(pctInfo, &ifaceguid);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_SetTypeFlags(pctInfo, TYPEFLAG_FOLEAUTOMATION);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddRefTypeInfo(pctInfo, preftInfo, &refType);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddImplType(pctInfo, 0, refType);
    ok(hr == S_OK, "got %08x\n", hr);

    ICreateTypeInfo_Release(pctInfo);

    hr = ICreateTypeLib2_SaveAllChanges(pctLib);
    ok(hr == S_OK, "got %08x\n", hr);

    ICreateTypeLib2_Release(pctLib);

    ITypeInfo_Release(preftInfo);
    ITypeLib_Release(preftLib);

    DeleteFileW(refFilenameW);

    hr = LoadTypeLibEx(filenameW, REGKIND_NONE, &ptLib);
    ok(hr == S_OK, "got: %x\n", hr);

    hr = ITypeLib_GetTypeInfoOfGuid(ptLib, &ifaceguid, &ptInfo);
    ok(hr == S_OK, "got: %x\n", hr);

    hr = ITypeInfo_GetRefTypeOfImplType(ptInfo, 0, &refType);
    ok(hr == S_OK, "got: %x\n", hr);

    hr = ITypeInfo_GetRefTypeInfo(ptInfo, refType, &ptInfoExt);
    ok(hr == S_OK || broken(hr == TYPE_E_CANTLOADLIBRARY) /* win 2000 */, "got: %x\n", hr);

    ITypeInfo_Release(ptInfo);
    if(ptInfoExt)
        ITypeInfo_Release(ptInfoExt);
    ITypeLib_Release(ptLib);

    DeleteFileW(filenameW);
}