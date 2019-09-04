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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IAssemblyCache ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CLDB_E_FILE_OLDVER ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ E_ACCESSDENIED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IAssemblyCache_InstallAssembly (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAssemblyCache_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAssemblyCache_UninstallAssembly (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_assembly (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCreateAssemblyCache (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL check_dotnet20(void)
{
    IAssemblyCache *cache;
    HRESULT hr;
    BOOL ret = FALSE;
    ULONG disp;

    static const WCHAR winedll[] = {'w','i','n','e','.','d','l','l',0};

    create_assembly("wine.dll");

    hr = pCreateAssemblyCache(&cache, 0);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IAssemblyCache_InstallAssembly(cache, 0, winedll, NULL);
    if (hr == S_OK)
        ret = TRUE;
    else if (hr == CLDB_E_FILE_OLDVER)
        win_skip("Tests can't be run on older .NET version (.NET 1.1)\n");
    else if (hr == E_ACCESSDENIED)
        skip("Not enough rights to install an assembly\n");
    else
        ok(0, "Expected S_OK, got %08x\n", hr);

    DeleteFileA("wine.dll");
    IAssemblyCache_UninstallAssembly(cache, 0, winedll, NULL, &disp);
    IAssemblyCache_Release(cache);
    return ret;
}