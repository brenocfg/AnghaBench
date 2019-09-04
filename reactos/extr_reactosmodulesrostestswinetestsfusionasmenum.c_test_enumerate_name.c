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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/  IAssemblyEnum ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_CACHE_GAC ; 
 int /*<<< orphan*/  CANOF_PARSE_DISPLAY_NAME ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/ * IAssemblyEnum_GetNextAssembly (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAssemblyEnum_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAssemblyName_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  create_file_data (char*,char*,int) ; 
 int /*<<< orphan*/  create_full_path (char*) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pCreateAssemblyEnum (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pCreateAssemblyNameObject (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pGetCachePath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  to_multibyte (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_widechar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  win_skip (char*,char*) ; 

__attribute__((used)) static void test_enumerate_name(void)
{
    IAssemblyEnum *asmenum;
    IAssemblyName *asmname, *next;
    WCHAR buf[MAX_PATH];
    CHAR gac[MAX_PATH];
    CHAR path[MAX_PATH];
    CHAR disp[MAX_PATH];
    WCHAR namestr[MAX_PATH];
    CHAR exp[6][MAX_PATH];
    HRESULT hr;
    DWORD size;

    lstrcpyA(exp[0], "wine, Version=1.0.0.0, Culture=neutral, PublicKeyToken=16a3fcd171e93a8d");
    lstrcpyA(exp[1], "wine, Version=1.0.1.2, Culture=neutral, PublicKeyToken=123456789abcdef0");
    lstrcpyA(exp[2], "wine, Version=1.0.1.2, Culture=neutral, PublicKeyToken=16a3fcd171e93a8d");
    lstrcpyA(exp[3], "Wine, Version=1.0.0.0, Culture=neutral, PublicKeyToken=16a3fcd171e93a8d");
    lstrcpyA(exp[4], "Wine, Version=1.0.1.2, Culture=neutral, PublicKeyToken=123456789abcdef0");
    lstrcpyA(exp[5], "Wine, Version=1.0.1.2, Culture=neutral, PublicKeyToken=16a3fcd171e93a8d");

    size = MAX_PATH;
    hr = pGetCachePath(ASM_CACHE_GAC, buf, &size);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    to_multibyte(gac, buf);
    create_full_path(gac);

    sprintf(path, "%s\\Wine", gac);
    CreateDirectoryA(path, NULL);

    sprintf(path, "%s\\Wine\\1.0.0.0__16a3fcd171e93a8d", gac);
    CreateDirectoryA(path, NULL);

    lstrcatA(path, "\\Wine.dll");
    if (!create_file_data(path, path, 100))
    {
        win_skip("Failed to open file %s, skipping name enumeration tests\n", path);
        goto done;
    }

    sprintf(path, "%s\\Wine\\1.0.1.2__16a3fcd171e93a8d", gac);
    CreateDirectoryA(path, NULL);

    lstrcatA(path, "\\Wine.dll");
    if (!create_file_data(path, path, 100))
    {
        win_skip("Failed to open file %s, skipping name enumeration tests\n", path);
        goto done;
    }

    sprintf(path, "%s\\Wine\\1.0.1.2__123456789abcdef0", gac);
    CreateDirectoryA(path, NULL);

    lstrcatA(path, "\\Wine.dll");
    if (!create_file_data(path, path, 100))
    {
        win_skip("Failed to open file %s, skipping name enumeration tests\n", path);
        goto done;
    }

    /* test case sensitivity */
    to_widechar(namestr, "wine");
    asmname = NULL;
    hr = pCreateAssemblyNameObject(&asmname, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmname != NULL, "Expected non-NULL asmname\n");

    asmenum = NULL;
    hr = pCreateAssemblyEnum(&asmenum, NULL, asmname, ASM_CACHE_GAC, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmenum != NULL, "Expected non-NULL asmenum\n");

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[0]),
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[0], exp[1], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[1]) ||
       !lstrcmpA(disp, exp[2]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[1], exp[2], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[2]) ||
       !lstrcmpA(disp, exp[1]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[2], exp[1], disp);

    IAssemblyName_Release(next);

    next = (IAssemblyName *)0xdeadbeef;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_FALSE, "Expected S_FALSE, got %08x\n", hr);
    ok(next == (IAssemblyName *)0xdeadbeef,
       "Expected next to be unchanged, got %p\n", next);

    IAssemblyEnum_Release(asmenum);
    IAssemblyName_Release(asmname);

    /* only Version */
    to_widechar(namestr, "Wine, Version=1.0.1.2");
    asmname = NULL;
    hr = pCreateAssemblyNameObject(&asmname, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmname != NULL, "Expected non-NULL asmname\n");

    asmenum = NULL;
    hr = pCreateAssemblyEnum(&asmenum, NULL, asmname, ASM_CACHE_GAC, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmenum != NULL, "Expected non-NULL asmenum\n");

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[4]) ||
       !lstrcmpA(disp, exp[5]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[4], exp[5], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[5]) ||
       !lstrcmpA(disp, exp[4]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[5], exp[4], disp);

    IAssemblyName_Release(next);

    next = (IAssemblyName *)0xdeadbeef;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_FALSE, "Expected S_FALSE, got %08x\n", hr);
    ok(next == (IAssemblyName *)0xdeadbeef,
       "Expected next to be unchanged, got %p\n", next);

    IAssemblyEnum_Release(asmenum);
    IAssemblyName_Release(asmname);

    /* only PublicKeyToken */
    to_widechar(namestr, "Wine, PublicKeyToken=16a3fcd171e93a8d");
    asmname = NULL;
    hr = pCreateAssemblyNameObject(&asmname, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmname != NULL, "Expected non-NULL asmname\n");

    asmenum = NULL;
    hr = pCreateAssemblyEnum(&asmenum, NULL, asmname, ASM_CACHE_GAC, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmenum != NULL, "Expected non-NULL asmenum\n");

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[3]), "Expected \"%s\", got \"%s\"\n", exp[3], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[5]), "Expected \"%s\", got \"%s\"\n", exp[5], disp);

    IAssemblyName_Release(next);

    next = (IAssemblyName *)0xdeadbeef;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_FALSE, "Expected S_FALSE, got %08x\n", hr);
    ok(next == (IAssemblyName *)0xdeadbeef,
       "Expected next to be unchanged, got %p\n", next);

    IAssemblyEnum_Release(asmenum);
    IAssemblyName_Release(asmname);

    /* only Culture */
    to_widechar(namestr, "wine, Culture=neutral");
    asmname = NULL;
    hr = pCreateAssemblyNameObject(&asmname, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmname != NULL, "Expected non-NULL asmname\n");

    asmenum = NULL;
    hr = pCreateAssemblyEnum(&asmenum, NULL, asmname, ASM_CACHE_GAC, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmenum != NULL, "Expected non-NULL asmenum\n");

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[0]), "Expected \"%s\", got \"%s\"\n", exp[0], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[1]) ||
       !lstrcmpA(disp, exp[2]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[1], exp[2], disp);

    IAssemblyName_Release(next);

    next = NULL;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(next != NULL, "Expected non-NULL next\n");

    size = MAX_PATH;
    hr = IAssemblyName_GetDisplayName(next, buf, &size, 0);
    to_multibyte(disp, buf);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(!lstrcmpA(disp, exp[2]) ||
       !lstrcmpA(disp, exp[1]), /* Win98 */
       "Expected \"%s\" or \"%s\", got \"%s\"\n", exp[2], exp[1], disp);

    IAssemblyName_Release(next);

    next = (IAssemblyName *)0xdeadbeef;
    hr = IAssemblyEnum_GetNextAssembly(asmenum, NULL, &next, 0);
    ok(hr == S_FALSE, "Expected S_FALSE, got %08x\n", hr);
    ok(next == (IAssemblyName *)0xdeadbeef,
       "Expected next to be unchanged, got %p\n", next);

    IAssemblyEnum_Release(asmenum);
    IAssemblyName_Release(asmname);

done:
    sprintf(path, "%s\\Wine\\1.0.0.0__16a3fcd171e93a8d\\Wine.dll", gac);
    DeleteFileA(path);
    sprintf(path, "%s\\Wine\\1.0.1.2__16a3fcd171e93a8d\\Wine.dll", gac);
    DeleteFileA(path);
    sprintf(path, "%s\\Wine\\1.0.1.2__123456789abcdef0\\Wine.dll", gac);
    DeleteFileA(path);
    sprintf(path, "%s\\Wine\\1.0.0.0__16a3fcd171e93a8d", gac);
    RemoveDirectoryA(path);
    sprintf(path, "%s\\Wine\\1.0.1.2__16a3fcd171e93a8d", gac);
    RemoveDirectoryA(path);
    sprintf(path, "%s\\Wine\\1.0.1.2__123456789abcdef0", gac);
    RemoveDirectoryA(path);
    sprintf(path, "%s\\Wine", gac);
    RemoveDirectoryA(path);
}