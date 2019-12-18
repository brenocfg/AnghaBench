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
 int /*<<< orphan*/  PACKAGE_NAME ; 
 char const* dngettext (int /*<<< orphan*/ ,char const*,char const*,unsigned long) ; 
 scalar_t__ likely (char const) ; 

const char *vlc_ngettext(const char *msgid, const char *plural,
                         unsigned long n)
{
#ifdef ENABLE_NLS
    if (likely(*msgid))
        return dngettext (PACKAGE_NAME, msgid, plural, n);
#endif
    return ((n == 1) ? msgid : plural);
}