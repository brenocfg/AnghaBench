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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GspMemoryError ; 
 int /*<<< orphan*/  KdpCopyMemoryChunks (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMDBG_COPY_UNSAFE ; 
 int /*<<< orphan*/  MmDbgCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CHAR
GspReadMemSafe(PCHAR Address)
{
    CHAR Ch = 0;

#if 0
    if (!NT_SUCCESS(KdpCopyMemoryChunks((ULONG64)(ULONG_PTR)Address, &Ch, 1,
                                        0, MMDBG_COPY_UNSAFE, NULL)))
#else
    if (!NT_SUCCESS(MmDbgCopyMemory((ULONG64)(ULONG_PTR)Address, &Ch, 1,
                                    MMDBG_COPY_UNSAFE)))
#endif
    {
        GspMemoryError = TRUE;
    }

    return Ch;
}