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
struct TYPE_4__ {int Address; scalar_t__ Size; scalar_t__ Handle; scalar_t__ LockCount; } ;
typedef  TYPE_1__* PXMS_HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AllocBitmap ; 
 int /*<<< orphan*/  FreeBlocks ; 
 TYPE_1__* GetXmsHandleRecord (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  ValidateXmsHandle (TYPE_1__*) ; 
 int XMS_ADDRESS ; 
 int XMS_BLOCK_SIZE ; 
 int /*<<< orphan*/  XMS_STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  XMS_STATUS_LOCKED ; 
 int /*<<< orphan*/  XMS_STATUS_SUCCESS ; 

__attribute__((used)) static UCHAR XmsFree(WORD Handle)
{
    DWORD BlockNumber;
    PXMS_HANDLE HandleEntry = GetXmsHandleRecord(Handle);

    if (!ValidateXmsHandle(HandleEntry))
        return XMS_STATUS_INVALID_HANDLE;

    if (HandleEntry->LockCount)
        return XMS_STATUS_LOCKED;

    BlockNumber = (HandleEntry->Address - XMS_ADDRESS) / XMS_BLOCK_SIZE;
    RtlClearBits(&AllocBitmap, BlockNumber, HandleEntry->Size);

    HandleEntry->Handle = 0;
    FreeBlocks += HandleEntry->Size;

    return XMS_STATUS_SUCCESS;
}