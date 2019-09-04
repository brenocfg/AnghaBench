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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  STRRET ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LPSHELLFOLDER ;
typedef  scalar_t__ LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
#define  ILGDN_FORPARSING 130 
#define  ILGDN_INFOLDER 129 
#define  ILGDN_NORMAL 128 
 int /*<<< orphan*/  IShellFolder_GetDisplayNameOf (scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (scalar_t__) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  SHBindToParent (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int SHGDN_FORADDRESSBAR ; 
 int SHGDN_FORPARSING ; 
 int SHGDN_INFOLDER ; 
 int SHGDN_NORMAL ; 
 int /*<<< orphan*/  SHGetDesktopFolder (scalar_t__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrRetToStrNW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

BOOL ILGetDisplayNameExW(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, LPWSTR path, DWORD type)
{
    LPSHELLFOLDER psfParent, lsf = psf;
    HRESULT ret = NO_ERROR;
    LPCITEMIDLIST pidllast;
    STRRET strret;
    DWORD flag;

    TRACE("%p %p %p %x\n", psf, pidl, path, type);

    if (!pidl || !path)
        return FALSE;

    if (!lsf)
    {
        ret = SHGetDesktopFolder(&lsf);
        if (FAILED(ret))
            return FALSE;
    }

    switch (type)
    {
    case ILGDN_FORPARSING:
        flag = SHGDN_FORPARSING | SHGDN_FORADDRESSBAR;
        break;
    case ILGDN_NORMAL:
        flag = SHGDN_NORMAL;
        break;
    case ILGDN_INFOLDER:
        flag = SHGDN_INFOLDER;
        break;
    default:
        FIXME("Unknown type parameter = %x\n", type);
        flag = SHGDN_FORPARSING | SHGDN_FORADDRESSBAR;
        break;
    }

    if (!*(const WORD*)pidl || type == ILGDN_FORPARSING)
    {
        ret = IShellFolder_GetDisplayNameOf(lsf, pidl, flag, &strret);
        if (SUCCEEDED(ret))
        {
            if(!StrRetToStrNW(path, MAX_PATH, &strret, pidl))
                ret = E_FAIL;
        }
    }
    else
    {
        ret = SHBindToParent(pidl, &IID_IShellFolder, (LPVOID*)&psfParent, &pidllast);
        if (SUCCEEDED(ret))
        {
            ret = IShellFolder_GetDisplayNameOf(psfParent, pidllast, flag, &strret);
            if (SUCCEEDED(ret))
            {
                if(!StrRetToStrNW(path, MAX_PATH, &strret, pidllast))
                    ret = E_FAIL;
            }
            IShellFolder_Release(psfParent);
        }
    }

    TRACE("%p %p %s\n", psf, pidl, debugstr_w(path));

    if (!psf)
        IShellFolder_Release(lsf);
    return SUCCEEDED(ret);
}