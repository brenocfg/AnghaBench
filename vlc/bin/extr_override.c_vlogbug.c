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
 unsigned int MAX_ERRORS ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  backtrace (void**,size_t const) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlogbug (unsigned *pc, const char *level, const char *func,
                     const char *fmt, va_list ap)
{
#ifdef HAVE_BACKTRACE
    const size_t framec = 5;
    void *framev[framec];

    backtrace (framev, framec);
#endif
    flockfile (stderr);
    if (*pc < MAX_ERRORS)
    {
        (*pc)++;
        fprintf (stderr, "%s: call to %s(", level, func);
        vfprintf (stderr, fmt, ap);
        fputs (")\n", stderr);
        fflush (stderr);
#ifdef HAVE_BACKTRACE
        backtrace_symbols_fd (framev + 2, framec - 2, STDERR_FILENO);
#endif
    }
    funlockfile (stderr);
}