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
typedef  int /*<<< orphan*/ * sds ;

/* Variables and functions */
 int /*<<< orphan*/ * ACLDefaultUserFirstPassword () ; 
 int /*<<< orphan*/  rewriteConfigMarkAsProcessed (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sdscatlen (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * sdscatsds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdsnew (char*) ; 

void rewriteConfigRequirepassOption(struct rewriteConfigState *state, char *option) {
    int force = 1;
    sds line;
    sds password = ACLDefaultUserFirstPassword();

    /* If there is no password set, we don't want the requirepass option
     * to be present in the configuration at all. */
    if (password == NULL) {
        rewriteConfigMarkAsProcessed(state,option);
        return;
    }

    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatsds(line, password);

    rewriteConfigRewriteLine(state,option,line,force);
}