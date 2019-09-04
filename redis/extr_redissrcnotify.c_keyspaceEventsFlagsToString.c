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
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int NOTIFY_ALL ; 
 int NOTIFY_EVICTED ; 
 int NOTIFY_EXPIRED ; 
 int NOTIFY_GENERIC ; 
 int NOTIFY_HASH ; 
 int NOTIFY_KEYEVENT ; 
 int NOTIFY_KEYSPACE ; 
 int NOTIFY_KEY_MISS ; 
 int NOTIFY_LIST ; 
 int NOTIFY_SET ; 
 int NOTIFY_STREAM ; 
 int NOTIFY_STRING ; 
 int NOTIFY_ZSET ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 

sds keyspaceEventsFlagsToString(int flags) {
    sds res;

    res = sdsempty();
    if ((flags & NOTIFY_ALL) == NOTIFY_ALL) {
        res = sdscatlen(res,"A",1);
    } else {
        if (flags & NOTIFY_GENERIC) res = sdscatlen(res,"g",1);
        if (flags & NOTIFY_STRING) res = sdscatlen(res,"$",1);
        if (flags & NOTIFY_LIST) res = sdscatlen(res,"l",1);
        if (flags & NOTIFY_SET) res = sdscatlen(res,"s",1);
        if (flags & NOTIFY_HASH) res = sdscatlen(res,"h",1);
        if (flags & NOTIFY_ZSET) res = sdscatlen(res,"z",1);
        if (flags & NOTIFY_EXPIRED) res = sdscatlen(res,"x",1);
        if (flags & NOTIFY_EVICTED) res = sdscatlen(res,"e",1);
        if (flags & NOTIFY_STREAM) res = sdscatlen(res,"t",1);
        if (flags & NOTIFY_KEY_MISS) res = sdscatlen(res,"m",1);
    }
    if (flags & NOTIFY_KEYSPACE) res = sdscatlen(res,"K",1);
    if (flags & NOTIFY_KEYEVENT) res = sdscatlen(res,"E",1);
    return res;
}