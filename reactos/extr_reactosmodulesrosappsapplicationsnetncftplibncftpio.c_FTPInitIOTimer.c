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
typedef  scalar_t__ longest_int ;
struct TYPE_3__ {double kBytesPerSec; double percentCompleted; double sec; double secLeft; int useProgressMeter; int /*<<< orphan*/  t0; scalar_t__ dataTimedOut; scalar_t__ stalled; scalar_t__ nextProgressUpdate; int /*<<< orphan*/ * lname; int /*<<< orphan*/ * rname; int /*<<< orphan*/  mdtm; int /*<<< orphan*/  expectedSize; scalar_t__ bytesTransferred; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kModTimeUnknown ; 
 int /*<<< orphan*/  kSizeUnknown ; 

void
FTPInitIOTimer(const FTPCIPtr cip)
{
	cip->bytesTransferred = (longest_int) 0;
	cip->expectedSize = kSizeUnknown;
	cip->mdtm = kModTimeUnknown;
	cip->rname = NULL;
	cip->lname = NULL;
	cip->kBytesPerSec = -1.0;
	cip->percentCompleted = -1.0;
	cip->sec = -1.0;
	cip->secLeft = -1.0;
	cip->nextProgressUpdate = 0;
	cip->stalled = 0;
	cip->dataTimedOut = 0;
	cip->useProgressMeter = 1;
	(void) gettimeofday(&cip->t0, NULL);
}