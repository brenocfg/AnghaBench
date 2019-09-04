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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PLARGE_INTEGER ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KWAIT_REASON ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS TcpipWaitForSingleObject( PVOID Object,
				   KWAIT_REASON Reason,
				   KPROCESSOR_MODE WaitMode,
				   BOOLEAN Alertable,
				   PLARGE_INTEGER Timeout ) {
    return STATUS_SUCCESS;
}