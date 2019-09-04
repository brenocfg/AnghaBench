#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  int uint64_t ;
struct hllhdr {scalar_t__ encoding; int /*<<< orphan*/  registers; } ;
typedef  scalar_t__ sds ;
struct TYPE_7__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  unsigned int int64_t ;
typedef  int /*<<< orphan*/  ele ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_9__ {int hll_sparse_max_bytes; } ;
struct TYPE_8__ {int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  HLL_DENSE_GET_REGISTER (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HLL_DENSE_SET_REGISTER (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ HLL_DENSE_SIZE ; 
 scalar_t__ HLL_HDR_SIZE ; 
 int HLL_REGISTERS ; 
 unsigned int HLL_REGISTER_MAX ; 
 scalar_t__ HLL_SPARSE ; 
 unsigned int HLL_TEST_CYCLES ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long,...) ; 
 int ceil (double) ; 
 TYPE_1__* createHLLObject () ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  hllAdd (TYPE_1__*,unsigned char*,int) ; 
 scalar_t__ hllCount (struct hllhdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hllDenseAdd (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int rand () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 scalar_t__ sdsnewlen (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__ server ; 
 TYPE_2__ shared ; 
 double sqrt (int) ; 

void pfselftestCommand(client *c) {
    unsigned int j, i;
    sds bitcounters = sdsnewlen(NULL,HLL_DENSE_SIZE);
    struct hllhdr *hdr = (struct hllhdr*) bitcounters, *hdr2;
    robj *o = NULL;
    uint8_t bytecounters[HLL_REGISTERS];

    /* Test 1: access registers.
     * The test is conceived to test that the different counters of our data
     * structure are accessible and that setting their values both result in
     * the correct value to be retained and not affect adjacent values. */
    for (j = 0; j < HLL_TEST_CYCLES; j++) {
        /* Set the HLL counters and an array of unsigned byes of the
         * same size to the same set of random values. */
        for (i = 0; i < HLL_REGISTERS; i++) {
            unsigned int r = rand() & HLL_REGISTER_MAX;

            bytecounters[i] = r;
            HLL_DENSE_SET_REGISTER(hdr->registers,i,r);
        }
        /* Check that we are able to retrieve the same values. */
        for (i = 0; i < HLL_REGISTERS; i++) {
            unsigned int val;

            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
            if (val != bytecounters[i]) {
                addReplyErrorFormat(c,
                    "TESTFAILED Register %d should be %d but is %d",
                    i, (int) bytecounters[i], (int) val);
                goto cleanup;
            }
        }
    }

    /* Test 2: approximation error.
     * The test adds unique elements and check that the estimated value
     * is always reasonable bounds.
     *
     * We check that the error is smaller than a few times than the expected
     * standard error, to make it very unlikely for the test to fail because
     * of a "bad" run.
     *
     * The test is performed with both dense and sparse HLLs at the same
     * time also verifying that the computed cardinality is the same. */
    memset(hdr->registers,0,HLL_DENSE_SIZE-HLL_HDR_SIZE);
    o = createHLLObject();
    double relerr = 1.04/sqrt(HLL_REGISTERS);
    int64_t checkpoint = 1;
    uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
    uint64_t ele;
    for (j = 1; j <= 10000000; j++) {
        ele = j ^ seed;
        hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
        hllAdd(o,(unsigned char*)&ele,sizeof(ele));

        /* Make sure that for small cardinalities we use sparse
         * encoding. */
        if (j == checkpoint && j < server.hll_sparse_max_bytes/2) {
            hdr2 = o->ptr;
            if (hdr2->encoding != HLL_SPARSE) {
                addReplyError(c, "TESTFAILED sparse encoding not used");
                goto cleanup;
            }
        }

        /* Check that dense and sparse representations agree. */
        if (j == checkpoint && hllCount(hdr,NULL) != hllCount(o->ptr,NULL)) {
                addReplyError(c, "TESTFAILED dense/sparse disagree");
                goto cleanup;
        }

        /* Check error. */
        if (j == checkpoint) {
            int64_t abserr = checkpoint - (int64_t)hllCount(hdr,NULL);
            uint64_t maxerr = ceil(relerr*6*checkpoint);

            /* Adjust the max error we expect for cardinality 10
             * since from time to time it is statistically likely to get
             * much higher error due to collision, resulting into a false
             * positive. */
            if (j == 10) maxerr = 1;

            if (abserr < 0) abserr = -abserr;
            if (abserr > (int64_t)maxerr) {
                addReplyErrorFormat(c,
                    "TESTFAILED Too big error. card:%llu abserr:%llu",
                    (unsigned long long) checkpoint,
                    (unsigned long long) abserr);
                goto cleanup;
            }
            checkpoint *= 10;
        }
    }

    /* Success! */
    addReply(c,shared.ok);

cleanup:
    sdsfree(bitcounters);
    if (o) decrRefCount(o);
}