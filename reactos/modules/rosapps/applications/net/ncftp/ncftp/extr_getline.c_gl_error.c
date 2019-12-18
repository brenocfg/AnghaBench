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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  gl_cleanup () ; 
 scalar_t__ strlen (char const* const) ; 
 int /*<<< orphan*/  write (int,char const* const,int) ; 

__attribute__((used)) static void
gl_error(const char *const buf)
{
    int len = (int) strlen(buf);

    gl_cleanup();
    write(2, buf, len);
    exit(1);
}