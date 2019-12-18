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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  log_debug (char*,long,int) ; 
 int utf8proc_wcwidth (scalar_t__) ; 
 int wcwidth (scalar_t__) ; 

__attribute__((used)) static int
utf8_width(wchar_t wc)
{
	int	width;

#ifdef HAVE_UTF8PROC
	width = utf8proc_wcwidth(wc);
#else
	width = wcwidth(wc);
#endif
	if (width < 0 || width > 0xff) {
		log_debug("Unicode %04lx, wcwidth() %d", (long)wc, width);

#ifndef __OpenBSD__
		/*
		 * Many platforms (particularly and inevitably OS X) have no
		 * width for relatively common characters (wcwidth() returns
		 * -1); assume width 1 in this case. This will be wrong for
		 * genuinely nonprintable characters, but they should be
		 * rare. We may pass through stuff that ideally we would block,
		 * but this is no worse than sending the same to the terminal
		 * without tmux.
		 */
		if (width < 0)
			return (1);
#endif
		return (-1);
	}
	return (width);
}