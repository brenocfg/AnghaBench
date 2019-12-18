#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_12__ {int argc; size_t resp; TYPE_4__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_14__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * null; int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyDoubleDistance (TYPE_1__*,double) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeGeohash (double,double*) ; 
 double extractUnitOrReply (TYPE_1__*,TYPE_4__*) ; 
 double geohashGetDistance (double,double,double,double) ; 
 int /*<<< orphan*/ * lookupKeyReadOrReply (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ shared ; 
 scalar_t__ zsetScore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

void geodistCommand(client *c) {
    double to_meter = 1;

    /* Check if there is the unit to extract, otherwise assume meters. */
    if (c->argc == 5) {
        to_meter = extractUnitOrReply(c,c->argv[4]);
        if (to_meter < 0) return;
    } else if (c->argc > 5) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Look up the requested zset */
    robj *zobj = NULL;
    if ((zobj = lookupKeyReadOrReply(c, c->argv[1], shared.null[c->resp]))
        == NULL || checkType(c, zobj, OBJ_ZSET)) return;

    /* Get the scores. We need both otherwise NULL is returned. */
    double score1, score2, xyxy[4];
    if (zsetScore(zobj, c->argv[2]->ptr, &score1) == C_ERR ||
        zsetScore(zobj, c->argv[3]->ptr, &score2) == C_ERR)
    {
        addReplyNull(c);
        return;
    }

    /* Decode & compute the distance. */
    if (!decodeGeohash(score1,xyxy) || !decodeGeohash(score2,xyxy+2))
        addReplyNull(c);
    else
        addReplyDoubleDistance(c,
            geohashGetDistance(xyxy[0],xyxy[1],xyxy[2],xyxy[3]) / to_meter);
}