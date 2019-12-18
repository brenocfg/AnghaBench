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
typedef  int /*<<< orphan*/  buffW ;
typedef  int /*<<< orphan*/  buffA ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ITextStream ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetLastError () ; 
 scalar_t__ IFileSystem3_CreateTextFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ITextStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextStream_WriteLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int ReadFile (scalar_t__,char*,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveDirectoryW (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  crlfW ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  get_temp_filepath (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  testfileW ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_WriteLine(void)
{
    WCHAR pathW[MAX_PATH], dirW[MAX_PATH];
    WCHAR buffW[MAX_PATH], buff2W[MAX_PATH];
    char buffA[MAX_PATH];
    ITextStream *stream;
    DWORD r, len;
    HANDLE file;
    BSTR nameW;
    HRESULT hr;
    BOOL ret;

    get_temp_filepath(testfileW, pathW, dirW);

    ret = CreateDirectoryW(dirW, NULL);
    ok(ret, "got %d, %d\n", ret, GetLastError());

    /* create as ASCII file first */
    nameW = SysAllocString(pathW);
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_FALSE, VARIANT_FALSE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = ITextStream_WriteLine(stream, nameW);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ITextStream_Release(stream);

    /* check contents */
    file = CreateFileW(pathW, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "got %p\n", file);
    r = 0;
    ret = ReadFile(file, buffA, sizeof(buffA), &r, NULL);
    ok(ret && r, "read %d, got %d, %d\n", r, ret, GetLastError());

    len = MultiByteToWideChar(CP_ACP, 0, buffA, r, buffW, ARRAY_SIZE(buffW));
    buffW[len] = 0;
    lstrcpyW(buff2W, nameW);
    lstrcatW(buff2W, crlfW);
    ok(!lstrcmpW(buff2W, buffW), "got %s, expected %s\n", wine_dbgstr_w(buffW), wine_dbgstr_w(buff2W));
    CloseHandle(file);
    DeleteFileW(nameW);

    /* same for unicode file */
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_FALSE, VARIANT_TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = ITextStream_WriteLine(stream, nameW);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ITextStream_Release(stream);

    /* check contents */
    file = CreateFileW(pathW, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "got %p\n", file);
    r = 0;
    ret = ReadFile(file, buffW, sizeof(buffW), &r, NULL);
    ok(ret && r, "read %d, got %d, %d\n", r, ret, GetLastError());
    buffW[r/sizeof(WCHAR)] = 0;

    buff2W[0] = 0xfeff;
    buff2W[1] = 0;
    lstrcatW(buff2W, nameW);
    lstrcatW(buff2W, crlfW);
    ok(!lstrcmpW(buff2W, buffW), "got %s, expected %s\n", wine_dbgstr_w(buffW), wine_dbgstr_w(buff2W));
    CloseHandle(file);
    DeleteFileW(nameW);

    RemoveDirectoryW(dirW);
    SysFreeString(nameW);
}