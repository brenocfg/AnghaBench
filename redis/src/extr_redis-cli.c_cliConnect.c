#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* hostsocket; char* hostip; int hostport; scalar_t__ tls; } ;
struct TYPE_7__ {char* errstr; int /*<<< orphan*/  fd; scalar_t__ err; } ;

/* Variables and functions */
 int CC_FORCE ; 
 int CC_QUIET ; 
 int /*<<< orphan*/  REDIS_CLI_KEEPALIVE_INTERVAL ; 
 scalar_t__ REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  anetKeepAlive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cliAuth () ; 
 scalar_t__ cliSecureConnection (TYPE_1__*,char const**) ; 
 scalar_t__ cliSelect () ; 
 scalar_t__ cliSwitchProto () ; 
 TYPE_5__ config ; 
 TYPE_1__* context ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* redisConnect (char*,int) ; 
 TYPE_1__* redisConnectUnix (char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cliConnect(int flags) {
    if (context == NULL || flags & CC_FORCE) {
        if (context != NULL) {
            redisFree(context);
        }

        if (config.hostsocket == NULL) {
            context = redisConnect(config.hostip,config.hostport);
        } else {
            context = redisConnectUnix(config.hostsocket);
        }

        if (!context->err && config.tls) {
            const char *err = NULL;
            if (cliSecureConnection(context, &err) == REDIS_ERR && err) {
                fprintf(stderr, "Could not negotiate a TLS connection: %s\n", err);
                context = NULL;
                redisFree(context);
                return REDIS_ERR;
            }
        }

        if (context->err) {
            if (!(flags & CC_QUIET)) {
                fprintf(stderr,"Could not connect to Redis at ");
                if (config.hostsocket == NULL)
                    fprintf(stderr,"%s:%d: %s\n",
                        config.hostip,config.hostport,context->errstr);
                else
                    fprintf(stderr,"%s: %s\n",
                        config.hostsocket,context->errstr);
            }
            redisFree(context);
            context = NULL;
            return REDIS_ERR;
        }


        /* Set aggressive KEEP_ALIVE socket option in the Redis context socket
         * in order to prevent timeouts caused by the execution of long
         * commands. At the same time this improves the detection of real
         * errors. */
        anetKeepAlive(NULL, context->fd, REDIS_CLI_KEEPALIVE_INTERVAL);

        /* Do AUTH, select the right DB, switch to RESP3 if needed. */
        if (cliAuth() != REDIS_OK)
            return REDIS_ERR;
        if (cliSelect() != REDIS_OK)
            return REDIS_ERR;
        if (cliSwitchProto() != REDIS_OK)
            return REDIS_ERR;
    }
    return REDIS_OK;
}