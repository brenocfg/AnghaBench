#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* array; } ;
struct TYPE_6__ {int flags; scalar_t__ type; size_t len; scalar_t__ proto; TYPE_1__ val; } ;
typedef  TYPE_2__ RedisModuleCallReply ;

/* Variables and functions */
 int REDISMODULE_REPLYFLAG_NESTED ; 
 int REDISMODULE_REPLYFLAG_TOPARSE ; 
 scalar_t__ REDISMODULE_REPLY_ARRAY ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void RM_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
    /* Don't free nested replies by default: the user must always free the
     * toplevel reply. However be gentle and don't crash if the module
     * misuses the API. */
    if (!freenested && reply->flags & REDISMODULE_REPLYFLAG_NESTED) return;

    if (!(reply->flags & REDISMODULE_REPLYFLAG_TOPARSE)) {
        if (reply->type == REDISMODULE_REPLY_ARRAY) {
            size_t j;
            for (j = 0; j < reply->len; j++)
                RM_FreeCallReply_Rec(reply->val.array+j,1);
            zfree(reply->val.array);
        }
    }

    /* For nested replies, we don't free reply->proto (which if not NULL
     * references the parent reply->proto buffer), nor the structure
     * itself which is allocated as an array of structures, and is freed
     * when the array value is released. */
    if (!(reply->flags & REDISMODULE_REPLYFLAG_NESTED)) {
        if (reply->proto) sdsfree(reply->proto);
        zfree(reply);
    }
}