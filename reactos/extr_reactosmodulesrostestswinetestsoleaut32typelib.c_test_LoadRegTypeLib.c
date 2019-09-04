#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_4__ {int lcid; int wMajorVerNum; int wMinorVerNum; int wLibFlags; } ;
typedef  TYPE_1__ TLIBATTR ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int GetLastError () ; 
 int ITypeLib_GetLibAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_ReleaseTLibAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_RUSSIAN ; 
 int LIBFLAG_FHASDISKIMAGE ; 
 int /*<<< orphan*/  LIBID_TestTypelib ; 
 int /*<<< orphan*/  LIBID_register_test ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int LoadRegTypeLib (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QueryPathOfRegTypeLib (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int TYPE_E_LIBNOTREGISTERED ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_actctx (char*) ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manifest_dep ; 
 int /*<<< orphan*/  manifest_main ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pActivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  write_typelib (int,char*) ; 

__attribute__((used)) static void test_LoadRegTypeLib(void)
{
    LCID lcid_en = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    LCID lcid_ru = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL), SORT_DEFAULT);
    ULONG_PTR cookie;
    TLIBATTR *attr;
    HANDLE handle;
    ITypeLib *tl;
    HRESULT hr;
    BSTR path;
    BOOL ret;

    if (!pActivateActCtx)
    {
        win_skip("Activation contexts not supported, skipping LoadRegTypeLib tests\n");
        return;
    }

    create_manifest_file("testdep.manifest", manifest_dep);
    create_manifest_file("main.manifest", manifest_main);

    handle = create_actctx("main.manifest");
    DeleteFileA("testdep.manifest");
    DeleteFileA("main.manifest");

    /* create typelib file */
    write_typelib(1, "test_actctx_tlb.tlb");
    write_typelib(3, "test_actctx_tlb2.tlb");

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 1, 0, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    hr = LoadRegTypeLib(&LIBID_register_test, 1, 0, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 0, LOCALE_NEUTRAL, &path);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    ret = pActivateActCtx(handle, &cookie);
    ok(ret, "ActivateActCtx failed: %u\n", GetLastError());

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 0, LOCALE_NEUTRAL, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(path);

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 0, lcid_en, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(path);

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 0, lcid_ru, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(path);

    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 8, LOCALE_NEUTRAL, &path);
    ok(hr == TYPE_E_LIBNOTREGISTERED || broken(hr == S_OK) /* winxp */, "got 0x%08x\n", hr);

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 2, 7, LOCALE_NEUTRAL, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(path);

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 1, 0, LOCALE_NEUTRAL, &path);
    ok(hr == TYPE_E_LIBNOTREGISTERED || broken(hr == S_OK) /* winxp */, "got 0x%08x\n", hr);
    SysFreeString(path);

    path = NULL;
    hr = QueryPathOfRegTypeLib(&LIBID_TestTypelib, 0xffff, 0xffff, LOCALE_NEUTRAL, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(path);

    /* manifest version is 2.0, actual is 1.0 */
    hr = LoadRegTypeLib(&LIBID_register_test, 1, 0, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED || broken(hr == S_OK) /* winxp */, "got 0x%08x\n", hr);
    if (hr == S_OK) ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_register_test, 2, 0, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    /* manifest version is 2.7, actual is 2.5 */
    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 0, LOCALE_NEUTRAL, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    if (hr == S_OK) ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 1, LOCALE_NEUTRAL, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    if (hr == S_OK) ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 0, lcid_en, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    if (hr == S_OK) ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 0, lcid_ru, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    if (hr == S_OK) ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 7, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 5, LOCALE_NEUTRAL, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = ITypeLib_GetLibAttr(tl, &attr);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ok(attr->lcid == 0, "got %x\n", attr->lcid);
    ok(attr->wMajorVerNum == 2, "got %d\n", attr->wMajorVerNum);
    ok(attr->wMinorVerNum == 5, "got %d\n", attr->wMinorVerNum);
    ok(attr->wLibFlags == LIBFLAG_FHASDISKIMAGE, "got %x\n", attr->wLibFlags);

    ITypeLib_ReleaseTLibAttr(tl, attr);
    ITypeLib_Release(tl);

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 1, 7, LOCALE_NEUTRAL, &tl);
    ok(hr == TYPE_E_LIBNOTREGISTERED, "got 0x%08x\n", hr);

    tl = NULL;
    hr = LoadRegTypeLib(&LIBID_TestTypelib, 0xffff, 0xffff, LOCALE_NEUTRAL, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    if (tl)
    {
        hr = ITypeLib_GetLibAttr(tl, &attr);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        ok(attr->lcid == 0, "got %x\n", attr->lcid);
        ok(attr->wMajorVerNum == 2, "got %d\n", attr->wMajorVerNum);
        ok(attr->wMinorVerNum == 5, "got %d\n", attr->wMinorVerNum);
        ok(attr->wLibFlags == LIBFLAG_FHASDISKIMAGE, "got %x\n", attr->wLibFlags);

        ITypeLib_ReleaseTLibAttr(tl, attr);
        ITypeLib_Release(tl);
    }

    DeleteFileA("test_actctx_tlb.tlb");
    DeleteFileA("test_actctx_tlb2.tlb");

    ret = pDeactivateActCtx(0, cookie);
    ok(ret, "DeactivateActCtx failed: %u\n", GetLastError());

    pReleaseActCtx(handle);
}