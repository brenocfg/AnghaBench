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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pD3DReadFileToBlob ; 

__attribute__((used)) static BOOL load_d3dcompiler_47(void)
{
    HMODULE module;

    if (!(module = LoadLibraryA("d3dcompiler_47.dll")))
        return FALSE;

    pD3DReadFileToBlob = (void *)GetProcAddress(module, "D3DReadFileToBlob");
    return TRUE;
}