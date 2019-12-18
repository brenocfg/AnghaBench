#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* progress ) (TYPE_1__* const,int /*<<< orphan*/ ) ;int /*<<< orphan*/  t0; } ;
typedef  int /*<<< orphan*/  (* FTPProgressMeterProc ) (TYPE_1__* const,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kPrInitMsg ; 
 int /*<<< orphan*/  stub1 (TYPE_1__* const,int /*<<< orphan*/ ) ; 

void
FTPStartIOTimer(const FTPCIPtr cip)
{
	(void) gettimeofday(&cip->t0, NULL);
	if (cip->progress != (FTPProgressMeterProc) 0)
		(*cip->progress)(cip, kPrInitMsg);
}