#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_4__ {int /*<<< orphan*/  Status; int /*<<< orphan*/  Information; } ;
struct TYPE_5__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */

NTSTATUS
ViSetIoStatus(NTSTATUS Status, ULONG_PTR Information, PIRP Irp)
{
    /* Only set what we got */
    Irp->IoStatus.Information = Information;
    Irp->IoStatus.Status = Status;

    /* And return the status, so that caller can return with us */
    return Status;
}