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
struct TYPE_6__ {int /*<<< orphan*/  (* progress ) (TYPE_1__* const,int /*<<< orphan*/ ) ;scalar_t__ nextProgressUpdate; } ;
typedef  int /*<<< orphan*/  (* FTPProgressMeterProc ) (TYPE_1__* const,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  FTPUpdateIOTimer (TYPE_1__* const) ; 
 int /*<<< orphan*/  kPrEndMsg ; 
 int /*<<< orphan*/  stub1 (TYPE_1__* const,int /*<<< orphan*/ ) ; 

void
FTPStopIOTimer(const FTPCIPtr cip)
{
	cip->nextProgressUpdate = 0;	/* force last update */
	FTPUpdateIOTimer(cip);
	if (cip->progress != (FTPProgressMeterProc) 0)
		(*cip->progress)(cip, kPrEndMsg);
}