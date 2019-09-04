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

/* Variables and functions */
 scalar_t__ gDoNotDisplayAds ; 
 int gNumProgramRuns ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
Plug(void)
{
#if defined(WIN32) || defined(_WINDOWS)
	/* NcFTPd hasn't been ported to Windows. */
#else
	if ((gDoNotDisplayAds == 0) && ((gNumProgramRuns % 7) == 2)) {
		(void) printf("\n\n\n\tThank you for using NcFTP Client.\n\tAsk your system administrator to try NcFTPd Server!\n\thttp://www.ncftpd.com\n\n\n\n");
	}
#endif
}