#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int LockCount; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__* PXMS_HANDLE ;
typedef  int /*<<< orphan*/ * PDWORD ;

/* Variables and functions */
 TYPE_1__* GetXmsHandleRecord (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ValidateXmsHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  XMS_STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  XMS_STATUS_LOCK_OVERFLOW ; 
 int /*<<< orphan*/  XMS_STATUS_SUCCESS ; 

__attribute__((used)) static UCHAR XmsLock(WORD Handle, PDWORD Address)
{
    PXMS_HANDLE HandleEntry = GetXmsHandleRecord(Handle);

    if (!ValidateXmsHandle(HandleEntry))
        return XMS_STATUS_INVALID_HANDLE;

    if (HandleEntry->LockCount == 0xFF)
        return XMS_STATUS_LOCK_OVERFLOW;

    /* Increment the lock count */
    HandleEntry->LockCount++;
    *Address = HandleEntry->Address;

    return XMS_STATUS_SUCCESS;
}