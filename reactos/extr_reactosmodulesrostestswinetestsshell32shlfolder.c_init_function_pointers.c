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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 void* GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SHGetMalloc (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 void* pIsWow64Process ; 
 void* pSHCreateDefaultContextMenu ; 
 void* pSHCreateItemFromIDList ; 
 void* pSHCreateItemFromParsingName ; 
 void* pSHCreateItemFromRelativeName ; 
 void* pSHCreateItemInKnownFolder ; 
 void* pSHCreateShellItem ; 
 void* pSHCreateShellItemArray ; 
 void* pSHCreateShellItemArrayFromDataObject ; 
 void* pSHCreateShellItemArrayFromIDLists ; 
 void* pSHCreateShellItemArrayFromShellItem ; 
 void* pSHGetIDListFromObject ; 
 void* pSHGetItemFromDataObject ; 
 void* pSHGetItemFromObject ; 
 void* pSHGetKnownFolderPath ; 
 void* pSHGetNameFromIDList ; 
 void* pSHGetPathFromIDListEx ; 
 void* pSHGetSetFolderCustomSettings ; 
 int /*<<< orphan*/  ppM ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hmod;
    HRESULT hr;
    void *ptr;

    hmod = GetModuleHandleA("shell32.dll");

#define MAKEFUNC(f) (p##f = (void*)GetProcAddress(hmod, #f))
    MAKEFUNC(SHCreateItemFromIDList);
    MAKEFUNC(SHCreateItemFromParsingName);
    MAKEFUNC(SHCreateItemFromRelativeName);
    MAKEFUNC(SHCreateItemInKnownFolder);
    MAKEFUNC(SHCreateShellItem);
    MAKEFUNC(SHCreateShellItemArray);
    MAKEFUNC(SHCreateShellItemArrayFromIDLists);
    MAKEFUNC(SHCreateShellItemArrayFromDataObject);
    MAKEFUNC(SHCreateShellItemArrayFromShellItem);
    MAKEFUNC(SHGetKnownFolderPath);
    MAKEFUNC(SHGetNameFromIDList);
    MAKEFUNC(SHGetItemFromDataObject);
    MAKEFUNC(SHGetIDListFromObject);
    MAKEFUNC(SHGetItemFromObject);
    MAKEFUNC(SHCreateDefaultContextMenu);
    MAKEFUNC(SHGetPathFromIDListEx);
    MAKEFUNC(SHGetSetFolderCustomSettings);
#undef MAKEFUNC

    /* test named exports */
    ptr = GetProcAddress(hmod, "ILFree");
    ok(broken(ptr == 0) || ptr != 0, "expected named export for ILFree\n");
    if (ptr)
    {
#define TESTNAMED(f) \
    ptr = (void*)GetProcAddress(hmod, #f); \
    ok(ptr != 0, "expected named export for " #f "\n");

        TESTNAMED(ILAppendID);
        TESTNAMED(ILClone);
        TESTNAMED(ILCloneFirst);
        TESTNAMED(ILCombine);
        TESTNAMED(ILCreateFromPath);
        TESTNAMED(ILCreateFromPathA);
        TESTNAMED(ILCreateFromPathW);
        TESTNAMED(ILFindChild);
        TESTNAMED(ILFindLastID);
        TESTNAMED(ILGetNext);
        TESTNAMED(ILGetSize);
        TESTNAMED(ILIsEqual);
        TESTNAMED(ILIsParent);
        TESTNAMED(ILRemoveLastID);
        TESTNAMED(ILSaveToStream);
#undef TESTNAMED
    }

    hmod = GetModuleHandleA("kernel32.dll");
    pIsWow64Process = (void*)GetProcAddress(hmod, "IsWow64Process");

    hr = SHGetMalloc(&ppM);
    ok(hr == S_OK, "SHGetMalloc failed %08x\n", hr);
}