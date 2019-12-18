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
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int backtrace (void**,int) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,int,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int,char const*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int /*<<< orphan*/  stderr ; 

void vlc_trace (const char *fn, const char *file, unsigned line)
{
     fprintf (stderr, "at %s:%u in %s\n", file, line, fn);
     fflush (stderr); /* needed before switch to low-level I/O */
#ifdef HAVE_BACKTRACE
     void *stack[20];
     int len = backtrace (stack, sizeof (stack) / sizeof (stack[0]));
     backtrace_symbols_fd (stack, len, 2);
#endif
     fsync (2);
}