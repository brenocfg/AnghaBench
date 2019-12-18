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
 char const* _ (char*) ; 
 char const** sys_errlist ; 
 scalar_t__ sys_nerr ; 

const char *vlc_strerror_c(int errnum)
{
    /* We cannot simply use strerror() here, since it is not thread-safe. */
    if ((unsigned)errnum < (unsigned)sys_nerr)
        return sys_errlist[errnum];

    return _("Unknown error");
}