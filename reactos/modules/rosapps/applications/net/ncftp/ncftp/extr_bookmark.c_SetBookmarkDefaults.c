#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_4__ {char xferType; char xferMode; int isUnix; scalar_t__ deleted; scalar_t__ lastCall; void* hasPASV; void* hasUTIME; void* hasMDTM; void* hasSIZE; } ;
typedef  TYPE_1__* BookmarkPtr ;
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 void* kCommandAvailabilityUnknown ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
SetBookmarkDefaults(BookmarkPtr bmp)
{
	(void) memset(bmp, 0, sizeof(Bookmark));

	bmp->xferType = 'I';
	bmp->xferMode = 'S';	/* Use FTP protocol default as ours too. */
	bmp->hasSIZE = kCommandAvailabilityUnknown;
	bmp->hasMDTM = kCommandAvailabilityUnknown;
	bmp->hasUTIME = kCommandAvailabilityUnknown;
	bmp->hasPASV = kCommandAvailabilityUnknown;
	bmp->isUnix = 1;
	bmp->lastCall = (time_t) 0;
	bmp->deleted = 0;
}