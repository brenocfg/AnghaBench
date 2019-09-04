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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct server_pool {int /*<<< orphan*/  dist_type; int /*<<< orphan*/  server; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct server {TYPE_1__ pname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VERB ; 
 struct server* array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_pool_idx (struct server_pool*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct server *
server_pool_server(struct server_pool *pool, uint8_t *key, uint32_t keylen)
{
    struct server *server;
    uint32_t idx;

    idx = server_pool_idx(pool, key, keylen);
    server = array_get(&pool->server, idx);

    log_debug(LOG_VERB, "key '%.*s' on dist %d maps to server '%.*s'", keylen,
              key, pool->dist_type, server->pname.len, server->pname.data);

    return server;
}