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
 void* pCryptCATAdminAcquireContext ; 
 void* pCryptCATAdminAddCatalog ; 
 void* pCryptCATAdminCalcHashFromFileHandle ; 
 void* pCryptCATAdminReleaseCatalogContext ; 
 void* pCryptCATAdminReleaseContext ; 
 void* pCryptCATAdminRemoveCatalog ; 
 void* pCryptCATCDFClose ; 
 void* pCryptCATCDFEnumCatAttributes ; 
 void* pCryptCATCDFEnumMembersByCDFTagEx ; 
 void* pCryptCATCDFOpen ; 
 void* pCryptCATCatalogInfoFromContext ; 
 void* pCryptCATClose ; 
 void* pCryptCATEnumerateAttr ; 
 void* pCryptCATEnumerateCatAttr ; 
 void* pCryptCATEnumerateMember ; 
 void* pCryptCATOpen ; 
 void* pGetSignedDataMsg ; 
 void* pPutSignedDataMsg ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    HMODULE hWintrust = GetModuleHandleA("wintrust.dll");

#define WINTRUST_GET_PROC(func) \
    p ## func = (void*)GetProcAddress(hWintrust, #func); \
    if(!p ## func) { \
      trace("GetProcAddress(%s) failed\n", #func); \
    }

    WINTRUST_GET_PROC(CryptCATAdminAcquireContext)
    WINTRUST_GET_PROC(CryptCATAdminReleaseContext)
    WINTRUST_GET_PROC(CryptCATAdminCalcHashFromFileHandle)
    WINTRUST_GET_PROC(CryptCATAdminAddCatalog)
    WINTRUST_GET_PROC(CryptCATAdminRemoveCatalog)
    WINTRUST_GET_PROC(CryptCATAdminReleaseCatalogContext)
    WINTRUST_GET_PROC(CryptCATOpen)
    WINTRUST_GET_PROC(CryptCATCatalogInfoFromContext)
    WINTRUST_GET_PROC(CryptCATCDFClose)
    WINTRUST_GET_PROC(CryptCATCDFEnumCatAttributes)
    WINTRUST_GET_PROC(CryptCATCDFEnumMembersByCDFTagEx)
    WINTRUST_GET_PROC(CryptCATCDFOpen)
    WINTRUST_GET_PROC(CryptCATEnumerateCatAttr)
    WINTRUST_GET_PROC(CryptCATEnumerateMember)
    WINTRUST_GET_PROC(CryptCATEnumerateAttr)
    WINTRUST_GET_PROC(CryptCATClose)

#undef WINTRUST_GET_PROC

    pGetSignedDataMsg = (void*)GetProcAddress(hWintrust, "CryptSIPGetSignedDataMsg");
    if(!pGetSignedDataMsg)
        trace("GetProcAddress(CryptSIPGetSignedDataMsg) failed\n");

    pPutSignedDataMsg = (void*)GetProcAddress(hWintrust, "CryptSIPPutSignedDataMsg");
    if(!pPutSignedDataMsg)
        trace("GetProcAddress(CryptSIPPutSignedDataMsg) failed\n");
}