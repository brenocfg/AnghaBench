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
struct TYPE_4__ {int /*<<< orphan*/ * ControlChannel; } ;
struct TYPE_5__ {TYPE_1__ Handle; } ;
typedef  TYPE_2__* PTDI_REQUEST ;
typedef  int /*<<< orphan*/  PCONTROL_CHANNEL ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS FileCloseControlChannel(
  PTDI_REQUEST Request)
{
  if (!Request->Handle.ControlChannel) return STATUS_INVALID_PARAMETER;

  DereferenceObject((PCONTROL_CHANNEL)Request->Handle.ControlChannel);

  Request->Handle.ControlChannel = NULL;

  return STATUS_SUCCESS;
}