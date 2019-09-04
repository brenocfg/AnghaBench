#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_4__ {int /*<<< orphan*/  LowPart; scalar_t__ HighPart; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ CurrentByteOffset; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_3__ FILE_POSITION_INFORMATION ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FilePositionInformation ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RosSymStatus ; 
 int /*<<< orphan*/  ZwSetInformationFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 

BOOLEAN
RosSymZwSeekFile(PVOID FileContext, ULONG_PTR Position)
{
	//NTSTATUS Status;
  IO_STATUS_BLOCK IoStatusBlock;
  FILE_POSITION_INFORMATION NewPosition;

  NewPosition.CurrentByteOffset.u.HighPart = 0;
  NewPosition.CurrentByteOffset.u.LowPart = Position;
  RosSymStatus = ZwSetInformationFile(*((HANDLE *) FileContext),
                                &IoStatusBlock,
                                (PVOID) &NewPosition,
                                sizeof(FILE_POSITION_INFORMATION),
                                FilePositionInformation);

  return NT_SUCCESS(RosSymStatus);
}