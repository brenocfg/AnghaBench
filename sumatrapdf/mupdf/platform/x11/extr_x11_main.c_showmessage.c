#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  pdfapp_t ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  message ; 
 int showingmessage ; 
 scalar_t__ showingpage ; 
 int /*<<< orphan*/  timeradd (struct timeval*,TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__ tmo ; 
 TYPE_1__ tmo_at ; 

__attribute__((used)) static void showmessage(pdfapp_t *app, int timeout, char *msg)
{
	struct timeval now;

	showingmessage = 1;
	showingpage = 0;

	fz_strlcpy(message, msg, sizeof message);

	if ((!tmo_at.tv_sec && !tmo_at.tv_usec) || tmo.tv_sec < timeout)
	{
		tmo.tv_sec = timeout;
		tmo.tv_usec = 0;
		gettimeofday(&now, NULL);
		timeradd(&now, &tmo, &tmo_at);
	}
}