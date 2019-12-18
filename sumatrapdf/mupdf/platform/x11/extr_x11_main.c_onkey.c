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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {scalar_t__ issearching; } ;

/* Variables and functions */
 scalar_t__ advance_scheduled ; 
 TYPE_1__ gapp ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ justcopied ; 
 int /*<<< orphan*/  pdfapp_onkey (TYPE_1__*,int,int) ; 
 scalar_t__ showingmessage ; 
 int showingpage ; 
 int /*<<< orphan*/  timeradd (struct timeval*,struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmo_at ; 
 int /*<<< orphan*/  winrepaint (TYPE_1__*) ; 

__attribute__((used)) static void onkey(int c, int modifiers)
{
	advance_scheduled = 0;

	if (justcopied)
	{
		justcopied = 0;
		winrepaint(&gapp);
	}

	if (!gapp.issearching && c == 'P')
	{
		struct timeval now;
		struct timeval tmo;
		tmo.tv_sec = 2;
		tmo.tv_usec = 0;
		gettimeofday(&now, NULL);
		timeradd(&now, &tmo, &tmo_at);
		showingpage = 1;
		winrepaint(&gapp);
		return;
	}

	pdfapp_onkey(&gapp, c, modifiers);

	if (gapp.issearching)
	{
		showingpage = 0;
		showingmessage = 0;
	}
}