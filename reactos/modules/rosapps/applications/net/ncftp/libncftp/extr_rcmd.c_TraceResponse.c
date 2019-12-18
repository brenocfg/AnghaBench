#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  line; struct TYPE_7__* next; } ;
struct TYPE_5__ {TYPE_3__* first; } ;
struct TYPE_6__ {int /*<<< orphan*/  code; TYPE_1__ msg; } ;
typedef  TYPE_2__* ResponsePtr ;
typedef  TYPE_3__* LinePtr ;
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  PrintF (int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ,...) ; 

void
TraceResponse(const FTPCIPtr cip, ResponsePtr rp)
{
	LinePtr lp;

	if (rp != NULL)	{
		lp = rp->msg.first;
		if (lp != NULL) {
			PrintF(cip, "%3d: %s\n", rp->code, lp->line);
			for (lp = lp->next; lp != NULL; lp = lp->next)
				PrintF(cip, "     %s\n", lp->line);
		}
	}
}