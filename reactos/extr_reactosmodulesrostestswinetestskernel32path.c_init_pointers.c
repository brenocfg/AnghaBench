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
 void* pCheckNameLegalDOS8Dot3A ; 
 void* pCheckNameLegalDOS8Dot3W ; 
 void* pCreateActCtxW ; 
 void* pDeactivateActCtx ; 
 void* pGetCurrentActCtx ; 
 void* pGetLongPathNameA ; 
 void* pGetLongPathNameW ; 
 void* pNeedCurrentDirectoryForExePathA ; 
 void* pNeedCurrentDirectoryForExePathW ; 
 void* pReleaseActCtx ; 
 void* pSearchPathA ; 
 void* pSearchPathW ; 
 void* pSetSearchPathMode ; 

__attribute__((used)) static void init_pointers(void)
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");

#define MAKEFUNC(f) (p##f = (void*)GetProcAddress(hKernel32, #f))
    MAKEFUNC(GetLongPathNameA);
    MAKEFUNC(GetLongPathNameW);
    MAKEFUNC(NeedCurrentDirectoryForExePathA);
    MAKEFUNC(NeedCurrentDirectoryForExePathW);
    MAKEFUNC(SearchPathA);
    MAKEFUNC(SearchPathW);
    MAKEFUNC(SetSearchPathMode);
    MAKEFUNC(ActivateActCtx);
    MAKEFUNC(CreateActCtxW);
    MAKEFUNC(DeactivateActCtx);
    MAKEFUNC(GetCurrentActCtx);
    MAKEFUNC(ReleaseActCtx);
    MAKEFUNC(CheckNameLegalDOS8Dot3W);
    MAKEFUNC(CheckNameLegalDOS8Dot3A);
#undef MAKEFUNC
}