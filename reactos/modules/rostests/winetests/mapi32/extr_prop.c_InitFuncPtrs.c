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
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  hMapi32 ; 
 void* pCreateIProp ; 
 void* pDeinitMapiUtil ; 
 void* pFBadColumnSet ; 
 void* pFBadProp ; 
 void* pFBadPropTag ; 
 void* pFBadRglpszA ; 
 void* pFBadRglpszW ; 
 void* pFBadRow ; 
 void* pFBadRowSet ; 
 void* pFPropCompareProp ; 
 void* pFPropContainsProp ; 
 void* pLPropCompareProp ; 
 void* pLpValFindProp ; 
 void* pMAPIAllocateBuffer ; 
 void* pMAPIAllocateMore ; 
 void* pMAPIFreeBuffer ; 
 void* pMAPIInitialize ; 
 void* pMAPIUninitialize ; 
 void* pPpropFindProp ; 
 void* pPropCopyMore ; 
 void* pScCopyProps ; 
 void* pScCountProps ; 
 void* pScInitMapiUtil ; 
 void* pScRelocProps ; 
 void* pUlPropSize ; 

__attribute__((used)) static BOOL InitFuncPtrs(void)
{
    hMapi32 = LoadLibraryA("mapi32.dll");

    pPropCopyMore = (void*)GetProcAddress(hMapi32, "PropCopyMore@16");
    pUlPropSize = (void*)GetProcAddress(hMapi32, "UlPropSize@4");
    pFPropContainsProp = (void*)GetProcAddress(hMapi32, "FPropContainsProp@12");
    pFPropCompareProp = (void*)GetProcAddress(hMapi32, "FPropCompareProp@12");
    pLPropCompareProp = (void*)GetProcAddress(hMapi32, "LPropCompareProp@8");
    pPpropFindProp = (void*)GetProcAddress(hMapi32, "PpropFindProp@12");
    pScCountProps = (void*)GetProcAddress(hMapi32, "ScCountProps@12");
    pScCopyProps = (void*)GetProcAddress(hMapi32, "ScCopyProps@16");
    pScRelocProps = (void*)GetProcAddress(hMapi32, "ScRelocProps@20");
    pLpValFindProp = (void*)GetProcAddress(hMapi32, "LpValFindProp@12");
    pFBadRglpszA = (void*)GetProcAddress(hMapi32, "FBadRglpszA@8");
    pFBadRglpszW = (void*)GetProcAddress(hMapi32, "FBadRglpszW@8");
    pFBadRowSet = (void*)GetProcAddress(hMapi32, "FBadRowSet@4");
    pFBadPropTag = (void*)GetProcAddress(hMapi32, "FBadPropTag@4");
    pFBadRow = (void*)GetProcAddress(hMapi32, "FBadRow@4");
    pFBadProp = (void*)GetProcAddress(hMapi32, "FBadProp@4");
    pFBadColumnSet = (void*)GetProcAddress(hMapi32, "FBadColumnSet@4");
    pCreateIProp = (void*)GetProcAddress(hMapi32, "CreateIProp@24");

    pScInitMapiUtil = (void*)GetProcAddress(hMapi32, "ScInitMapiUtil@4");
    pDeinitMapiUtil = (void*)GetProcAddress(hMapi32, "DeinitMapiUtil@0");
    pMAPIAllocateBuffer = (void*)GetProcAddress(hMapi32, "MAPIAllocateBuffer");
    pMAPIAllocateMore = (void*)GetProcAddress(hMapi32, "MAPIAllocateMore");
    pMAPIFreeBuffer = (void*)GetProcAddress(hMapi32, "MAPIFreeBuffer");
    pMAPIInitialize = (void*)GetProcAddress(hMapi32, "MAPIInitialize");
    pMAPIUninitialize = (void*)GetProcAddress(hMapi32, "MAPIUninitialize");

    return pMAPIAllocateBuffer && pMAPIAllocateMore && pMAPIFreeBuffer &&
           pScInitMapiUtil && pDeinitMapiUtil;
}