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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IFolder ;
typedef  int /*<<< orphan*/  IFileCollection ;
typedef  int /*<<< orphan*/  IFile ;
typedef  int /*<<< orphan*/  IEnumVARIANT ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_File ; 
 int /*<<< orphan*/  CLSID_Files ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFileW (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int E_NOINTERFACE ; 
 int E_POINTER ; 
 int /*<<< orphan*/  FILE_FLAG_DELETE_ON_CLOSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GET_REFCOUNT (int /*<<< orphan*/ *) ; 
 int IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int IEnumVARIANT_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IEnumVARIANT_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IEnumVARIANT_Release (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Reset (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Skip (int /*<<< orphan*/ *,int) ; 
 int IFileCollection_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFileCollection_Release (int /*<<< orphan*/ *) ; 
 int IFileCollection_get_Count (int /*<<< orphan*/ *,int*) ; 
 int IFileCollection_get__NewEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IFileSystem3_GetFolder (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFile_Release (int /*<<< orphan*/ *) ; 
 int IFile_get_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFolder_Release (int /*<<< orphan*/ *) ; 
 int IFolder_get_Files (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IEnumVARIANT ; 
 int /*<<< orphan*/  IID_IFile ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryW (char*) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/ * SysAllocString (char*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int VT_DISPATCH ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  get_temp_path (char const*,char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  test_provideclassinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_FileCollection(void)
{
    static const WCHAR fooW[] = {'\\','f','o','o',0};
    static const WCHAR aW[] = {'\\','a',0};
    static const WCHAR bW[] = {'\\','b',0};
    static const WCHAR cW[] = {'\\','c',0};
    WCHAR buffW[MAX_PATH], pathW[MAX_PATH];
    IFolder *folder;
    IFileCollection *files;
    IFile *file;
    IEnumVARIANT *enumvar, *clone;
    LONG count, ref, ref2, i;
    IUnknown *unk, *unk2;
    ULONG fetched;
    VARIANT var, var2[2];
    HRESULT hr;
    BSTR str;
    HANDLE file_a, file_b, file_c;
    int found_a = 0, found_b = 0, found_c = 0;

    get_temp_path(fooW, buffW);
    CreateDirectoryW(buffW, NULL);

    str = SysAllocString(buffW);
    hr = IFileSystem3_GetFolder(fs3, str, &folder);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(str);

    hr = IFolder_get_Files(folder, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    lstrcpyW(pathW, buffW);
    lstrcatW(pathW, aW);
    file_a = CreateFileW(pathW, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                         FILE_FLAG_DELETE_ON_CLOSE, 0);
    lstrcpyW(pathW, buffW);
    lstrcatW(pathW, bW);
    file_b = CreateFileW(pathW, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                         FILE_FLAG_DELETE_ON_CLOSE, 0);

    hr = IFolder_get_Files(folder, &files);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    test_provideclassinfo(files, &CLSID_Files);
    IFolder_Release(folder);

    count = 0;
    hr = IFileCollection_get_Count(files, &count);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(count == 2, "got %d\n", count);

    lstrcpyW(pathW, buffW);
    lstrcatW(pathW, cW);
    file_c = CreateFileW(pathW, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                         FILE_FLAG_DELETE_ON_CLOSE, 0);

    /* every time property is requested it scans directory */
    count = 0;
    hr = IFileCollection_get_Count(files, &count);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(count == 3, "got %d\n", count);

    hr = IFileCollection_get__NewEnum(files, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    hr = IFileCollection_QueryInterface(files, &IID_IEnumVARIANT, (void**)&unk);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    /* NewEnum creates new instance each time it's called */
    ref = GET_REFCOUNT(files);

    unk = NULL;
    hr = IFileCollection_get__NewEnum(files, &unk);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ref2 = GET_REFCOUNT(files);
    ok(ref2 == ref + 1, "got %d, %d\n", ref2, ref);

    unk2 = NULL;
    hr = IFileCollection_get__NewEnum(files, &unk2);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(unk != unk2, "got %p, %p\n", unk2, unk);
    IUnknown_Release(unk2);

    /* now get IEnumVARIANT */
    ref = GET_REFCOUNT(files);
    hr = IUnknown_QueryInterface(unk, &IID_IEnumVARIANT, (void**)&enumvar);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ref2 = GET_REFCOUNT(files);
    ok(ref2 == ref, "got %d, %d\n", ref2, ref);

    /* clone enumerator */
    hr = IEnumVARIANT_Clone(enumvar, &clone);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(clone != enumvar, "got %p, %p\n", enumvar, clone);
    IEnumVARIANT_Release(clone);

    hr = IEnumVARIANT_Reset(enumvar);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    for (i = 0; i < 3; i++)
    {
        VariantInit(&var);
        fetched = 0;
        hr = IEnumVARIANT_Next(enumvar, 1, &var, &fetched);
        ok(hr == S_OK, "%d: got 0x%08x\n", i, hr);
        ok(fetched == 1, "%d: got %d\n", i, fetched);
        ok(V_VT(&var) == VT_DISPATCH, "%d: got type %d\n", i, V_VT(&var));

        hr = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IFile, (void **)&file);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        test_provideclassinfo(file, &CLSID_File);

        str = NULL;
        hr = IFile_get_Name(file, &str);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        if (!lstrcmpW(str, aW + 1))
            found_a++;
        else if (!lstrcmpW(str, bW + 1))
            found_b++;
        else if (!lstrcmpW(str, cW + 1))
            found_c++;
        else
            ok(0, "unexpected file %s was found\n", wine_dbgstr_w(str));
        SysFreeString(str);

        IFile_Release(file);
        VariantClear(&var);
    }

    ok(found_a == 1 && found_b == 1 && found_c == 1,
       "each file should be found 1 time instead of %d/%d/%d\n",
       found_a, found_b, found_c);

    VariantInit(&var);
    fetched = -1;
    hr = IEnumVARIANT_Next(enumvar, 1, &var, &fetched);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(fetched == 0, "got %d\n", fetched);

    hr = IEnumVARIANT_Reset(enumvar);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IEnumVARIANT_Skip(enumvar, 2);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IEnumVARIANT_Skip(enumvar, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    VariantInit(&var2[0]);
    VariantInit(&var2[1]);
    fetched = -1;
    hr = IEnumVARIANT_Next(enumvar, 0, var2, &fetched);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(fetched == 0, "got %d\n", fetched);
    fetched = -1;
    hr = IEnumVARIANT_Next(enumvar, 2, var2, &fetched);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(fetched == 1, "got %d\n", fetched);
    ok(V_VT(&var2[0]) == VT_DISPATCH, "got type %d\n", V_VT(&var2[0]));
    VariantClear(&var2[0]);
    VariantClear(&var2[1]);

    IEnumVARIANT_Release(enumvar);
    IUnknown_Release(unk);

    CloseHandle(file_a);
    CloseHandle(file_b);
    CloseHandle(file_c);
    RemoveDirectoryW(buffW);

    IFileCollection_Release(files);
}