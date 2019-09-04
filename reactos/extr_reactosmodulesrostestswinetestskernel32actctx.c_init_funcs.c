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
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pActivateActCtx ; 
 void* pCreateActCtxA ; 
 void* pCreateActCtxW ; 
 void* pDeactivateActCtx ; 
 void* pFindActCtxSectionGuid ; 
 void* pFindActCtxSectionStringA ; 
 void* pFindActCtxSectionStringW ; 
 void* pGetCurrentActCtx ; 
 void* pIsDebuggerPresent ; 
 void* pQueryActCtxW ; 
 void* pReleaseActCtx ; 
 void* pRtlCreateUnicodeStringFromAsciiz ; 
 void* pRtlFindActivationContextSectionString ; 
 void* pRtlFreeUnicodeString ; 
 void* pZombifyActCtx ; 

__attribute__((used)) static BOOL init_funcs(void)
{
    HMODULE hLibrary = GetModuleHandleA("kernel32.dll");

#define X(f) if (!(p##f = (void*)GetProcAddress(hLibrary, #f))) return FALSE;
    X(ActivateActCtx);
    X(CreateActCtxA);
    X(CreateActCtxW);
    X(DeactivateActCtx);
    X(FindActCtxSectionStringA);
    X(FindActCtxSectionStringW);
    X(GetCurrentActCtx);
    X(IsDebuggerPresent);
    X(QueryActCtxW);
    X(ReleaseActCtx);
    X(FindActCtxSectionGuid);
    X(ZombifyActCtx);

    hLibrary = GetModuleHandleA("ntdll.dll");
    X(RtlFindActivationContextSectionString);
    X(RtlCreateUnicodeStringFromAsciiz);
    X(RtlFreeUnicodeString);
#undef X

    return TRUE;
}