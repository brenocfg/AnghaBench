#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct hllhdr {int* card; int /*<<< orphan*/  encoding; } ;
struct TYPE_16__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  max ;
struct TYPE_17__ {int argc; int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;
struct TYPE_19__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_18__ {int /*<<< orphan*/  czero; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 int HLL_HDR_SIZE ; 
 int /*<<< orphan*/  HLL_RAW ; 
 int HLL_REGISTERS ; 
 scalar_t__ HLL_VALID_CACHE (struct hllhdr*) ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dbUnshareStringValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int hllCount (struct hllhdr*,int*) ; 
 scalar_t__ hllMerge (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  invalid_hll_err ; 
 scalar_t__ isHLLObjectOrReply (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* lookupKeyRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pfcountCommand(client *c) {
    robj *o;
    struct hllhdr *hdr;
    uint64_t card;

    /* Case 1: multi-key keys, cardinality of the union.
     *
     * When multiple keys are specified, PFCOUNT actually computes
     * the cardinality of the merge of the N HLLs specified. */
    if (c->argc > 2) {
        uint8_t max[HLL_HDR_SIZE+HLL_REGISTERS], *registers;
        int j;

        /* Compute an HLL with M[i] = MAX(M[i]_j). */
        memset(max,0,sizeof(max));
        hdr = (struct hllhdr*) max;
        hdr->encoding = HLL_RAW; /* Special internal-only encoding. */
        registers = max + HLL_HDR_SIZE;
        for (j = 1; j < c->argc; j++) {
            /* Check type and size. */
            robj *o = lookupKeyRead(c->db,c->argv[j]);
            if (o == NULL) continue; /* Assume empty HLL for non existing var.*/
            if (isHLLObjectOrReply(c,o) != C_OK) return;

            /* Merge with this HLL with our 'max' HLL by setting max[i]
             * to MAX(max[i],hll[i]). */
            if (hllMerge(registers,o) == C_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
        }

        /* Compute cardinality of the resulting set. */
        addReplyLongLong(c,hllCount(hdr,NULL));
        return;
    }

    /* Case 2: cardinality of the single HLL.
     *
     * The user specified a single key. Either return the cached value
     * or compute one and update the cache. */
    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* No key? Cardinality is zero since no element was added, otherwise
         * we would have a key as HLLADD creates it as a side effect. */
        addReply(c,shared.czero);
    } else {
        if (isHLLObjectOrReply(c,o) != C_OK) return;
        o = dbUnshareStringValue(c->db,c->argv[1],o);

        /* Check if the cached cardinality is valid. */
        hdr = o->ptr;
        if (HLL_VALID_CACHE(hdr)) {
            /* Just return the cached value. */
            card = (uint64_t)hdr->card[0];
            card |= (uint64_t)hdr->card[1] << 8;
            card |= (uint64_t)hdr->card[2] << 16;
            card |= (uint64_t)hdr->card[3] << 24;
            card |= (uint64_t)hdr->card[4] << 32;
            card |= (uint64_t)hdr->card[5] << 40;
            card |= (uint64_t)hdr->card[6] << 48;
            card |= (uint64_t)hdr->card[7] << 56;
        } else {
            int invalid = 0;
            /* Recompute it and update the cached value. */
            card = hllCount(hdr,&invalid);
            if (invalid) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            hdr->card[0] = card & 0xff;
            hdr->card[1] = (card >> 8) & 0xff;
            hdr->card[2] = (card >> 16) & 0xff;
            hdr->card[3] = (card >> 24) & 0xff;
            hdr->card[4] = (card >> 32) & 0xff;
            hdr->card[5] = (card >> 40) & 0xff;
            hdr->card[6] = (card >> 48) & 0xff;
            hdr->card[7] = (card >> 56) & 0xff;
            /* This is not considered a read-only command even if the
             * data structure is not modified, since the cached value
             * may be modified and given that the HLL is a Redis string
             * we need to propagate the change. */
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        }
        addReplyLongLong(c,card);
    }
}