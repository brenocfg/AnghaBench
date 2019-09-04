#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_NOTOUCH ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,long long) ; 
 long long getExpire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookupKeyReadWithFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long mstime () ; 

void ttlGenericCommand(client *c, int output_ms) {
    long long expire, ttl = -1;

    /* If the key does not exist at all, return -2 */
    if (lookupKeyReadWithFlags(c->db,c->argv[1],LOOKUP_NOTOUCH) == NULL) {
        addReplyLongLong(c,-2);
        return;
    }
    /* The key exists. Return -1 if it has no expire, or the actual
     * TTL value otherwise. */
    expire = getExpire(c->db,c->argv[1]);
    if (expire != -1) {
        ttl = expire-mstime();
        if (ttl < 0) ttl = 0;
    }
    if (ttl == -1) {
        addReplyLongLong(c,-1);
    } else {
        addReplyLongLong(c,output_ms ? ttl : ((ttl+500)/1000));
    }
}