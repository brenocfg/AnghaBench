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
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int MAX_STACK_FRAMES ; 
#define  SIGABRT 132 
#define  SIGFPE 131 
#define  SIGILL 130 
#define  SIGINT 129 
#define  SIGSEGV 128 
 int /*<<< orphan*/  SIG_DFL ; 
 int ZSTD_START_SYMBOLLIST_FRAME ; 
 int backtrace (void**,int) ; 
 char** backtrace_symbols (void**,int) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ABRThandler(int sig) {
    const char* name;
    void* addrlist[MAX_STACK_FRAMES];
    char** symbollist;
    int addrlen, i;

    switch (sig) {
        case SIGABRT: name = "SIGABRT"; break;
        case SIGFPE: name = "SIGFPE"; break;
        case SIGILL: name = "SIGILL"; break;
        case SIGINT: name = "SIGINT"; break;
        case SIGSEGV: name = "SIGSEGV"; break;
        default: name = "UNKNOWN";
    }

    DISPLAY("Caught %s signal, printing stack:\n", name);
    /* Retrieve current stack addresses. */
    addrlen = backtrace(addrlist, MAX_STACK_FRAMES);
    if (addrlen == 0) {
        DISPLAY("\n");
        return;
    }
    /* Create readable strings to each frame. */
    symbollist = backtrace_symbols(addrlist, addrlen);
    /* Print the stack trace, excluding calls handling the signal. */
    for (i = ZSTD_START_SYMBOLLIST_FRAME; i < addrlen; i++) {
        DISPLAY("%s\n", symbollist[i]);
    }
    free(symbollist);
    /* Reset and raise the signal so default handler runs. */
    signal(sig, SIG_DFL);
    raise(sig);
}