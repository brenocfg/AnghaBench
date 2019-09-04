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
typedef  int /*<<< orphan*/  IFile ;
typedef  double HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int FileAttribute ;
typedef  int DWORD ;
typedef  double DATE ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 double CTL_E_FILENOTFOUND ; 
 double CTL_E_PERMISSIONDENIED ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 double E_INVALIDARG ; 
 double E_POINTER ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_COMPRESSED ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetFileAttributesW (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 double IFileSystem3_DeleteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double IFileSystem3_GetFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFile_Release (int /*<<< orphan*/ *) ; 
 double IFile_get_Attributes (int /*<<< orphan*/ *,int*) ; 
 double IFile_get_DateLastModified (int /*<<< orphan*/ *,double*) ; 
 double IFile_get_Path (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 double IFile_get_Size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double IFile_put_Attributes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryW (char*) ; 
 double S_OK ; 
 int /*<<< orphan*/ * SysAllocString (char*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 double VT_I4 ; 
 double V_I4 (int /*<<< orphan*/ *) ; 
 double V_VT (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  get_temp_path (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 double wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetFile(void)
{
    static const WCHAR slW[] = {'\\',0};
    BSTR path, str;
    WCHAR pathW[MAX_PATH];
    FileAttribute fa;
    VARIANT size;
    DWORD gfa, new_gfa;
    IFile *file;
    HRESULT hr;
    HANDLE hf;
    BOOL ret;
    DATE date;

    get_temp_path(NULL, pathW);

    path = SysAllocString(pathW);
    hr = IFileSystem3_GetFile(fs3, path, NULL);
    ok(hr == E_POINTER, "GetFile returned %x, expected E_POINTER\n", hr);
    hr = IFileSystem3_GetFile(fs3, NULL, &file);
    ok(hr == E_INVALIDARG, "GetFile returned %x, expected E_INVALIDARG\n", hr);

    file = (IFile*)0xdeadbeef;
    hr = IFileSystem3_GetFile(fs3, path, &file);
    ok(!file, "file != NULL\n");
    ok(hr == CTL_E_FILENOTFOUND, "GetFile returned %x, expected CTL_E_FILENOTFOUND\n", hr);

    hf = CreateFileW(pathW, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_READONLY, NULL);
    if(hf == INVALID_HANDLE_VALUE) {
        skip("Can't create temporary file\n");
        SysFreeString(path);
        return;
    }
    CloseHandle(hf);

    hr = IFileSystem3_GetFile(fs3, path, &file);
    ok(hr == S_OK, "GetFile returned %x, expected S_OK\n", hr);

    hr = IFile_get_DateLastModified(file, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    date = 0.0;
    hr = IFile_get_DateLastModified(file, &date);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(date > 0.0, "got %f\n", date);

    hr = IFile_get_Path(file, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    hr = IFile_get_Path(file, &str);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpiW(str, pathW), "got %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

#define FILE_ATTR_MASK (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | \
        FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_ARCHIVE | \
        FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_COMPRESSED)

    hr = IFile_get_Attributes(file, &fa);
    gfa = GetFileAttributesW(pathW) & FILE_ATTR_MASK;
    ok(hr == S_OK, "get_Attributes returned %x, expected S_OK\n", hr);
    ok(fa == gfa, "fa = %x, expected %x\n", fa, gfa);

    hr = IFile_put_Attributes(file, gfa | FILE_ATTRIBUTE_READONLY);
    ok(hr == S_OK, "put_Attributes failed: %08x\n", hr);
    new_gfa = GetFileAttributesW(pathW) & FILE_ATTR_MASK;
    ok(new_gfa == (gfa|FILE_ATTRIBUTE_READONLY), "new_gfa = %x, expected %x\n", new_gfa, gfa|FILE_ATTRIBUTE_READONLY);

    hr = IFile_get_Attributes(file, &fa);
    ok(hr == S_OK, "get_Attributes returned %x, expected S_OK\n", hr);
    ok(fa == new_gfa, "fa = %x, expected %x\n", fa, new_gfa);

    hr = IFile_put_Attributes(file, gfa);
    ok(hr == S_OK, "put_Attributes failed: %08x\n", hr);
    new_gfa = GetFileAttributesW(pathW) & FILE_ATTR_MASK;
    ok(new_gfa == gfa, "new_gfa = %x, expected %x\n", new_gfa, gfa);

    hr = IFile_get_Attributes(file, &fa);
    ok(hr == S_OK, "get_Attributes returned %x, expected S_OK\n", hr);
    ok(fa == gfa, "fa = %x, expected %x\n", fa, gfa);

    hr = IFile_get_Size(file, &size);
    ok(hr == S_OK, "get_Size returned %x, expected S_OK\n", hr);
    ok(V_VT(&size) == VT_I4, "V_VT(&size) = %d, expected VT_I4\n", V_VT(&size));
    ok(V_I4(&size) == 0, "V_I4(&size) = %d, expected 0\n", V_I4(&size));
    IFile_Release(file);

    hr = IFileSystem3_DeleteFile(fs3, path, FALSE);
    ok(hr==CTL_E_PERMISSIONDENIED || broken(hr==S_OK),
            "DeleteFile returned %x, expected CTL_E_PERMISSIONDENIED\n", hr);
    if(hr != S_OK) {
        hr = IFileSystem3_DeleteFile(fs3, path, TRUE);
        ok(hr == S_OK, "DeleteFile returned %x, expected S_OK\n", hr);
    }
    hr = IFileSystem3_DeleteFile(fs3, path, TRUE);
    ok(hr == CTL_E_FILENOTFOUND, "DeleteFile returned %x, expected CTL_E_FILENOTFOUND\n", hr);

    SysFreeString(path);

    /* try with directory */
    lstrcatW(pathW, slW);
    ret = CreateDirectoryW(pathW, NULL);
    ok(ret, "got %d, error %d\n", ret, GetLastError());

    path = SysAllocString(pathW);
    hr = IFileSystem3_GetFile(fs3, path, &file);
    ok(hr == CTL_E_FILENOTFOUND, "GetFile returned %x, expected S_OK\n", hr);
    SysFreeString(path);

    RemoveDirectoryW(pathW);
}