#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_4__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ redisDb ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  aux ;
struct TYPE_5__ {int dbnum; TYPE_1__* db; } ;

/* Variables and functions */
 int /*<<< orphan*/ * createStringObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixDigest (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int sdslen (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  xorDigest (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  xorObjectDigest (TYPE_1__*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 

void computeDatasetDigest(unsigned char *final) {
    unsigned char digest[20];
    dictIterator *di = NULL;
    dictEntry *de;
    int j;
    uint32_t aux;

    memset(final,0,20); /* Start with a clean result */

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;

        if (dictSize(db->dict) == 0) continue;
        di = dictGetSafeIterator(db->dict);

        /* hash the DB id, so the same dataset moved in a different
         * DB will lead to a different digest */
        aux = htonl(j);
        mixDigest(final,&aux,sizeof(aux));

        /* Iterate this DB writing every entry */
        while((de = dictNext(di)) != NULL) {
            sds key;
            robj *keyobj, *o;

            memset(digest,0,20); /* This key-val digest */
            key = dictGetKey(de);
            keyobj = createStringObject(key,sdslen(key));

            mixDigest(digest,key,sdslen(key));

            o = dictGetVal(de);
            xorObjectDigest(db,keyobj,digest,o);

            /* We can finally xor the key-val digest to the final digest */
            xorDigest(final,digest,20);
            decrRefCount(keyobj);
        }
        dictReleaseIterator(di);
    }
}