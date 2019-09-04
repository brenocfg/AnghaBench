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
typedef  char* sds ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {int /*<<< orphan*/  prompt; int /*<<< orphan*/ * dbnum; int /*<<< orphan*/  hostport; int /*<<< orphan*/  hostip; int /*<<< orphan*/ * hostsocket; scalar_t__ eval_ldb; } ;

/* Variables and functions */
 int /*<<< orphan*/  anetFormatAddr (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ config ; 
 char* sdscatfmt (char*,char*,int /*<<< orphan*/ *) ; 
 char* sdscatlen (char*,char*,int) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void cliRefreshPrompt(void) {
    if (config.eval_ldb) return;

    sds prompt = sdsempty();
    if (config.hostsocket != NULL) {
        prompt = sdscatfmt(prompt,"redis %s",config.hostsocket);
    } else {
        char addr[256];
        anetFormatAddr(addr, sizeof(addr), config.hostip, config.hostport);
        prompt = sdscatlen(prompt,addr,strlen(addr));
    }

    /* Add [dbnum] if needed */
    if (config.dbnum != 0)
        prompt = sdscatfmt(prompt,"[%i]",config.dbnum);

    /* Copy the prompt in the static buffer. */
    prompt = sdscatlen(prompt,"> ",2);
    snprintf(config.prompt,sizeof(config.prompt),"%s",prompt);
    sdsfree(prompt);
}