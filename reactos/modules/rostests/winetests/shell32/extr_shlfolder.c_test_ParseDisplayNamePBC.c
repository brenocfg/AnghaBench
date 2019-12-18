#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  float WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  GetFindData; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IBindCtx_RegisterObjectParam (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  fsbd ; 
 TYPE_1__ fsbdVtbl ; 
 int /*<<< orphan*/  fsbd_GetFindData_fail ; 
 int /*<<< orphan*/  fsbd_GetFindData_invalid ; 
 int /*<<< orphan*/  fsbd_GetFindData_junk ; 
 int /*<<< orphan*/  fsbd_GetFindData_nul ; 
 int /*<<< orphan*/  fsbd_GetFindData_valid ; 
 int /*<<< orphan*/  lstrcmpiW (float*,float*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  verify_pidl (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ParseDisplayNamePBC(void)
{
    WCHAR wFileSystemBindData[] =
        {'F','i','l','e',' ','S','y','s','t','e','m',' ','B','i','n','d',' ','D','a','t','a',0};
    WCHAR adirW[] = {'C',':','\\','f','s','b','d','d','i','r',0};
    WCHAR afileW[] = {'C',':','\\','f','s','b','d','d','i','r','\\','f','i','l','e','.','t','x','t',0};
    WCHAR afile2W[] = {'C',':','\\','f','s','b','d','d','i','r','\\','s','\\','f','i','l','e','.','t','x','t',0};
    const HRESULT exp_err = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);

    IShellFolder *psf;
    IBindCtx *pbc;
    HRESULT hres;
    ITEMIDLIST *pidl;

    /* Check if we support WCHAR functions */
    SetLastError(0xdeadbeef);
    lstrcmpiW(adirW, adirW);
    if(GetLastError() == ERROR_CALL_NOT_IMPLEMENTED){
        win_skip("Most W-calls are not implemented\n");
        return;
    }

    hres = SHGetDesktopFolder(&psf);
    ok(hres == S_OK, "SHGetDesktopFolder failed: 0x%08x\n", hres);
    if(FAILED(hres)){
        win_skip("Failed to get IShellFolder, can't run tests\n");
        return;
    }

    /* fails on unknown dir with no IBindCtx */
    hres = IShellFolder_ParseDisplayName(psf, NULL, NULL, adirW, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);
    hres = IShellFolder_ParseDisplayName(psf, NULL, NULL, afileW, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);
    hres = IShellFolder_ParseDisplayName(psf, NULL, NULL, afile2W, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);

    /* fails on unknown dir with IBindCtx with no IFileSystemBindData */
    hres = CreateBindCtx(0, &pbc);
    ok(hres == S_OK, "CreateBindCtx failed: 0x%08x\n", hres);

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == exp_err, "ParseDisplayName failed with wrong error: 0x%08x\n", hres);

    /* unknown dir with IBindCtx with IFileSystemBindData */
    hres = IBindCtx_RegisterObjectParam(pbc, wFileSystemBindData, (IUnknown*)&fsbd);
    ok(hres == S_OK, "RegisterObjectParam failed: 0x%08x\n", hres);

    /* return E_FAIL from GetFindData */
    pidl = (ITEMIDLIST*)0xdeadbeef;
    fsbdVtbl.GetFindData = fsbd_GetFindData_fail;
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, adirW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afileW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afile2W);
        ILFree(pidl);
    }

    /* set FIND_DATA struct to NULLs */
    pidl = (ITEMIDLIST*)0xdeadbeef;
    fsbdVtbl.GetFindData = fsbd_GetFindData_nul;
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, adirW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afileW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afile2W);
        ILFree(pidl);
    }

    /* set FIND_DATA struct to junk */
    pidl = (ITEMIDLIST*)0xdeadbeef;
    fsbdVtbl.GetFindData = fsbd_GetFindData_junk;
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, adirW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afileW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afile2W);
        ILFree(pidl);
    }

    /* set FIND_DATA struct to invalid data */
    pidl = (ITEMIDLIST*)0xdeadbeef;
    fsbdVtbl.GetFindData = fsbd_GetFindData_invalid;
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, adirW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afileW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afile2W);
        ILFree(pidl);
    }

    /* set FIND_DATA struct to valid data */
    pidl = (ITEMIDLIST*)0xdeadbeef;
    fsbdVtbl.GetFindData = fsbd_GetFindData_valid;
    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, adirW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, adirW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afileW, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afileW);
        ILFree(pidl);
    }

    hres = IShellFolder_ParseDisplayName(psf, NULL, pbc, afile2W, NULL, &pidl, NULL);
    ok(hres == S_OK, "ParseDisplayName failed: 0x%08x\n", hres);
    if(SUCCEEDED(hres)){
        verify_pidl(pidl, afile2W);
        ILFree(pidl);
    }

    IBindCtx_Release(pbc);
    IShellFolder_Release(psf);
}