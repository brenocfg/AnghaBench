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
typedef  char* sds ;

/* Variables and functions */
 int CMD_ADMIN ; 
 int CMD_DENYOOM ; 
 int CMD_FAST ; 
 int CMD_LOADING ; 
 int CMD_MODULE_GETKEYS ; 
 int CMD_MODULE_NO_CLUSTER ; 
 int CMD_NOSCRIPT ; 
 int CMD_PUBSUB ; 
 int CMD_RANDOM ; 
 int CMD_READONLY ; 
 int CMD_SKIP_MONITOR ; 
 int CMD_STALE ; 
 int CMD_WRITE ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 char** sdssplitlen (char*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int commandFlagsFromString(char *s) {
    int count, j;
    int flags = 0;
    sds *tokens = sdssplitlen(s,strlen(s)," ",1,&count);
    for (j = 0; j < count; j++) {
        char *t = tokens[j];
        if (!strcasecmp(t,"write")) flags |= CMD_WRITE;
        else if (!strcasecmp(t,"readonly")) flags |= CMD_READONLY;
        else if (!strcasecmp(t,"admin")) flags |= CMD_ADMIN;
        else if (!strcasecmp(t,"deny-oom")) flags |= CMD_DENYOOM;
        else if (!strcasecmp(t,"deny-script")) flags |= CMD_NOSCRIPT;
        else if (!strcasecmp(t,"allow-loading")) flags |= CMD_LOADING;
        else if (!strcasecmp(t,"pubsub")) flags |= CMD_PUBSUB;
        else if (!strcasecmp(t,"random")) flags |= CMD_RANDOM;
        else if (!strcasecmp(t,"allow-stale")) flags |= CMD_STALE;
        else if (!strcasecmp(t,"no-monitor")) flags |= CMD_SKIP_MONITOR;
        else if (!strcasecmp(t,"fast")) flags |= CMD_FAST;
        else if (!strcasecmp(t,"getkeys-api")) flags |= CMD_MODULE_GETKEYS;
        else if (!strcasecmp(t,"no-cluster")) flags |= CMD_MODULE_NO_CLUSTER;
        else break;
    }
    sdsfreesplitres(tokens,count);
    if (j != count) return -1; /* Some token not processed correctly. */
    return flags;
}