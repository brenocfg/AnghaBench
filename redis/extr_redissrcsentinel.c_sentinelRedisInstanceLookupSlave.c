#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  slaves; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int NET_PEER_ID_LEN ; 
 int SRI_MASTER ; 
 int /*<<< orphan*/  anetFormatAddr (char*,int,char*,int) ; 
 TYPE_1__* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  serverAssert (int) ; 

sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
                sentinelRedisInstance *ri, char *ip, int port)
{
    sds key;
    sentinelRedisInstance *slave;
    char buf[NET_PEER_ID_LEN];

    serverAssert(ri->flags & SRI_MASTER);
    anetFormatAddr(buf,sizeof(buf),ip,port);
    key = sdsnew(buf);
    slave = dictFetchValue(ri->slaves,key);
    sdsfree(key);
    return slave;
}