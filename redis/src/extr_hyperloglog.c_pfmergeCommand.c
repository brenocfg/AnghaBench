#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct hllhdr {int encoding; int /*<<< orphan*/  registers; } ;
struct TYPE_24__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  max ;
struct TYPE_25__ {int argc; TYPE_3__* db; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_28__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_27__ {int /*<<< orphan*/  ok; } ;
struct TYPE_26__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
#define  HLL_DENSE 129 
 int /*<<< orphan*/  HLL_INVALIDATE_CACHE (struct hllhdr*) ; 
 int HLL_REGISTERS ; 
#define  HLL_SPARSE 128 
 int /*<<< orphan*/  NOTIFY_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createHLLObject () ; 
 int /*<<< orphan*/  dbAdd (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* dbUnshareStringValue (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hllDenseSet (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ hllMerge (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  hllSparseSet (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ hllSparseToDense (TYPE_1__*) ; 
 int /*<<< orphan*/  invalid_hll_err ; 
 scalar_t__ isHLLObjectOrReply (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* lookupKeyRead (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyWrite (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ ) ; 
 TYPE_5__ server ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,int /*<<< orphan*/ ) ; 

void pfmergeCommand(client *c) {
    uint8_t max[HLL_REGISTERS];
    struct hllhdr *hdr;
    int j;
    int use_dense = 0; /* Use dense representation as target? */

    /* Compute an HLL with M[i] = MAX(M[i]_j).
     * We store the maximum into the max array of registers. We'll write
     * it to the target variable later. */
    memset(max,0,sizeof(max));
    for (j = 1; j < c->argc; j++) {
        /* Check type and size. */
        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) continue; /* Assume empty HLL for non existing var. */
        if (isHLLObjectOrReply(c,o) != C_OK) return;

        /* If at least one involved HLL is dense, use the dense representation
         * as target ASAP to save time and avoid the conversion step. */
        hdr = o->ptr;
        if (hdr->encoding == HLL_DENSE) use_dense = 1;

        /* Merge with this HLL with our 'max' HLL by setting max[i]
         * to MAX(max[i],hll[i]). */
        if (hllMerge(max,o) == C_ERR) {
            addReplySds(c,sdsnew(invalid_hll_err));
            return;
        }
    }

    /* Create / unshare the destination key's value if needed. */
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
         * is guaranteed to return bytes initialized to zero. */
        o = createHLLObject();
        dbAdd(c->db,c->argv[1],o);
    } else {
        /* If key exists we are sure it's of the right type/size
         * since we checked when merging the different HLLs, so we
         * don't check again. */
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Convert the destination object to dense representation if at least
     * one of the inputs was dense. */
    if (use_dense && hllSparseToDense(o) == C_ERR) {
        addReplySds(c,sdsnew(invalid_hll_err));
        return;
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    for (j = 0; j < HLL_REGISTERS; j++) {
        if (max[j] == 0) continue;
        hdr = o->ptr;
        switch(hdr->encoding) {
        case HLL_DENSE: hllDenseSet(hdr->registers,j,max[j]); break;
        case HLL_SPARSE: hllSparseSet(o,j,max[j]); break;
        }
    }
    hdr = o->ptr; /* o->ptr may be different now, as a side effect of
                     last hllSparseSet() call. */
    HLL_INVALIDATE_CACHE(hdr);

    signalModifiedKey(c->db,c->argv[1]);
    /* We generate a PFADD event for PFMERGE for semantical simplicity
     * since in theory this is a mass-add of elements. */
    notifyKeyspaceEvent(NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
    addReply(c,shared.ok);
}