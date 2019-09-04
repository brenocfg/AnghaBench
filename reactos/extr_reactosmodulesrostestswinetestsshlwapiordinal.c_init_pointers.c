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
typedef  char* LPSTR ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hShlwapi ; 
 void* pConnectToConnectionPoint ; 
 void* pDllGetVersion ; 
 void* pGUIDFromStringA ; 
 void* pGetAcceptLanguagesA ; 
 void* pGetShellSecurityDescriptor ; 
 void* pIConnectionPoint_InvokeWithCancel ; 
 void* pIConnectionPoint_SimpleInvoke ; 
 void* pIUnknown_GetClassID ; 
 void* pIUnknown_ProfferService ; 
 void* pIUnknown_QueryServiceExec ; 
 void* pSHAllocShared ; 
 void* pSHCreateWorkerWindowA ; 
 void* pSHFormatDateTimeA ; 
 void* pSHFormatDateTimeW ; 
 void* pSHFreeShared ; 
 void* pSHGetIniStringW ; 
 void* pSHGetObjectCompatFlags ; 
 void* pSHGetShellKey ; 
 void* pSHIShellFolder_EnumObjects ; 
 void* pSHLockShared ; 
 void* pSHMapHandle ; 
 void* pSHPackDispParams ; 
 void* pSHPropertyBag_ReadLONG ; 
 void* pSHSearchMapInt ; 
 void* pSHSetIniStringW ; 
 void* pSHSetParentHwnd ; 
 void* pSHSetWindowBits ; 
 void* pSHUnlockShared ; 
 void* pSKAllocValueW ; 
 void* pSKDeleteValueW ; 
 void* pSKGetValueW ; 
 void* pSKSetValueW ; 

__attribute__((used)) static void init_pointers(void)
{
#define MAKEFUNC(f, ord) (p##f = (void*)GetProcAddress(hShlwapi, (LPSTR)(ord)))
    MAKEFUNC(SHAllocShared, 7);
    MAKEFUNC(SHLockShared, 8);
    MAKEFUNC(SHUnlockShared, 9);
    MAKEFUNC(SHFreeShared, 10);
    MAKEFUNC(SHMapHandle, 11);
    MAKEFUNC(GetAcceptLanguagesA, 14);
    MAKEFUNC(SHSetWindowBits, 165);
    MAKEFUNC(SHSetParentHwnd, 167);
    MAKEFUNC(ConnectToConnectionPoint, 168);
    MAKEFUNC(IUnknown_GetClassID, 175);
    MAKEFUNC(SHSearchMapInt, 198);
    MAKEFUNC(SHCreateWorkerWindowA, 257);
    MAKEFUNC(GUIDFromStringA, 269);
    MAKEFUNC(SHPackDispParams, 282);
    MAKEFUNC(IConnectionPoint_InvokeWithCancel, 283);
    MAKEFUNC(IConnectionPoint_SimpleInvoke, 284);
    MAKEFUNC(SHGetIniStringW, 294);
    MAKEFUNC(SHSetIniStringW, 295);
    MAKEFUNC(SHFormatDateTimeA, 353);
    MAKEFUNC(SHFormatDateTimeW, 354);
    MAKEFUNC(SHIShellFolder_EnumObjects, 404);
    MAKEFUNC(GetShellSecurityDescriptor, 475);
    MAKEFUNC(SHGetObjectCompatFlags, 476);
    MAKEFUNC(IUnknown_QueryServiceExec, 484);
    MAKEFUNC(SHGetShellKey, 491);
    MAKEFUNC(SHPropertyBag_ReadLONG, 496);
    MAKEFUNC(IUnknown_ProfferService, 514);
    MAKEFUNC(SKGetValueW, 516);
    MAKEFUNC(SKSetValueW, 517);
    MAKEFUNC(SKDeleteValueW, 518);
    MAKEFUNC(SKAllocValueW, 519);
#undef MAKEFUNC

    pDllGetVersion = (void*)GetProcAddress(hShlwapi, "DllGetVersion");
}