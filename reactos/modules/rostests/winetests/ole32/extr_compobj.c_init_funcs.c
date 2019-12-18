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
 void* pActivateActCtx ; 
 void* pCoGetApartmentType ; 
 void* pCoGetContextToken ; 
 void* pCoGetObjectContext ; 
 void* pCoGetTreatAsClass ; 
 void* pCoInitializeEx ; 
 void* pCoSwitchCallContext ; 
 void* pCoTreatAsClass ; 
 void* pCreateActCtxW ; 
 void* pDeactivateActCtx ; 
 void* pIsWow64Process ; 
 void* pRegDeleteKeyExA ; 
 void* pRegOverridePredefKey ; 
 void* pReleaseActCtx ; 

__attribute__((used)) static void init_funcs(void)
{
    HMODULE hOle32 = GetModuleHandleA("ole32");
    HMODULE hAdvapi32 = GetModuleHandleA("advapi32");
    HMODULE hkernel32 = GetModuleHandleA("kernel32");

    pCoGetObjectContext = (void*)GetProcAddress(hOle32, "CoGetObjectContext");
    pCoSwitchCallContext = (void*)GetProcAddress(hOle32, "CoSwitchCallContext");
    pCoGetTreatAsClass = (void*)GetProcAddress(hOle32,"CoGetTreatAsClass");
    pCoTreatAsClass = (void*)GetProcAddress(hOle32,"CoTreatAsClass");
    pCoGetContextToken = (void*)GetProcAddress(hOle32, "CoGetContextToken");
    pCoGetApartmentType = (void*)GetProcAddress(hOle32, "CoGetApartmentType");
    pRegDeleteKeyExA = (void*)GetProcAddress(hAdvapi32, "RegDeleteKeyExA");
    pRegOverridePredefKey = (void*)GetProcAddress(hAdvapi32, "RegOverridePredefKey");
    pCoInitializeEx = (void*)GetProcAddress(hOle32, "CoInitializeEx");

    pActivateActCtx = (void*)GetProcAddress(hkernel32, "ActivateActCtx");
    pCreateActCtxW = (void*)GetProcAddress(hkernel32, "CreateActCtxW");
    pDeactivateActCtx = (void*)GetProcAddress(hkernel32, "DeactivateActCtx");
    pIsWow64Process = (void*)GetProcAddress(hkernel32, "IsWow64Process");
    pReleaseActCtx = (void*)GetProcAddress(hkernel32, "ReleaseActCtx");
}