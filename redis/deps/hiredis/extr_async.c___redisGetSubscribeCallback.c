#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_16__ {scalar_t__ type; int elements; TYPE_1__** element; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ redisContext ;
struct TYPE_18__ {scalar_t__ pending_subs; } ;
typedef  TYPE_5__ redisCallback ;
struct TYPE_15__ {int /*<<< orphan*/  invalid; int /*<<< orphan*/ * patterns; int /*<<< orphan*/ * channels; } ;
struct TYPE_19__ {TYPE_2__ sub; TYPE_4__ c; } ;
typedef  TYPE_6__ redisAsyncContext ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_14__ {scalar_t__ type; char* str; scalar_t__ integer; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_ARRAY ; 
 scalar_t__ REDIS_REPLY_INTEGER ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  REDIS_SUBSCRIBED ; 
 int /*<<< orphan*/  __redisShiftCallback (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* dictGetEntryVal (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char tolower (char) ; 

__attribute__((used)) static int __redisGetSubscribeCallback(redisAsyncContext *ac, redisReply *reply, redisCallback *dstcb) {
    redisContext *c = &(ac->c);
    dict *callbacks;
    redisCallback *cb;
    dictEntry *de;
    int pvariant;
    char *stype;
    sds sname;

    /* Custom reply functions are not supported for pub/sub. This will fail
     * very hard when they are used... */
    if (reply->type == REDIS_REPLY_ARRAY) {
        assert(reply->elements >= 2);
        assert(reply->element[0]->type == REDIS_REPLY_STRING);
        stype = reply->element[0]->str;
        pvariant = (tolower(stype[0]) == 'p') ? 1 : 0;

        if (pvariant)
            callbacks = ac->sub.patterns;
        else
            callbacks = ac->sub.channels;

        /* Locate the right callback */
        assert(reply->element[1]->type == REDIS_REPLY_STRING);
        sname = sdsnewlen(reply->element[1]->str,reply->element[1]->len);
        de = dictFind(callbacks,sname);
        if (de != NULL) {
            cb = dictGetEntryVal(de);

            /* If this is an subscribe reply decrease pending counter. */
            if (strcasecmp(stype+pvariant,"subscribe") == 0) {
                cb->pending_subs -= 1;
            }

            memcpy(dstcb,cb,sizeof(*dstcb));

            /* If this is an unsubscribe message, remove it. */
            if (strcasecmp(stype+pvariant,"unsubscribe") == 0) {
                if (cb->pending_subs == 0)
                    dictDelete(callbacks,sname);

                /* If this was the last unsubscribe message, revert to
                 * non-subscribe mode. */
                assert(reply->element[2]->type == REDIS_REPLY_INTEGER);

                /* Unset subscribed flag only when no pipelined pending subscribe. */
                if (reply->element[2]->integer == 0
                    && dictSize(ac->sub.channels) == 0
                    && dictSize(ac->sub.patterns) == 0)
                    c->flags &= ~REDIS_SUBSCRIBED;
            }
        }
        sdsfree(sname);
    } else {
        /* Shift callback for invalid commands. */
        __redisShiftCallback(&ac->sub.invalid,dstcb);
    }
    return REDIS_OK;
}