#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_10__ {scalar_t__ BaseDateYear; } ;
struct TYPE_9__ {scalar_t__ Year; int /*<<< orphan*/  Month; int /*<<< orphan*/  Day; } ;
struct TYPE_8__ {int Second; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Minute; } ;
struct TYPE_7__ {int Second; scalar_t__ Year; int /*<<< orphan*/  Month; int /*<<< orphan*/  Day; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Minute; } ;
typedef  TYPE_1__ TIME_FIELDS ;
typedef  int /*<<< orphan*/  PUSHORT ;
typedef  int /*<<< orphan*/ * PLARGE_INTEGER ;
typedef  TYPE_2__* PDOSTIME ;
typedef  TYPE_3__* PDOSDATE ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ExSystemTimeToLocalTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RtlTimeToTimeFields (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
FsdSystemTimeToDosDateTime(
    PDEVICE_EXTENSION DeviceExt,
    PLARGE_INTEGER SystemTime,
    PUSHORT pDosDate,
    PUSHORT pDosTime)
{
    PDOSTIME pdtime = (PDOSTIME)pDosTime;
    PDOSDATE pddate = (PDOSDATE)pDosDate;
    TIME_FIELDS TimeFields;
    LARGE_INTEGER LocalTime;

    if (SystemTime == NULL)
        return FALSE;

    ExSystemTimeToLocalTime(SystemTime, &LocalTime);
    RtlTimeToTimeFields(&LocalTime, &TimeFields);

    if (pdtime)
    {
        pdtime->Second = TimeFields.Second / 2;
        pdtime->Minute = TimeFields.Minute;
        pdtime->Hour = TimeFields.Hour;
    }

    if (pddate)
    {
        pddate->Day = TimeFields.Day;
        pddate->Month = TimeFields.Month;
        pddate->Year = (USHORT) (TimeFields.Year - DeviceExt->BaseDateYear);
    }

    return TRUE;
}