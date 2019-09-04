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

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pFmtIdToPropStgName ; 
 void* pPropStgNameToFmtId ; 
 void* pStgCreatePropSetStg ; 
 void* pStgCreatePropStg ; 
 void* pStgOpenPropStg ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hmod = GetModuleHandleA("ole32.dll");
    pFmtIdToPropStgName = (void*)GetProcAddress(hmod, "FmtIdToPropStgName");
    pPropStgNameToFmtId = (void*)GetProcAddress(hmod, "PropStgNameToFmtId");
    pStgCreatePropSetStg = (void*)GetProcAddress(hmod, "StgCreatePropSetStg");
    pStgCreatePropStg = (void*)GetProcAddress(hmod, "StgCreatePropStg");
    pStgOpenPropStg = (void*)GetProcAddress(hmod, "StgOpenPropStg");
}