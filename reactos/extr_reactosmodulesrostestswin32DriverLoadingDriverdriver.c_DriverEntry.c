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
struct TYPE_3__ {int /*<<< orphan*/  DriverUnload; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_1__* PDRIVER_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  DriverUnload ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject,
            PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    DbgPrint("Test driver loaded sucessfully\n");

    return STATUS_SUCCESS;
}