#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_13__ {int argc; TYPE_4__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_15__ {int bits; } ;
struct TYPE_14__ {int min; int max; } ;
typedef  TYPE_2__ GeoHashRange ;
typedef  TYPE_3__ GeoHashBits ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeGeohash (double,double*) ; 
 int /*<<< orphan*/  geohashEncode (TYPE_2__*,TYPE_2__*,double,double,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * lookupKeyRead (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ zsetScore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

void geohashCommand(client *c) {
    char *geoalphabet= "0123456789bcdefghjkmnpqrstuvwxyz";
    int j;

    /* Look up the requested zset */
    robj *zobj = lookupKeyRead(c->db, c->argv[1]);
    if (zobj && checkType(c, zobj, OBJ_ZSET)) return;

    /* Geohash elements one after the other, using a null bulk reply for
     * missing elements. */
    addReplyArrayLen(c,c->argc-2);
    for (j = 2; j < c->argc; j++) {
        double score;
        if (!zobj || zsetScore(zobj, c->argv[j]->ptr, &score) == C_ERR) {
            addReplyNull(c);
        } else {
            /* The internal format we use for geocoding is a bit different
             * than the standard, since we use as initial latitude range
             * -85,85, while the normal geohashing algorithm uses -90,90.
             * So we have to decode our position and re-encode using the
             * standard ranges in order to output a valid geohash string. */

            /* Decode... */
            double xy[2];
            if (!decodeGeohash(score,xy)) {
                addReplyNull(c);
                continue;
            }

            /* Re-encode */
            GeoHashRange r[2];
            GeoHashBits hash;
            r[0].min = -180;
            r[0].max = 180;
            r[1].min = -90;
            r[1].max = 90;
            geohashEncode(&r[0],&r[1],xy[0],xy[1],26,&hash);

            char buf[11];
            int i;
            for (i = 0; i < 10; i++) {
                int idx = (hash.bits >> (52-((i+1)*5))) & 0x1f;
                buf[i] = geoalphabet[idx];
            }
            buf[10] = '\0';
            addReplyBulkCBuffer(c,buf,10);
        }
    }
}