#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_8__ {int argc; TYPE_2__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplyHumanLongDouble (TYPE_1__*,double) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_1__*) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeGeohash (double,double*) ; 
 int /*<<< orphan*/ * lookupKeyRead (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zsetScore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

void geoposCommand(client *c) {
    int j;

    /* Look up the requested zset */
    robj *zobj = lookupKeyRead(c->db, c->argv[1]);
    if (zobj && checkType(c, zobj, OBJ_ZSET)) return;

    /* Report elements one after the other, using a null bulk reply for
     * missing elements. */
    addReplyArrayLen(c,c->argc-2);
    for (j = 2; j < c->argc; j++) {
        double score;
        if (!zobj || zsetScore(zobj, c->argv[j]->ptr, &score) == C_ERR) {
            addReplyNullArray(c);
        } else {
            /* Decode... */
            double xy[2];
            if (!decodeGeohash(score,xy)) {
                addReplyNullArray(c);
                continue;
            }
            addReplyArrayLen(c,2);
            addReplyHumanLongDouble(c,xy[0]);
            addReplyHumanLongDouble(c,xy[1]);
        }
    }
}