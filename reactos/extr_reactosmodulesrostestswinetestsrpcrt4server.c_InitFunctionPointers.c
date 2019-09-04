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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  old_windows_version ; 
 void* pNDRSContextMarshall2 ; 
 void* pNDRSContextUnmarshall2 ; 
 void* pRpcBindingSetAuthInfoExA ; 
 void* pRpcServerRegisterAuthInfoA ; 
 void* pRpcServerRegisterIfEx ; 

__attribute__((used)) static void InitFunctionPointers(void)
{
    HMODULE hrpcrt4 = GetModuleHandleA("rpcrt4.dll");

    pNDRSContextMarshall2 = (void *)GetProcAddress(hrpcrt4, "NDRSContextMarshall2");
    pNDRSContextUnmarshall2 = (void *)GetProcAddress(hrpcrt4, "NDRSContextUnmarshall2");
    pRpcServerRegisterIfEx = (void *)GetProcAddress(hrpcrt4, "RpcServerRegisterIfEx");
    pRpcBindingSetAuthInfoExA = (void *)GetProcAddress(hrpcrt4, "RpcBindingSetAuthInfoExA");
    pRpcServerRegisterAuthInfoA = (void *)GetProcAddress(hrpcrt4, "RpcServerRegisterAuthInfoA");

    if (!pNDRSContextMarshall2) old_windows_version = TRUE;
}