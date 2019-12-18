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
typedef  void* PVOID ;

/* Variables and functions */
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 void* pAcceptSecurityContext ; 
 void* pAcquireCredentialsHandleA ; 
 void* pCompleteAuthToken ; 
 void* pDeleteSecurityContext ; 
 void* pEnumerateSecurityPackagesA ; 
 void* pFreeContextBuffer ; 
 void* pFreeCredentialsHandle ; 
 void* pInitSecurityInterfaceA ; 
 void* pInitializeSecurityContextA ; 
 void* pQueryContextAttributesA ; 
 void* pQuerySecurityPackageInfoA ; 
 scalar_t__ secdll ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    secdll = LoadLibraryA("secur32.dll");
    if(!secdll)
        secdll = LoadLibraryA("security.dll");
    if(secdll)
    {
        pInitSecurityInterfaceA = (PVOID)GetProcAddress(secdll, "InitSecurityInterfaceA");
        pEnumerateSecurityPackagesA = (PVOID)GetProcAddress(secdll, "EnumerateSecurityPackagesA");
        pFreeContextBuffer = (PVOID)GetProcAddress(secdll, "FreeContextBuffer");
        pQuerySecurityPackageInfoA = (PVOID)GetProcAddress(secdll, "QuerySecurityPackageInfoA");
        pAcquireCredentialsHandleA = (PVOID)GetProcAddress(secdll, "AcquireCredentialsHandleA");
        pInitializeSecurityContextA = (PVOID)GetProcAddress(secdll, "InitializeSecurityContextA");
        pCompleteAuthToken = (PVOID)GetProcAddress(secdll, "CompleteAuthToken");
        pAcceptSecurityContext = (PVOID)GetProcAddress(secdll, "AcceptSecurityContext");
        pFreeCredentialsHandle = (PVOID)GetProcAddress(secdll, "FreeCredentialsHandle");
        pDeleteSecurityContext = (PVOID)GetProcAddress(secdll, "DeleteSecurityContext");
        pQueryContextAttributesA = (PVOID)GetProcAddress(secdll, "QueryContextAttributesA");
    }
}