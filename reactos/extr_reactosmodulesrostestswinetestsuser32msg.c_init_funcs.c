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
 void* pCreateActCtxW ; 
 void* pDeactivateActCtx ; 
 void* pGetCurrentActCtx ; 
 void* pQueryActCtxW ; 
 void* pReleaseActCtx ; 

__attribute__((used)) static void init_funcs(void)
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");

#define X(f) p##f = (void*)GetProcAddress(hKernel32, #f)
    X(ActivateActCtx);
    X(CreateActCtxW);
    X(DeactivateActCtx);
    X(GetCurrentActCtx);
    X(QueryActCtxW);
    X(ReleaseActCtx);
#undef X
}