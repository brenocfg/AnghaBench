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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IShellLinkW ;
typedef  int /*<<< orphan*/  IPersistFile ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IShellLink ; 
 int /*<<< orphan*/  IPersistFile_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistFile_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellLinkW_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellLinkW_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellLinkW_SetArguments (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellLinkW_SetDescription (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellLinkW_SetIconLocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellLinkW_SetPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellLinkW_SetWorkingDirectory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HRESULT
CreateShellLink(
    LPCWSTR pszLinkPath,
    LPCWSTR pszCmd,
    LPCWSTR pszArg,
    LPCWSTR pszDir,
    LPCWSTR pszIconPath,
    INT iIconNr,
    LPCWSTR pszComment)
{
    IShellLinkW *psl;
    IPersistFile *ppf;

    HRESULT hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&psl);

    if (SUCCEEDED(hr))
    {
        hr = IShellLinkW_SetPath(psl, pszCmd);

        if (pszArg)
            hr = IShellLinkW_SetArguments(psl, pszArg);

        if (pszDir)
            hr = IShellLinkW_SetWorkingDirectory(psl, pszDir);

        if (pszIconPath)
            hr = IShellLinkW_SetIconLocation(psl, pszIconPath, iIconNr);

        if (pszComment)
            hr = IShellLinkW_SetDescription(psl, pszComment);

        hr = IShellLinkW_QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hr))
        {
            hr = IPersistFile_Save(ppf, pszLinkPath, TRUE);
            IPersistFile_Release(ppf);
        }

        IShellLinkW_Release(psl);
    }

    return hr;
}