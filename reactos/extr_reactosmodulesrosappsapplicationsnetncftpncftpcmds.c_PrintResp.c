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
struct TYPE_4__ {char* line; struct TYPE_4__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;

/* Variables and functions */
 scalar_t__ ISTRNCMP (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
PrintResp(LineListPtr llp)
{
	LinePtr lp;

	if (llp != NULL) {
		for (lp = llp->first; lp != NULL; lp = lp->next) {
			if ((lp == llp->first) && (ISTRNCMP(lp->line, "CWD command", 11) == 0))
				continue;
			(void) printf("%s\n", lp->line);
		}
	}
}