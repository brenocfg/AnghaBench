#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ crash_blackbox_t ;
typedef  int /*<<< orphan*/  blackbox ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  SetErrorMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUnhandledExceptionFilter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_blackbox (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void doCrash(int argc,  char** argv)
{
    volatile char* p;

    /* make sure the exception gets to the debugger */
    SetErrorMode( 0 );
    SetUnhandledExceptionFilter( NULL );

    if (argc >= 4)
    {
        crash_blackbox_t blackbox;
        blackbox.pid=GetCurrentProcessId();
        save_blackbox(argv[3], &blackbox, sizeof(blackbox));
    }

    /* Just crash */
    trace("child: crashing...\n");
    p=NULL;
    *p=0;
}