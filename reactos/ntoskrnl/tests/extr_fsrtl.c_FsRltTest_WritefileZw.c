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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PLARGE_INTEGER ;
typedef  int /*<<< orphan*/  PIO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ZwWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NTSTATUS FsRltTest_WritefileZw(HANDLE fh, PLARGE_INTEGER Offset, ULONG Length, PVOID Buffer, PIO_STATUS_BLOCK pIoStatus){
    NTSTATUS Return;

    Return = ZwWriteFile(
        fh,
        NULL,
        NULL,
        NULL,
        pIoStatus,
        Buffer,
        Length,
        Offset,
        NULL
        );

    return Return;
}