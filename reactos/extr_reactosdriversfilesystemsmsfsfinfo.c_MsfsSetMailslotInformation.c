#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ReadTimeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  TimeOut; } ;
typedef  int* PULONG ;
typedef  TYPE_1__* PMSFS_FCB ;
typedef  TYPE_2__* PFILE_MAILSLOT_SET_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_MAILSLOT_SET_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS
MsfsSetMailslotInformation(PMSFS_FCB Fcb,
                           PFILE_MAILSLOT_SET_INFORMATION Buffer,
                           PULONG BufferLength)
{
    if (*BufferLength < sizeof(FILE_MAILSLOT_SET_INFORMATION))
        return STATUS_BUFFER_OVERFLOW;

    Fcb->TimeOut = *Buffer->ReadTimeout;

    return STATUS_SUCCESS;
}