#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_14__ {size_t resp; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_15__ {int /*<<< orphan*/ * null; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
 int /*<<< orphan*/  addReplyDouble (TYPE_2__*,double) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ shared ; 
 scalar_t__ zsetScore (TYPE_1__*,int /*<<< orphan*/ ,double*) ; 

void zscoreCommand(client *c) {
    robj *key = c->argv[1];
    robj *zobj;
    double score;

    if ((zobj = lookupKeyReadOrReply(c,key,shared.null[c->resp])) == NULL ||
        checkType(c,zobj,OBJ_ZSET)) return;

    if (zsetScore(zobj,c->argv[2]->ptr,&score) == C_ERR) {
        addReplyNull(c);
    } else {
        addReplyDouble(c,score);
    }
}