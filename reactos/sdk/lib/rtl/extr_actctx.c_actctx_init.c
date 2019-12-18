#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {TYPE_1__* ProcessEnvironmentBlock; } ;
struct TYPE_7__ {int /*<<< orphan*/  NtSystemRoot; } ;
struct TYPE_6__ {int cbSize; int dwFlags; int /*<<< orphan*/ * lpSource; int /*<<< orphan*/ * lpResourceName; int /*<<< orphan*/ * hModule; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ImageBaseAddress; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_2__ ACTCTXW ;

/* Variables and functions */
 int ACTCTX_FLAG_HMODULE_VALID ; 
 int ACTCTX_FLAG_RESOURCE_NAME_VALID ; 
 scalar_t__ CREATEPROCESS_MANIFEST_RESOURCE_ID ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LdrpInitializeProcessCompat (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_4__* NtCurrentTeb () ; 
 int /*<<< orphan*/  RTL_NUMBER_OF (int /*<<< orphan*/ *) ; 
 scalar_t__ RosGetProcessCompatVersion () ; 
 int /*<<< orphan*/  RtlCreateActivationContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlStringCchCatW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RtlStringCchCopyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* SharedUserData ; 
 void* check_actctx (int /*<<< orphan*/ ) ; 
 void* implicit_actctx ; 
 void* process_actctx ; 

void actctx_init(PVOID* pOldShimData)
{
    ACTCTXW ctx;
    HANDLE handle;
    WCHAR buffer[1024];
    NTSTATUS Status;

    ctx.cbSize   = sizeof(ctx);
    ctx.lpSource = NULL;
    ctx.dwFlags  = ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_HMODULE_VALID;
    ctx.hModule  = NtCurrentTeb()->ProcessEnvironmentBlock->ImageBaseAddress;
    ctx.lpResourceName = (LPCWSTR)CREATEPROCESS_MANIFEST_RESOURCE_ID;

    if (NT_SUCCESS(RtlCreateActivationContext(0, (PVOID)&ctx, 0, NULL, NULL, &handle)))
    {
        process_actctx = check_actctx(handle);
    }

    /* ReactOS specific:
       Now that we have found the process_actctx we can initialize the process compat subsystem */
    LdrpInitializeProcessCompat(process_actctx, pOldShimData);


    ctx.dwFlags  = 0;
    ctx.hModule  = NULL;
    ctx.lpResourceName = NULL;
    ctx.lpSource = buffer;
    RtlStringCchCopyW(buffer, RTL_NUMBER_OF(buffer), SharedUserData->NtSystemRoot);

    if (RosGetProcessCompatVersion())
    {
        RtlStringCchCatW(buffer, RTL_NUMBER_OF(buffer), L"\\winsxs\\manifests\\forwardcompatible.manifest");
    }
    else
    {
        RtlStringCchCatW(buffer, RTL_NUMBER_OF(buffer), L"\\winsxs\\manifests\\systemcompatible.manifest");
    }

    Status = RtlCreateActivationContext(0, (PVOID)&ctx, 0, NULL, NULL, &handle);
    if (NT_SUCCESS(Status))
    {
        implicit_actctx = check_actctx(handle);
    }
    else
    {
        DPRINT1("Failed to create the implicit act ctx. Status: 0x%x!!!\n", Status);
    }
}