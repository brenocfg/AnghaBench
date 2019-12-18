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
 void* pChangeServiceConfig2A ; 
 void* pChangeServiceConfig2W ; 
 void* pEnumServicesStatusExA ; 
 void* pEnumServicesStatusExW ; 
 void* pGetSecurityInfo ; 
 void* pNotifyServiceStatusChangeW ; 
 void* pQueryServiceConfig2A ; 
 void* pQueryServiceConfig2W ; 
 void* pQueryServiceObjectSecurity ; 
 void* pQueryServiceStatusEx ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");

    pChangeServiceConfig2A = (void*)GetProcAddress(hadvapi32, "ChangeServiceConfig2A");
    pChangeServiceConfig2W = (void*)GetProcAddress(hadvapi32, "ChangeServiceConfig2W");
    pEnumServicesStatusExA= (void*)GetProcAddress(hadvapi32, "EnumServicesStatusExA");
    pEnumServicesStatusExW= (void*)GetProcAddress(hadvapi32, "EnumServicesStatusExW");
    pGetSecurityInfo = (void *)GetProcAddress(hadvapi32, "GetSecurityInfo");
    pQueryServiceConfig2A= (void*)GetProcAddress(hadvapi32, "QueryServiceConfig2A");
    pQueryServiceConfig2W= (void*)GetProcAddress(hadvapi32, "QueryServiceConfig2W");
    pQueryServiceStatusEx= (void*)GetProcAddress(hadvapi32, "QueryServiceStatusEx");
    pQueryServiceObjectSecurity = (void*)GetProcAddress(hadvapi32, "QueryServiceObjectSecurity");
    pNotifyServiceStatusChangeW = (void*)GetProcAddress(hadvapi32, "NotifyServiceStatusChangeW");
}