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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free_error () ; 
 scalar_t__ oom ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_threadvar_set (int /*<<< orphan*/ ,char*) ; 

const char *libvlc_vprinterr (const char *fmt, va_list ap)
{
    char *msg;

    assert (fmt != NULL);
    if (vasprintf (&msg, fmt, ap) == -1)
        msg = (char *)oom;

    free_error ();
    vlc_threadvar_set (context, msg);
    return msg;
}