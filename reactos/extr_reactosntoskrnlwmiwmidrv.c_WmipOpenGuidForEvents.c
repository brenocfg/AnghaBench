#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WMI_OPEN_GUID_FOR_EVENTS ;
typedef  int /*<<< orphan*/  WMIP_RESULT2 ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  Handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  DesiredAccess; int /*<<< orphan*/  ObjectAttributes; } ;
typedef  TYPE_1__* PWMI_OPEN_GUID_FOR_EVENTS ;
typedef  TYPE_2__* PWMIP_RESULT2 ;
typedef  TYPE_1__* PVOID ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExGetPreviousMode () ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  WmipCaptureGuidObjectAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WmipOpenGuidObjectByName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static
NTSTATUS
WmipOpenGuidForEvents(
    PVOID Buffer,
    ULONG InputLength,
    PULONG OutputLength)
{
    PWMI_OPEN_GUID_FOR_EVENTS OpenGuidForEvents = Buffer;
    PWMIP_RESULT2 Result = (PWMIP_RESULT2)Buffer;
    OBJECT_ATTRIBUTES LocalObjectAttributes;
    UNICODE_STRING LocalObjectName;
    WCHAR LocalObjectNameBuffer[45 + 1];
    KPROCESSOR_MODE PreviousMode;
    HANDLE GuidObjectHandle;
    PVOID GuidObject;
    NTSTATUS Status;

    if ((InputLength != sizeof(WMI_OPEN_GUID_FOR_EVENTS)) ||
        (*OutputLength != sizeof(WMIP_RESULT2)))
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* Capture object attributes */
    PreviousMode = ExGetPreviousMode();
    Status = WmipCaptureGuidObjectAttributes(OpenGuidForEvents->ObjectAttributes,
                                             &LocalObjectAttributes,
                                             &LocalObjectName,
                                             LocalObjectNameBuffer,
                                             PreviousMode);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ProbeAndCaptureGuidObjectAttributes failed: 0x%lx\n", Status);
        return Status;
    }

    /* Open a new GUID object */
    Status = WmipOpenGuidObjectByName(&LocalObjectAttributes,
                                      OpenGuidForEvents->DesiredAccess,
                                      PreviousMode,
                                      &GuidObjectHandle,
                                      &GuidObject);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("WmipOpenGuidObjectByName failed: 0x%lx\n", Status);
        return Status;
    }

    Result->Handle = GuidObjectHandle;

    ObDereferenceObject(GuidObject);

    return STATUS_SUCCESS;
}