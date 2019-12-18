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
typedef  int /*<<< orphan*/  ucontext_t ;

/* Variables and functions */
 int backtrace (void**,int) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,int,int) ; 
 int /*<<< orphan*/  closeDirectLogFiledes (int) ; 
 int /*<<< orphan*/ * getMcontextEip (int /*<<< orphan*/ *) ; 
 int openDirectLogFiledes () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

void logStackTrace(ucontext_t *uc) {
    void *trace[101];
    int trace_size = 0, fd = openDirectLogFiledes();

    if (fd == -1) return; /* If we can't log there is anything to do. */

    /* Generate the stack trace */
    trace_size = backtrace(trace+1, 100);

    if (getMcontextEip(uc) != NULL) {
        char *msg1 = "EIP:\n";
        char *msg2 = "\nBacktrace:\n";
        if (write(fd,msg1,strlen(msg1)) == -1) {/* Avoid warning. */};
        trace[0] = getMcontextEip(uc);
        backtrace_symbols_fd(trace, 1, fd);
        if (write(fd,msg2,strlen(msg2)) == -1) {/* Avoid warning. */};
    }

    /* Write symbols to log file */
    backtrace_symbols_fd(trace+1, trace_size, fd);

    /* Cleanup */
    closeDirectLogFiledes(fd);
}