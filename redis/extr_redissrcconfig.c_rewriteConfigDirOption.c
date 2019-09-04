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
typedef  int /*<<< orphan*/  cwd ;

/* Variables and functions */
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  rewriteConfigMarkAsProcessed (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigStringOption (struct rewriteConfigState*,char*,char*,int /*<<< orphan*/ *) ; 

void rewriteConfigDirOption(struct rewriteConfigState *state) {
    char cwd[1024];

    if (getcwd(cwd,sizeof(cwd)) == NULL) {
        rewriteConfigMarkAsProcessed(state,"dir");
        return; /* no rewrite on error. */
    }
    rewriteConfigStringOption(state,"dir",cwd,NULL);
}