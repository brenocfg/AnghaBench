#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* sizecmd; } ;
typedef  TYPE_2__ typeinfo ;
struct TYPE_12__ {unsigned int elements; scalar_t__ type; unsigned long long integer; TYPE_1__** element; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_13__ {int err; char* errstr; } ;
struct TYPE_10__ {char* str; } ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 scalar_t__ REDIS_REPLY_INTEGER ; 
 TYPE_4__* context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_3__*) ; 
 int /*<<< orphan*/  redisAppendCommand (TYPE_4__*,char*,char*,char*,...) ; 
 scalar_t__ redisGetReply (TYPE_4__*,void**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void getKeySizes(redisReply *keys, typeinfo **types,
                        unsigned long long *sizes, int memkeys,
                        unsigned memkeys_samples)
{
    redisReply *reply;
    unsigned int i;

    /* Pipeline size commands */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that disappeared between SCAN and TYPE (or unknown types when not in memkeys mode) */
        if(!types[i] || (!types[i]->sizecmd && !memkeys))
            continue;

        if (!memkeys)
            redisAppendCommand(context, "%s %s",
                types[i]->sizecmd, keys->element[i]->str);
        else if (memkeys_samples==0)
            redisAppendCommand(context, "%s %s %s",
                "MEMORY", "USAGE", keys->element[i]->str);
        else
            redisAppendCommand(context, "%s %s %s SAMPLES %u",
                "MEMORY", "USAGE", keys->element[i]->str, memkeys_samples);
    }

    /* Retrieve sizes */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that disappeared between SCAN and TYPE (or unknown types when not in memkeys mode) */
        if(!types[i] || (!types[i]->sizecmd && !memkeys)) {
            sizes[i] = 0;
            continue;
        }

        /* Retrieve size */
        if(redisGetReply(context, (void**)&reply)!=REDIS_OK) {
            fprintf(stderr, "Error getting size for key '%s' (%d: %s)\n",
                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_INTEGER) {
            /* Theoretically the key could have been removed and
             * added as a different type between TYPE and SIZE */
            fprintf(stderr,
                "Warning:  %s on '%s' failed (may have changed type)\n",
                !memkeys? types[i]->sizecmd: "MEMORY USAGE",
                keys->element[i]->str);
            sizes[i] = 0;
        } else {
            sizes[i] = reply->integer;
        }

        freeReplyObject(reply);
    }
}