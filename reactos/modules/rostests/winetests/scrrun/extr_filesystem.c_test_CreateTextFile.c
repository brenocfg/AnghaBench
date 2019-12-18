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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  ITextStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__* BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CLSID_TextStream ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CTL_E_BADFILEMODE ; 
 int /*<<< orphan*/  CTL_E_FILEALREADYEXISTS ; 
 int /*<<< orphan*/  CTL_E_PATHNOTFOUND ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateDirectoryW (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFileW (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileW (scalar_t__*) ; 
 int /*<<< orphan*/  E_VAR_NOT_SET ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  ForReading ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetLastError () ; 
 int /*<<< orphan*/  IFileSystem3_CreateTextFile (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFileSystem3_OpenTextFile (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ITextStream_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextStream_Read (int /*<<< orphan*/ *,int,scalar_t__**) ; 
 int /*<<< orphan*/  ITextStream_ReadAll (int /*<<< orphan*/ *,scalar_t__**) ; 
 int /*<<< orphan*/  ITextStream_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  RemoveDirectoryW (scalar_t__*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__* SysAllocString (scalar_t__*) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__*) ; 
 int /*<<< orphan*/  TristateFalse ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  get_temp_filepath (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  test_provideclassinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testfileW ; 
 int /*<<< orphan*/  utf16bom ; 
 int wine_dbgstr_w (scalar_t__*) ; 

__attribute__((used)) static void test_CreateTextFile(void)
{
    WCHAR pathW[MAX_PATH], dirW[MAX_PATH], buffW[10];
    ITextStream *stream;
    BSTR nameW, str;
    HANDLE file;
    HRESULT hr;
    BOOL ret;

    get_temp_filepath(testfileW, pathW, dirW);

    /* dir doesn't exist */
    nameW = SysAllocString(pathW);
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_FALSE, VARIANT_FALSE, &stream);
    ok(hr == CTL_E_PATHNOTFOUND, "got 0x%08x\n", hr);

    ret = CreateDirectoryW(dirW, NULL);
    ok(ret, "got %d, %d\n", ret, GetLastError());

    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_FALSE, VARIANT_FALSE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    test_provideclassinfo(stream, &CLSID_TextStream);

    hr = ITextStream_Read(stream, 1, &str);
    ok(hr == CTL_E_BADFILEMODE, "got 0x%08x\n", hr);

    hr = ITextStream_Close(stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = ITextStream_Read(stream, 1, &str);
    ok(hr == CTL_E_BADFILEMODE || hr == E_VAR_NOT_SET, "got 0x%08x\n", hr);

    hr = ITextStream_Close(stream);
    ok(hr == S_FALSE || hr == E_VAR_NOT_SET, "got 0x%08x\n", hr);

    ITextStream_Release(stream);

    /* check it's created */
    file = CreateFileW(pathW, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "got %p\n", file);
    CloseHandle(file);

    /* try to create again with no-overwrite mode */
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_FALSE, VARIANT_FALSE, &stream);
    ok(hr == CTL_E_FILEALREADYEXISTS, "got 0x%08x\n", hr);

    /* now overwrite */
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_TRUE, VARIANT_FALSE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ITextStream_Release(stream);

    /* overwrite in Unicode mode, check for BOM */
    hr = IFileSystem3_CreateTextFile(fs3, nameW, VARIANT_TRUE, VARIANT_TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ITextStream_Release(stream);

    /* File was created in Unicode mode, it contains 0xfffe BOM. Opening it in non-Unicode mode
       treats BOM like a valuable data with appropriate CP_ACP -> WCHAR conversion. */
    buffW[0] = 0;
    MultiByteToWideChar(CP_ACP, 0, utf16bom, -1, buffW, ARRAY_SIZE(buffW));

    hr = IFileSystem3_OpenTextFile(fs3, nameW, ForReading, VARIANT_FALSE, TristateFalse, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = ITextStream_ReadAll(stream, &str);
    ok(hr == S_FALSE || broken(hr == S_OK) /* win2k */, "got 0x%08x\n", hr);
    ok(!lstrcmpW(str, buffW), "got %s, expected %s\n", wine_dbgstr_w(str), wine_dbgstr_w(buffW));
    SysFreeString(str);
    ITextStream_Release(stream);

    DeleteFileW(nameW);
    RemoveDirectoryW(dirW);
    SysFreeString(nameW);
}