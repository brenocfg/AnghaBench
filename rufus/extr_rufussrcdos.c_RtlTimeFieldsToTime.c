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
struct TYPE_10__ {int QuadPart; } ;
struct TYPE_9__ {int Milliseconds; int Second; int Minute; int Hour; int Month; int Day; int Year; } ;
struct TYPE_8__ {int Year; int Month; int Day; int Hour; int Minute; int Milliseconds; scalar_t__ Second; } ;
typedef  TYPE_1__ TIME_FIELDS ;
typedef  TYPE_2__* PTIME_FIELDS ;
typedef  TYPE_3__* PLARGE_INTEGER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int DaysSinceEpoch (int) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t IsLeapYear (int) ; 
 int** MonthLengths ; 
 int SECSPERDAY ; 
 int SECSPERHOUR ; 
 int SECSPERMIN ; 
 int TICKSPERMSEC ; 
 int TICKSPERSEC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static BOOLEAN RtlTimeFieldsToTime(PTIME_FIELDS TimeFields, PLARGE_INTEGER Time)
{
	int CurMonth;
	TIME_FIELDS IntTimeFields;

	memcpy(&IntTimeFields,
		TimeFields,
		sizeof(TIME_FIELDS));

	if (TimeFields->Milliseconds < 0 || TimeFields->Milliseconds > 999 ||
		TimeFields->Second < 0 || TimeFields->Second > 59 ||
		TimeFields->Minute < 0 || TimeFields->Minute > 59 ||
		TimeFields->Hour < 0 || TimeFields->Hour > 23 ||
		TimeFields->Month < 1 || TimeFields->Month > 12 ||
		TimeFields->Day < 1 ||
		TimeFields->Day >
		MonthLengths[IsLeapYear(TimeFields->Year)][TimeFields->Month - 1] ||
		TimeFields->Year < 1601) {
		return FALSE;
	}

	/* Compute the time */
	Time->QuadPart = DaysSinceEpoch(IntTimeFields.Year);
	for (CurMonth = 1; CurMonth < IntTimeFields.Month; CurMonth++) {
		Time->QuadPart += MonthLengths[IsLeapYear(IntTimeFields.Year)][CurMonth - 1];
	}
	Time->QuadPart += IntTimeFields.Day - 1;
	Time->QuadPart *= SECSPERDAY;
	Time->QuadPart += IntTimeFields.Hour * SECSPERHOUR + IntTimeFields.Minute * SECSPERMIN +
		IntTimeFields.Second;
	Time->QuadPart *= TICKSPERSEC;
	Time->QuadPart += IntTimeFields.Milliseconds * TICKSPERMSEC;

	return TRUE;
}