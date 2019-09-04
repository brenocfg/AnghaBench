#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int currentline; } ;

/* Variables and functions */
 TYPE_1__ ldb ; 
 char* ldbGetSourceLine (int) ; 
 int ldbIsBreakpoint (int) ; 
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  sdsempty () ; 

void ldbLogSourceLine(int lnum) {
    char *line = ldbGetSourceLine(lnum);
    char *prefix;
    int bp = ldbIsBreakpoint(lnum);
    int current = ldb.currentline == lnum;

    if (current && bp)
        prefix = "->#";
    else if (current)
        prefix = "-> ";
    else if (bp)
        prefix = "  #";
    else
        prefix = "   ";
    sds thisline = sdscatprintf(sdsempty(),"%s%-3d %s", prefix, lnum, line);
    ldbLog(thisline);
}