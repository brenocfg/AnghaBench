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
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_10__ {scalar_t__ BaseDateYear; } ;
struct TYPE_9__ {scalar_t__ Year; int /*<<< orphan*/  Month; int /*<<< orphan*/  Day; } ;
struct TYPE_8__ {int Second; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Minute; } ;
struct TYPE_7__ {int Second; scalar_t__ Year; int /*<<< orphan*/  Month; int /*<<< orphan*/  Day; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Minute; scalar_t__ Milliseconds; } ;
typedef  TYPE_1__ TIME_FIELDS ;
typedef  int /*<<< orphan*/ * PLARGE_INTEGER ;
typedef  TYPE_2__* PDOSTIME ;
typedef  TYPE_3__* PDOSDATE ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  scalar_t__ CSHORT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ExLocalTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RtlTimeFieldsToTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
FsdDosDateTimeToSystemTime(
    PDEVICE_EXTENSION DeviceExt,
    USHORT DosDate,
    USHORT DosTime,
    PLARGE_INTEGER SystemTime)
{
    PDOSTIME pdtime = (PDOSTIME)&DosTime;
    PDOSDATE pddate = (PDOSDATE)&DosDate;
    TIME_FIELDS TimeFields;
    LARGE_INTEGER LocalTime;

    if (SystemTime == NULL)
        return FALSE;

    TimeFields.Milliseconds = 0;
    TimeFields.Second = pdtime->Second * 2;
    TimeFields.Minute = pdtime->Minute;
    TimeFields.Hour = pdtime->Hour;

    TimeFields.Day = pddate->Day;
    TimeFields.Month = pddate->Month;
    TimeFields.Year = (CSHORT)(DeviceExt->BaseDateYear + pddate->Year);

    RtlTimeFieldsToTime(&TimeFields, &LocalTime);
    ExLocalTimeToSystemTime(&LocalTime, SystemTime);

    return TRUE;
}