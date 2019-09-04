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
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*,long long) ; 
 int /*<<< orphan*/  sdsempty () ; 

void rewriteConfigNumericalOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}