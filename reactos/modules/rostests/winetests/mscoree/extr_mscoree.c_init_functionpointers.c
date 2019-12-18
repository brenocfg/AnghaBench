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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hmscoree ; 
 void* pCreateConfigStream ; 
 void* pGetCORSystemDirectory ; 
 void* pGetCORVersion ; 
 void* pGetRequestedRuntimeInfo ; 
 void* pLoadLibraryShim ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_functionpointers(void)
{
    hmscoree = LoadLibraryA("mscoree.dll");

    if (!hmscoree)
    {
        win_skip("mscoree.dll not available\n");
        return FALSE;
    }

    pGetCORVersion = (void *)GetProcAddress(hmscoree, "GetCORVersion");
    pGetCORSystemDirectory = (void *)GetProcAddress(hmscoree, "GetCORSystemDirectory");
    pGetRequestedRuntimeInfo = (void *)GetProcAddress(hmscoree, "GetRequestedRuntimeInfo");
    pLoadLibraryShim = (void *)GetProcAddress(hmscoree, "LoadLibraryShim");
    pCreateConfigStream = (void *)GetProcAddress(hmscoree, "CreateConfigStream");

    if (!pGetCORVersion || !pGetCORSystemDirectory || !pGetRequestedRuntimeInfo || !pLoadLibraryShim)
    {
        win_skip("functions not available\n");
        FreeLibrary(hmscoree);
        return FALSE;
    }

    return TRUE;
}