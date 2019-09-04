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
typedef  float WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  float* BSTR ;

/* Variables and functions */
 scalar_t__ CTL_E_FILEALREADYEXISTS ; 
 scalar_t__ CTL_E_FILENOTFOUND ; 
 scalar_t__ CTL_E_PATHNOTFOUND ; 
 int CreateDirectoryW (float const*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetFileAttributesW (float*) ; 
 scalar_t__ IFileSystem3_CopyFile (int /*<<< orphan*/ ,float*,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ IFileSystem3_CopyFolder (int /*<<< orphan*/ ,float*,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ IFileSystem3_DeleteFile (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ IFileSystem3_DeleteFolder (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int RemoveDirectoryW (float*) ; 
 scalar_t__ S_OK ; 
 float* SysAllocString (float const*) ; 
 int /*<<< orphan*/  SysFreeString (float*) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int create_file (float*) ; 
 int /*<<< orphan*/  create_path (float const*,float const*,float*) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ wine_dbgstr_w (float*) ; 

__attribute__((used)) static void test_CopyFolder(void)
{
    static const WCHAR filesystem3_dir[] = {'f','i','l','e','s','y','s','t','e','m','3','_','t','e','s','t',0};
    static const WCHAR s1[] = {'s','r','c','1',0};
    static const WCHAR s[] = {'s','r','c','*',0};
    static const WCHAR d[] = {'d','s','t',0};
    static const WCHAR empty[] = {0};

    WCHAR tmp[MAX_PATH];
    BSTR bsrc, bdst;
    HRESULT hr;

    if(!CreateDirectoryW(filesystem3_dir, NULL)) {
        skip("can't create temporary directory\n");
        return;
    }

    create_path(filesystem3_dir, s1, tmp);
    bsrc = SysAllocString(tmp);
    create_path(filesystem3_dir, d, tmp);
    bdst = SysAllocString(tmp);
    hr = IFileSystem3_CopyFile(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_FILENOTFOUND, "CopyFile returned %x, expected CTL_E_FILENOTFOUND\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_PATHNOTFOUND, "CopyFolder returned %x, expected CTL_E_PATHNOTFOUND\n", hr);

    ok(create_file(bsrc), "can't create %s file\n", wine_dbgstr_w(bsrc));
    hr = IFileSystem3_CopyFile(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFile returned %x, expected S_OK\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_PATHNOTFOUND, "CopyFolder returned %x, expected CTL_E_PATHNOTFOUND\n", hr);

    hr = IFileSystem3_DeleteFile(fs3, bsrc, VARIANT_FALSE);
    ok(hr == S_OK, "DeleteFile returned %x, expected S_OK\n", hr);

    ok(CreateDirectoryW(bsrc, NULL), "can't create %s\n", wine_dbgstr_w(bsrc));
    hr = IFileSystem3_CopyFile(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_FILENOTFOUND, "CopyFile returned %x, expected CTL_E_FILENOTFOUND\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_FILEALREADYEXISTS, "CopyFolder returned %x, expected CTL_E_FILEALREADYEXISTS\n", hr);

    hr = IFileSystem3_DeleteFile(fs3, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "DeleteFile returned %x, expected S_OK\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);
    create_path(tmp, s1, tmp);
    ok(GetFileAttributesW(tmp) == INVALID_FILE_ATTRIBUTES,
            "%s file exists\n", wine_dbgstr_w(tmp));

    create_path(filesystem3_dir, d, tmp);
    create_path(tmp, empty, tmp);
    SysFreeString(bdst);
    bdst = SysAllocString(tmp);
    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);
    create_path(tmp, s1, tmp);
    ok(GetFileAttributesW(tmp) != INVALID_FILE_ATTRIBUTES,
            "%s directory doesn't exist\n", wine_dbgstr_w(tmp));
    ok(RemoveDirectoryW(tmp), "can't remove %s directory\n", wine_dbgstr_w(tmp));
    create_path(filesystem3_dir, d, tmp);
    SysFreeString(bdst);
    bdst = SysAllocString(tmp);


    create_path(filesystem3_dir, s, tmp);
    SysFreeString(bsrc);
    bsrc = SysAllocString(tmp);
    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);
    create_path(filesystem3_dir, d, tmp);
    create_path(tmp, s1, tmp);
    ok(GetFileAttributesW(tmp) != INVALID_FILE_ATTRIBUTES,
            "%s directory doesn't exist\n", wine_dbgstr_w(tmp));

    hr = IFileSystem3_DeleteFolder(fs3, bdst, VARIANT_FALSE);
    ok(hr == S_OK, "DeleteFolder returned %x, expected S_OK\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == CTL_E_PATHNOTFOUND, "CopyFolder returned %x, expected CTL_E_PATHNOTFOUND\n", hr);

    create_path(filesystem3_dir, s1, tmp);
    SysFreeString(bsrc);
    bsrc = SysAllocString(tmp);
    create_path(tmp, s1, tmp);
    ok(create_file(tmp), "can't create %s file\n", wine_dbgstr_w(tmp));
    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_FALSE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_FALSE);
    ok(hr == CTL_E_FILEALREADYEXISTS, "CopyFolder returned %x, expected CTL_E_FILEALREADYEXISTS\n", hr);

    hr = IFileSystem3_CopyFolder(fs3, bsrc, bdst, VARIANT_TRUE);
    ok(hr == S_OK, "CopyFolder returned %x, expected S_OK\n", hr);
    SysFreeString(bsrc);
    SysFreeString(bdst);

    bsrc = SysAllocString(filesystem3_dir);
    hr = IFileSystem3_DeleteFolder(fs3, bsrc, VARIANT_FALSE);
    ok(hr == S_OK, "DeleteFolder returned %x, expected S_OK\n", hr);
    SysFreeString(bsrc);
}