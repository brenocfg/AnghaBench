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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 struct tm* gmtime (scalar_t__*) ; 
 struct tm* gmtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ pdf_annot_modification_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selected_annot ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  ui_label (char*,char*) ; 

__attribute__((used)) static void do_annotate_date(void)
{
	time_t secs = pdf_annot_modification_date(ctx, selected_annot);
	if (secs > 0)
	{
#ifdef _POSIX_SOURCE
		struct tm tmbuf, *tm = gmtime_r(&secs, &tmbuf);
#else
		struct tm *tm = gmtime(&secs);
#endif
		char buf[100];
		if (tm)
		{
			strftime(buf, sizeof buf, "%Y-%m-%d %H:%M UTC", tm);
			ui_label("Date: %s", buf);
		}
	}
}