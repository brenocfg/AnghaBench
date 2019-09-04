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
struct TYPE_2__ {scalar_t__ cluster_reissue_command; scalar_t__ cluster_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_FORCE ; 
 int REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  cliConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliPrintContextError () ; 
 scalar_t__ cliSendCommand (int,char**,long) ; 
 TYPE_1__ config ; 

__attribute__((used)) static int issueCommandRepeat(int argc, char **argv, long repeat) {
    while (1) {
        config.cluster_reissue_command = 0;
        if (cliSendCommand(argc,argv,repeat) != REDIS_OK) {
            cliConnect(CC_FORCE);

            /* If we still cannot send the command print error.
             * We'll try to reconnect the next time. */
            if (cliSendCommand(argc,argv,repeat) != REDIS_OK) {
                cliPrintContextError();
                return REDIS_ERR;
            }
        }
        /* Issue the command again if we got redirected in cluster mode */
        if (config.cluster_mode && config.cluster_reissue_command) {
            cliConnect(CC_FORCE);
        } else {
            break;
        }
    }
    return REDIS_OK;
}