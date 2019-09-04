#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  CurrentCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  Id; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Set; } ;
struct TYPE_8__ {TYPE_1__ Property; int /*<<< orphan*/  PinId; scalar_t__ Reserved; } ;
struct TYPE_7__ {scalar_t__ (* Control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PMIXER_CONTEXT ;
typedef  scalar_t__ MIXER_STATUS ;
typedef  TYPE_3__ KSP_PIN ;
typedef  TYPE_4__ KSPIN_CINSTANCES ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 int /*<<< orphan*/  KSPROPERTY_PIN_CINSTANCES ; 
 int /*<<< orphan*/  KSPROPERTY_TYPE_GET ; 
 int /*<<< orphan*/  KSPROPSETID_Pin ; 
 scalar_t__ MM_STATUS_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

ULONG
MMixerGetPinInstanceCount(
    PMIXER_CONTEXT MixerContext,
    HANDLE hFilter,
    ULONG PinId)
{
    KSP_PIN PinRequest;
    KSPIN_CINSTANCES PinInstances;
    ULONG BytesReturned;
    MIXER_STATUS Status;

    /* query the instance count */
    PinRequest.Reserved = 0;
    PinRequest.PinId = PinId;
    PinRequest.Property.Set = KSPROPSETID_Pin;
    PinRequest.Property.Flags = KSPROPERTY_TYPE_GET;
    PinRequest.Property.Id = KSPROPERTY_PIN_CINSTANCES;

    Status = MixerContext->Control(hFilter, IOCTL_KS_PROPERTY, (PVOID)&PinRequest, sizeof(KSP_PIN), (PVOID)&PinInstances, sizeof(KSPIN_CINSTANCES), &BytesReturned);
    ASSERT(Status == MM_STATUS_SUCCESS);
    return PinInstances.CurrentCount;
}