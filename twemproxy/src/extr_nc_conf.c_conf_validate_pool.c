#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  valid; } ;
struct conf_pool {int valid; scalar_t__ distribution; scalar_t__ hash; scalar_t__ timeout; scalar_t__ backlog; scalar_t__ redis; scalar_t__ tcpkeepalive; scalar_t__ redis_db; scalar_t__ preconnect; scalar_t__ auto_eject_hosts; scalar_t__ server_connections; scalar_t__ server_retry_timeout; scalar_t__ server_failure_limit; TYPE_2__ redis_auth; int /*<<< orphan*/  client_connections; TYPE_1__ listen; int /*<<< orphan*/  name; } ;
struct conf {int dummy; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CONF_DEFAULT_AUTO_EJECT_HOSTS ; 
 int /*<<< orphan*/  CONF_DEFAULT_CLIENT_CONNECTIONS ; 
 scalar_t__ CONF_DEFAULT_DIST ; 
 scalar_t__ CONF_DEFAULT_HASH ; 
 scalar_t__ CONF_DEFAULT_LISTEN_BACKLOG ; 
 scalar_t__ CONF_DEFAULT_PRECONNECT ; 
 scalar_t__ CONF_DEFAULT_REDIS ; 
 scalar_t__ CONF_DEFAULT_REDIS_DB ; 
 scalar_t__ CONF_DEFAULT_SERVER_CONNECTIONS ; 
 scalar_t__ CONF_DEFAULT_SERVER_FAILURE_LIMIT ; 
 scalar_t__ CONF_DEFAULT_SERVER_RETRY_TIMEOUT ; 
 scalar_t__ CONF_DEFAULT_TCPKEEPALIVE ; 
 scalar_t__ CONF_DEFAULT_TIMEOUT ; 
 scalar_t__ CONF_UNSET_DIST ; 
 scalar_t__ CONF_UNSET_HASH ; 
 scalar_t__ CONF_UNSET_NUM ; 
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 scalar_t__ conf_validate_server (struct conf*,struct conf_pool*) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  string_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rstatus_t
conf_validate_pool(struct conf *cf, struct conf_pool *cp)
{
    rstatus_t status;

    ASSERT(!cp->valid);
    ASSERT(!string_empty(&cp->name));

    if (!cp->listen.valid) {
        log_error("conf: directive \"listen:\" is missing");
        return NC_ERROR;
    }

    /* set default values for unset directives */

    if (cp->distribution == CONF_UNSET_DIST) {
        cp->distribution = CONF_DEFAULT_DIST;
    }

    if (cp->hash == CONF_UNSET_HASH) {
        cp->hash = CONF_DEFAULT_HASH;
    }

    if (cp->timeout == CONF_UNSET_NUM) {
        cp->timeout = CONF_DEFAULT_TIMEOUT;
    }

    if (cp->backlog == CONF_UNSET_NUM) {
        cp->backlog = CONF_DEFAULT_LISTEN_BACKLOG;
    }

    cp->client_connections = CONF_DEFAULT_CLIENT_CONNECTIONS;

    if (cp->redis == CONF_UNSET_NUM) {
        cp->redis = CONF_DEFAULT_REDIS;
    }

    if (cp->tcpkeepalive == CONF_UNSET_NUM) {
        cp->tcpkeepalive = CONF_DEFAULT_TCPKEEPALIVE;
    }

    if (cp->redis_db == CONF_UNSET_NUM) {
        cp->redis_db = CONF_DEFAULT_REDIS_DB;
    }

    if (cp->preconnect == CONF_UNSET_NUM) {
        cp->preconnect = CONF_DEFAULT_PRECONNECT;
    }

    if (cp->auto_eject_hosts == CONF_UNSET_NUM) {
        cp->auto_eject_hosts = CONF_DEFAULT_AUTO_EJECT_HOSTS;
    }

    if (cp->server_connections == CONF_UNSET_NUM) {
        cp->server_connections = CONF_DEFAULT_SERVER_CONNECTIONS;
    } else if (cp->server_connections == 0) {
        log_error("conf: directive \"server_connections:\" cannot be 0");
        return NC_ERROR;
    }

    if (cp->server_retry_timeout == CONF_UNSET_NUM) {
        cp->server_retry_timeout = CONF_DEFAULT_SERVER_RETRY_TIMEOUT;
    }

    if (cp->server_failure_limit == CONF_UNSET_NUM) {
        cp->server_failure_limit = CONF_DEFAULT_SERVER_FAILURE_LIMIT;
    }

    if (!cp->redis && cp->redis_auth.len > 0) {
        log_error("conf: directive \"redis_auth:\" is only valid for a redis pool");
        return NC_ERROR;
    }

    status = conf_validate_server(cf, cp);
    if (status != NC_OK) {
        return status;
    }

    cp->valid = 1;

    return NC_OK;
}