#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  id; TYPE_1__* db; int /*<<< orphan*/  conn; } ;
typedef  TYPE_2__ client ;
struct TYPE_8__ {int version; int port; int /*<<< orphan*/  id; int /*<<< orphan*/  db; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ RedisModuleClientInfoV1 ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_MULTI ; 
 int CLIENT_PUBSUB ; 
 int CLIENT_TRACKING ; 
 int CLIENT_UNIX_SOCKET ; 
 int /*<<< orphan*/  REDISMODULE_CLIENTINFO_FLAG_BLOCKED ; 
 int /*<<< orphan*/  REDISMODULE_CLIENTINFO_FLAG_MULTI ; 
 int /*<<< orphan*/  REDISMODULE_CLIENTINFO_FLAG_PUBSUB ; 
 int /*<<< orphan*/  REDISMODULE_CLIENTINFO_FLAG_TRACKING ; 
 int /*<<< orphan*/  REDISMODULE_CLIENTINFO_FLAG_UNIXSOCKET ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  connPeerToString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int modulePopulateClientInfoStructure(void *ci, client *client, int structver) {
    if (structver != 1) return REDISMODULE_ERR;

    RedisModuleClientInfoV1 *ci1 = ci;
    memset(ci1,0,sizeof(*ci1));
    ci1->version = structver;
    if (client->flags & CLIENT_MULTI)
        ci1->flags |= REDISMODULE_CLIENTINFO_FLAG_MULTI;
    if (client->flags & CLIENT_PUBSUB)
        ci1->flags |= REDISMODULE_CLIENTINFO_FLAG_PUBSUB;
    if (client->flags & CLIENT_UNIX_SOCKET)
        ci1->flags |= REDISMODULE_CLIENTINFO_FLAG_UNIXSOCKET;
    if (client->flags & CLIENT_TRACKING)
        ci1->flags |= REDISMODULE_CLIENTINFO_FLAG_TRACKING;
    if (client->flags & CLIENT_BLOCKED)
        ci1->flags |= REDISMODULE_CLIENTINFO_FLAG_BLOCKED;

    int port;
    connPeerToString(client->conn,ci1->addr,sizeof(ci1->addr),&port);
    ci1->port = port;
    ci1->db = client->db->id;
    ci1->id = client->id;
    return REDISMODULE_OK;
}