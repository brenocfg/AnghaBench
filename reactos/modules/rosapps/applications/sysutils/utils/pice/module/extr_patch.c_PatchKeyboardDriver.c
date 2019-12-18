#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_6__ {scalar_t__ Context; scalar_t__ IsrRoutine; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PINTERNAL_I8042_HOOK_KEYBOARD ;
typedef  scalar_t__ PI8042_KEYBOARD_ISR ;
typedef  int /*<<< orphan*/ * PFILE_OBJECT ;
typedef  int /*<<< orphan*/ * PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  INTERNAL_I8042_HOOK_KEYBOARD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 TYPE_1__* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_READ_ACCESS ; 
 int /*<<< orphan*/  IOCTL_INTERNAL_I8042_HOOK_KEYBOARD ; 
 int /*<<< orphan*/  IoGetDeviceObjectPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ PiceKbdIsr ; 
 int /*<<< orphan*/  PiceSendIoctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ROS_STRING_INITIALIZER (char*) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 

BOOLEAN PatchKeyboardDriver(void)
{
	PINTERNAL_I8042_HOOK_KEYBOARD phkData;
	//When we have i8042 driver this should be changed!!!!!!!
    UNICODE_STRING DevName = ROS_STRING_INITIALIZER(L"\\Device\\Keyboard");
	PDEVICE_OBJECT kbdDevice = NULL;
	PFILE_OBJECT FO = NULL;
	NTSTATUS status;

	ENTER_FUNC();

	//Get pointer to keyboard device
    if( !NT_SUCCESS( status = IoGetDeviceObjectPointer( &DevName, FILE_READ_ACCESS, &FO, &kbdDevice ) ) )
	{
		DPRINT((0,"PatchKeyboardDriver: IoGetDeviceObjectPointer status: %x\n", status));
		return FALSE;
	}
	phkData = ExAllocatePool( PagedPool, sizeof( INTERNAL_I8042_HOOK_KEYBOARD ) );
	RtlZeroMemory( phkData, sizeof( INTERNAL_I8042_HOOK_KEYBOARD ) );

	phkData->IsrRoutine = (PI8042_KEYBOARD_ISR) PiceKbdIsr;
	phkData->Context = (PVOID) NULL; //DeviceObject;

	//call keyboard device internal io control to hook keyboard input stream
	status = PiceSendIoctl( kbdDevice, IOCTL_INTERNAL_I8042_HOOK_KEYBOARD,
			phkData, sizeof( INTERNAL_I8042_HOOK_KEYBOARD ) );
	DPRINT((0,"PatchKeyboardDriver: PiceSendIoctl status: %x\n", status));


	ObDereferenceObject(FO);
	ExFreePool(phkData);

	LEAVE_FUNC();

    return NT_SUCCESS(status);
}