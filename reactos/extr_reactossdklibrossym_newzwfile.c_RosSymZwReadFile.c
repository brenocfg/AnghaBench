#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Information; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RosSymStatus ; 
 int /*<<< orphan*/  ZwReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOLEAN
RosSymZwReadFile(PVOID FileContext, PVOID Buffer, ULONG Size)
{
	//NTSTATUS Status;
  IO_STATUS_BLOCK IoStatusBlock;

  RosSymStatus = ZwReadFile(*((HANDLE *) FileContext),
                      NULL, NULL, NULL,
                      &IoStatusBlock,
                      Buffer,
                      Size,
                      NULL, NULL);

  return NT_SUCCESS(RosSymStatus) && IoStatusBlock.Information == Size;
}