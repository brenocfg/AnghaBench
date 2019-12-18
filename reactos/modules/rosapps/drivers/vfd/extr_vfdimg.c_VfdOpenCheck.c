#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VFD_IMAGE_INFO ;
typedef  int ULONG ;
struct TYPE_10__ {int /*<<< orphan*/ * SecurityContext; scalar_t__ FileBuffer; scalar_t__ FileHandle; } ;
struct TYPE_9__ {int NameLength; scalar_t__ MediaType; scalar_t__ DiskType; } ;
struct TYPE_8__ {int Length; int /*<<< orphan*/  EffectiveOnly; int /*<<< orphan*/  ContextTrackingMode; int /*<<< orphan*/  ImpersonationLevel; } ;
typedef  TYPE_1__ SECURITY_QUALITY_OF_SERVICE ;
typedef  int /*<<< orphan*/  SECURITY_CLIENT_CONTEXT ;
typedef  TYPE_2__* PVFD_IMAGE_INFO ;
typedef  int /*<<< orphan*/ * PSECURITY_CLIENT_CONTEXT ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  PsGetCurrentThread () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SECURITY_STATIC_TRACKING ; 
 int /*<<< orphan*/  STATUS_DEVICE_BUSY ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeCreateClientSecurity (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeDeleteClientSecurity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecurityImpersonation ; 
 int /*<<< orphan*/  VFDTRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VFDWARN ; 
 scalar_t__ VFD_DISKTYPE_FILE ; 
 scalar_t__ VFD_MEDIA_MAX ; 
 scalar_t__ VFD_MEDIA_NONE ; 
 int /*<<< orphan*/  VFD_POOL_TAG ; 

NTSTATUS
VfdOpenCheck(
	PDEVICE_EXTENSION			DeviceExtension,
	PVFD_IMAGE_INFO				ImageInfo,
	ULONG						InputLength)
{
	//	Check media status

	if (DeviceExtension->FileHandle ||
		DeviceExtension->FileBuffer) {

		VFDTRACE(VFDWARN, ("[VFD] image already opened.\n"));

		return STATUS_DEVICE_BUSY;
	}

	//	Check input parameter length

	if (InputLength < sizeof(VFD_IMAGE_INFO) ||
		InputLength < sizeof(VFD_IMAGE_INFO) + ImageInfo->NameLength)
	{
		return STATUS_INVALID_PARAMETER;
	}

	//	Check input parameters

	if (ImageInfo->MediaType == VFD_MEDIA_NONE ||
		ImageInfo->MediaType >= VFD_MEDIA_MAX) {

		VFDTRACE(VFDWARN, ("[VFD] invalid MediaType - %u.\n",
			ImageInfo->MediaType));

		return STATUS_INVALID_PARAMETER;
	}

	if (ImageInfo->DiskType == VFD_DISKTYPE_FILE &&
		ImageInfo->NameLength == 0) {

		VFDTRACE(VFDWARN,
			("[VFD] File name required for VFD_DISKTYPE_FILE.\n"));

		return STATUS_INVALID_PARAMETER;
	}

	//	create a security context to match the calling process' context
	//	the driver thread uses this context to impersonate the client
	//	to open the specified image file

//	if (ImageInfo->DiskType == VFD_DISKTYPE_FILE)
	{
		SECURITY_QUALITY_OF_SERVICE sqos;

		if (DeviceExtension->SecurityContext != NULL) {
			SeDeleteClientSecurity(DeviceExtension->SecurityContext);
		}
		else {
			DeviceExtension->SecurityContext =
				(PSECURITY_CLIENT_CONTEXT)ExAllocatePoolWithTag(
				NonPagedPool, sizeof(SECURITY_CLIENT_CONTEXT), VFD_POOL_TAG);
		}

		RtlZeroMemory(&sqos, sizeof(SECURITY_QUALITY_OF_SERVICE));

		sqos.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
		sqos.ImpersonationLevel		= SecurityImpersonation;
		sqos.ContextTrackingMode	= SECURITY_STATIC_TRACKING;
		sqos.EffectiveOnly			= FALSE;

		SeCreateClientSecurity(
			PsGetCurrentThread(), &sqos, FALSE,
			DeviceExtension->SecurityContext);
	}

	return STATUS_SUCCESS;
}