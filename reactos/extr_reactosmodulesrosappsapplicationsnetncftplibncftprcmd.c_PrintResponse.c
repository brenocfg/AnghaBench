#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* first; } ;
struct TYPE_4__ {int /*<<< orphan*/  line; struct TYPE_4__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  PrintF (int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ) ; 

void
PrintResponse(const FTPCIPtr cip, LineListPtr llp)
{
	LinePtr lp;

	if (llp != NULL) {
		for (lp = llp->first; lp != NULL; lp = lp->next)
			PrintF(cip, "%s\n", lp->line);
	}
}