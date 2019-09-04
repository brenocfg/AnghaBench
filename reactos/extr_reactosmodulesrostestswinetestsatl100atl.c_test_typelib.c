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
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HINSTANCE ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const*) ; 
 scalar_t__ AtlLoadTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 size_t SysStringLen (scalar_t__) ; 
 scalar_t__ lstrcmpiW (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (scalar_t__) ; 

__attribute__((used)) static void test_typelib(void)
{
    ITypeLib *typelib;
    HINSTANCE inst;
    size_t len;
    BSTR path;
    HRESULT hres;

    static const WCHAR scrrun_dll_suffixW[] = {'\\','s','c','r','r','u','n','.','d','l','l',0};
    static const WCHAR mshtml_tlb_suffixW[] = {'\\','m','s','h','t','m','l','.','t','l','b',0};

    inst = LoadLibraryA("scrrun.dll");
    ok(inst != NULL, "Could not load scrrun.dll\n");

    typelib = NULL;
    hres = AtlLoadTypeLib(inst, NULL, &path, &typelib);
    ok(hres == S_OK, "AtlLoadTypeLib failed: %08x\n", hres);
    FreeLibrary(inst);

    len = SysStringLen(path);
    ok(len > ARRAY_SIZE(scrrun_dll_suffixW)
       && lstrcmpiW(path+len-ARRAY_SIZE(scrrun_dll_suffixW), scrrun_dll_suffixW),
       "unexpected path %s\n", wine_dbgstr_w(path));
    SysFreeString(path);
    ok(typelib != NULL, "typelib == NULL\n");
    ITypeLib_Release(typelib);

    inst = LoadLibraryA("mshtml.dll");
    ok(inst != NULL, "Could not load mshtml.dll\n");

    typelib = NULL;
    hres = AtlLoadTypeLib(inst, NULL, &path, &typelib);
    ok(hres == S_OK, "AtlLoadTypeLib failed: %08x\n", hres);
    FreeLibrary(inst);

    len = SysStringLen(path);
    ok(len > ARRAY_SIZE(mshtml_tlb_suffixW)
       && lstrcmpiW(path+len-ARRAY_SIZE(mshtml_tlb_suffixW), mshtml_tlb_suffixW),
       "unexpected path %s\n", wine_dbgstr_w(path));
    SysFreeString(path);
    ok(typelib != NULL, "typelib == NULL\n");
    ITypeLib_Release(typelib);
}