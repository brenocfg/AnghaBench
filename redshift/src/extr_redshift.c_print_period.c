#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int period_t ;

/* Variables and functions */
#define  PERIOD_DAYTIME 131 
#define  PERIOD_NIGHT 130 
#define  PERIOD_NONE 129 
#define  PERIOD_TRANSITION 128 
 char* _ (char*) ; 
 char* gettext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * period_names ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void
print_period(period_t period, double transition)
{
	switch (period) {
	case PERIOD_NONE:
	case PERIOD_NIGHT:
	case PERIOD_DAYTIME:
		printf(_("Period: %s\n"), gettext(period_names[period]));
		break;
	case PERIOD_TRANSITION:
		printf(_("Period: %s (%.2f%% day)\n"),
		       gettext(period_names[period]),
		       transition*100);
		break;
	}
}